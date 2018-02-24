#include "stdafx.h"
#include "PythonScript.h"
#include <Python.h>
#include "Log.h"
#include "Unknown.h"
#include <cstdio>
#include "Loader.h"
#include "Image.h"
#include "Event/EventManager.h"

Unknown::Python::Interpreter* ::Unknown::Python::instance = NULL;

void Unknown::Python::Interpreter::checkError(PyObject* obj)
{
    if(obj == NULL)
    {
        PyErr_Print();
        exit(0);
    }
}

void Unknown::Python::Interpreter::addSearchPath(std::string name)
{
    PyObject* sysModulePath = PyObject_GetAttrString(this->moduleSys, "path");
    checkError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString(name.c_str()));
}

void Unknown::Python::Interpreter::init()
{
    Py_Initialize();

    this->moduleSys = PyImport_ImportModule("sys");
    checkError(this->moduleSys);
    this->addSearchPath(".");
}

Unknown::Python::Interpreter* Unknown::Python::getInterpreter()
{
    if(instance == NULL)
    {
        instance = new Interpreter();
        instance->init();
    }
    return instance;
}

PyMethodDef* generatePyMethodDef(std::string functionName, PyCFunction implementation, std::string doc)
{
    PyMethodDef* definition = (PyMethodDef*) malloc(sizeof(*definition));
    definition->ml_name = functionName.c_str();
    definition->ml_meth = implementation;
    definition->ml_flags = METH_VARARGS;
    definition->ml_doc = doc.c_str();

    return definition;
}

PyObject* generatePyCallable(std::string moduleName, PyMethodDef* methodDefinition)
{
    PyObject* moduleNamePyString = PyUnicode_FromString(moduleName.c_str());
Unknown::Python::getInterpreter()->checkError(moduleNamePyString);
    PyObject* callable = PyCFunction_NewEx(methodDefinition, (PyObject*)NULL, moduleNamePyString);
    Unknown::Python::getInterpreter()->checkError(callable);

    return callable;
}

void createMethod(std::string moduleName, PyObject* callable, std::string functionName)
{
    PyObject* moduleNameString = PyUnicode_FromString(moduleName.c_str());
    PyObject* module = PyImport_Import(moduleNameString);
    Unknown::Python::getInterpreter()->checkError(module);
    PyObject* originalDict = PyModule_GetDict(module);
    Unknown::Python::getInterpreter()->checkError(originalDict);
    PyDict_SetItemString(originalDict, functionName.c_str(), callable);
}

void registerMethod(std::string moduleName, std::string functionName, std::string functionDescription, PyCFunction callback)
{
    PyMethodDef* methodDefinition = generatePyMethodDef(functionName, callback, functionDescription);
    PyObject* callable = generatePyCallable(moduleName, methodDefinition);
    createMethod(moduleName, callable, functionName);
}

PyObject* PyGetElement(PyObject* sequence, int index, std::string pyFuncName, int line) {
    PyObject* element = PySequence_GetItem(sequence, index);

    if(!element) {
        UK_LOG_ERROR_VERBOSE(::Unknown::concat("Invalid element at ", pyFuncName, ":", line));
        PyErr_PrintEx(1);
        return nullptr;
    }

    return element;
}

#define PY_GET_OBJ(args, index) PyGetElement(args, index, __FUNCTION__, __LINE__)
#define PY_GET_LONG(args, index)  PyLong_AsLong(PY_GET_OBJ(args, index))
#define PY_GET_UTF8(args, index) PyUnicode_AsUTF8(PY_GET_OBJ(args, index))
#define PY_GET_FLOAT(args, index) PyFloat_AsDouble(PY_GET_OBJ(args, index))


PyObject* registerHookHandler(PyObject* self, PyObject* args)
{
    Unknown::HookType hookTypeEnum = (Unknown::HookType)PY_GET_LONG(args, 0);

    PyObject* callback = PY_GET_OBJ(args, 1);
    ::Unknown::registerHook([=]() {
        if(!PyObject_CallObject(callback, NULL)) {
            UK_LOG_ERROR("Unable to call func");
            PyObject_Print(callback, stdout, Py_PRINT_RAW);
            PyErr_PrintEx(1);
        }
    }, hookTypeEnum);
    Py_RETURN_NONE;
}

void rawImageDestructor(PyObject* imageCapsule)
{
    UK_LOG_INFO("Destroying image");
}

PyObject* createRawImageHandler(PyObject* self, PyObject* args)
{
    const char* fileName_cStr = PY_GET_UTF8(args, 0);
    printf("Loading file '%s'\n", fileName_cStr);

    std::unique_ptr<Unknown::Graphics::Image> image = UK_LOAD_IMAGE(fileName_cStr);
    PyObject* capsule = PyCapsule_New(image.release(), NULL, rawImageDestructor);

    if(!capsule) {
        UK_LOG_ERROR("Unable to form capsule");
        PyErr_PrintEx(1);
        return nullptr;
    }

    return capsule;
}

PyObject* renderRawImageHandler(PyObject* self, PyObject* args)
{
    PyObject* capsule = PY_GET_OBJ(args, 0);

    PyObject* dataTuple = PY_GET_OBJ(args, 1);

    int XCoord = PY_GET_LONG(dataTuple, 0);
    int YCoord = PY_GET_LONG(dataTuple, 1);
    int angle = PY_GET_LONG(dataTuple, 2);
    PyObject* clipTuple = PyTuple_GetItem(dataTuple, 3);

    Unknown::Graphics::Image* image = (Unknown::Graphics::Image*)PyCapsule_GetPointer(capsule, NULL);

    if(image) {
        if(PyTuple_Check(clipTuple)) {
            // Only use user given clip if it is not None
            SDL_Rect clipRect;
            clipRect.x = PY_GET_LONG(clipTuple, 0);
            clipRect.y = PY_GET_LONG(clipTuple, 1);
            clipRect.w = PY_GET_LONG(clipTuple, 2);
            clipRect.h = PY_GET_LONG(clipTuple, 3);

            image->render(XCoord, YCoord, angle, &clipRect);
        } else {
            image->render(XCoord, YCoord, angle, NULL);
        }
    }

    Py_RETURN_NONE;
}

PyObject* createRawTimer(PyObject* self, PyObject* args)
{
    double timeStep = PY_GET_FLOAT(args, 0);
    Unknown::Timer* timer = new Unknown::Timer(timeStep);

    PyObject* capsule = PyCapsule_New(timer, NULL, rawImageDestructor);

    if(!capsule) {
        UK_LOG_ERROR("Unable to form capsule");
        PyErr_PrintEx(1);
        return nullptr;
    }

    return capsule;
}

PyObject* resetRawTimer(PyObject* self, PyObject* args)
{
    PyObject* capsule = PY_GET_OBJ(args, 0);

    Unknown::Timer* timer = (Unknown::Timer*)PyCapsule_GetPointer(capsule, NULL);

    if(timer) {
        timer->resetTimer();
    }

    Py_RETURN_NONE;
}

PyObject* checkRawTimer(PyObject* self, PyObject* args)
{
    PyObject* capsule = PY_GET_OBJ(args, 0);

    Unknown::Timer* timer = (Unknown::Timer*)PyCapsule_GetPointer(capsule, NULL);

    if(timer) {
        if(timer->isTickComplete()) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
        }

    }
}

PyObject* registerRawEventHandler(PyObject* self, PyObject* args)
{
    PyObject* hookType = PySequence_GetItem(args, 0);
    if(!hookType) {
        UK_LOG_ERROR("Invalid hookType for handler");
        return nullptr;
    }

    long hookTypeLong = PyLong_AsLong(hookType);
    Unknown::EventType type = (Unknown::EventType)hookTypeLong;

    PyObject* handlerName = PySequence_GetItem(args, 1);
    if(!handlerName) {
        UK_LOG_ERROR("Invalid handler name");
        PyErr_PrintEx(1);
        return nullptr;
    }
    const char* handlerName_cStr = PyUnicode_AsUTF8(handlerName);

    PyObject* callback = PySequence_GetItem(args, 2);
    if(!callback) {
        UK_LOG_ERROR("Invalid callback for handler");
        return nullptr;
    }

    ::Unknown::registerEventHandler(type, handlerName_cStr, [=](Unknown::Event& evnt) {
        PyObject* args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyLong_FromLong(evnt.SDLCode));
        PyTuple_SetItem(args, 1, PyLong_FromLong(evnt.keyCode));
        PyTuple_SetItem(args, 2, PyLong_FromLong(evnt.keyState));

        if(!PyObject_CallObject(callback, args)) {
            UK_LOG_ERROR("Unable to call func");
            PyObject_Print(callback, stdout, Py_PRINT_RAW);
            PyErr_PrintEx(1);
        }
    });

    Py_RETURN_NONE;
}

PyObject* logMessage(PyObject* self, PyObject* args)
{
    int loglevelValue = PY_GET_LONG(args, 0);

    PyObject* message = PySequence_GetItem(args, 1);
    if(!message) {
        UK_LOG_ERROR("Invalid message");
        PyErr_PrintEx(1);
        return nullptr;
    }
    const char* message_cStr = PyUnicode_AsUTF8(message);

    Unknown::log(loglevelValue, message_cStr);

    Py_RETURN_NONE;
}

PyObject* createRawSprite(PyObject* self, PyObject* args)
{
    int typeValue = PY_GET_LONG(args, 0);

    PyObject* data = PY_GET_OBJ(args, 1);

    // All sprites have an x and a y coord

    int xValue = PY_GET_LONG(data, 0);

    int yValue = PY_GET_LONG(data, 1);

    PyObject* capsule = nullptr;

    if(typeValue == 0) // If is a regular sprite
    {
        Unknown::Sprite *sprite = new Unknown::Sprite(xValue, yValue);

        capsule = PyCapsule_New(sprite, NULL, rawImageDestructor);
    }

    if(typeValue == 1) // If is an image sprite
    {
        PyObject* img = PY_GET_OBJ(data, 2);

        Unknown::Graphics::Image* imgValue = (Unknown::Graphics::Image*)PyCapsule_GetPointer(img, NULL);

        Unknown::Graphics::ImageSprite *sprite = new Unknown::Graphics::ImageSprite(xValue, yValue, imgValue);

        capsule = PyCapsule_New(sprite, NULL, rawImageDestructor);
    }

    if(typeValue == 2) // If is an animated sprite
    {
        PyObject* animation = PY_GET_OBJ(data, 2);

        Unknown::Graphics::Animation* animationValue = (Unknown::Graphics::Animation*)PyCapsule_GetPointer(animation, NULL);

        Unknown::Graphics::AnimatedSprite *sprite = new Unknown::Graphics::AnimatedSprite(xValue, yValue, animationValue);

        capsule = PyCapsule_New(sprite, NULL, rawImageDestructor);
    }

    if(!capsule) {
        UK_LOG_ERROR("Unable to form capsule");
        PyErr_PrintEx(1);
        return nullptr;
    }

    return capsule;
}

template <class T>
T getObjectCapsule(PyObject* capsule) {
    return *((T*) PyCapsule_GetPointer(capsule, NULL));
}

#define PY_UNPACK_OBJ(T, args, index) getObjectCapsule<T>(PY_GET_OBJ(args, index))

PyObject* rawSpriteInterface(PyObject *self, PyObject *args) {
    auto sprite = PY_UNPACK_OBJ(Unknown::Sprite, args, 0);

    long functionInt = PY_GET_LONG(args, 1);

    PyObject* data = PySequence_GetItem(args, 2);

    if (functionInt == 1) { // Move
        int xSpeedValue = PY_GET_LONG(data, 0);
        int ySpeedValue = PY_GET_LONG(data, 1);

        sprite.move(xSpeedValue, ySpeedValue);
    }

    if(functionInt == 2) {// Render
        sprite.render();
    }

    Py_RETURN_NONE;
}

PyObject* getMousePos(PyObject *self, PyObject *args) {
    Unknown::Point<int> p = Unknown::getMouseLocation();
    PyObject* seq = PyTuple_Pack(2, PyLong_FromLong(p.x), PyLong_FromLong(p.y));

    return seq;
}

void Unknown::Python::Interpreter::loadScript(std::string name)
{
    //register a test method
    registerMethod("Unknown", "register_hook",             "Add a base hook",         registerHookHandler);
    registerMethod("Unknown", "create_raw_image",          "Create an image capsule", createRawImageHandler);
    registerMethod("Unknown", "render_raw_image",          "Render an image capsule", renderRawImageHandler);
    registerMethod("Unknown", "create_raw_timer",          "Create a timer capsule",  createRawTimer);
    registerMethod("Unknown", "timer_reset",               "Resets a timer capsule",  resetRawTimer);
    registerMethod("Unknown", "timer_isTickComplete",      "Checks a timer capsule",  checkRawTimer);
    registerMethod("Unknown", "event_register_handler",    "Register a key handler",  registerRawEventHandler);
    registerMethod("Unknown", "uk_log",                    "Print a string to stdout",logMessage);
    registerMethod("Unknown", "create_raw_sprite",         "Create a sprite capsule", createRawSprite);
    registerMethod("Unknown", "raw_sprite_interface", "Interface with a sprite capsule", rawSpriteInterface);
    registerMethod("Unknown", "get_mouse_pos",        "Get mouse position",              getMousePos);

    log(UK_LOG_LEVEL_INFO, concat("Loading script", name));

    PyObject* testModule = PyImport_ImportModule(name.c_str());
    checkError(testModule);
    PyObject* initFunction = PyObject_GetAttrString(testModule, "init");
    if(initFunction)
    {
        PyObject_CallObject(initFunction, NULL);
    }
}