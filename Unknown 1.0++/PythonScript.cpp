
#include "stdafx.h"
#include "PythonScript.h"
#include <Python.h>
#include "Log.h"
#include "Unknown.h"
#include <cstdio>
#include <frameobject.h>
#include "Loader.h"
#include "Image.h"
#include "Event/EventManager.h"
#include "Input/Mouse.h"

std::shared_ptr<Unknown::Python::Interpreter> Unknown::Python::instance;

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

std::shared_ptr<Unknown::Python::Interpreter> Unknown::Python::getInterpreter()
{
    if(instance == NULL)
    {
        instance = std::make_shared<Interpreter>();
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

PyObject* getModule(const std::string& name) {
    PyObject* modulePyString = PyUnicode_FromString(name.c_str());
    PyObject* module = PyImport_Import(modulePyString);
    Unknown::Python::getInterpreter()->checkError(module);
    return module;
}

void createMethod(std::string moduleName, PyObject* callable, std::string functionName)
{
    PyObject* module = getModule(moduleName);
    PyObject* originalDict = PyModule_GetDict(module);
    Unknown::Python::getInterpreter()->checkError(originalDict);
    PyDict_SetItemString(originalDict, functionName.c_str(), callable);
}

PyObject* Unknown::Python::Interpreter::getMethod(const std::string& method) {
    UK_LOG_INFO("Locating", method);
    auto moduleName = method.substr(0, method.find("."));
    auto methodName = method.substr(method.find(".") + 1, method.size());

    PyObject* module = getModule(moduleName);
    PyObject* dict = PyModule_GetDict(module);
    PyObject* callable = PyDict_GetItem(dict, PyUnicode_FromString(methodName.c_str()));
    return callable;
}

void Unknown::Python::Interpreter::callMethod(const std::string& methodName, PyObject* argsTuple) {
    PyObject* callable = getMethod(methodName);

    if(!callable) {
        UK_LOG_ERROR("Attempted to call invalid python method", methodName);
        return;
    }

    PyEval_CallObject(callable, argsTuple);
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
        UK_LOG_ERROR_VERBOSE("Invalid element at", pyFuncName, ":", ::Unknown::intToString(line));
        PyErr_PrintEx(1);
        return nullptr;
    }

    return element;
}

template <class T>
T* getObjectCapsule(PyObject* capsule, std::string name) {
    return (T*) PyCapsule_GetPointer(capsule, name.c_str());
}

#define MAKE_FUNC_MAPPING(name, desc, callback) registerMethod("Unknown", name, desc, callback);
#define PY_MAKE_UTF8(value) PyUnicode_FromString(value)
#define PY_MAKE_FLOAT(value) PyFloat_FromDouble(value)
#define PY_MAKE_LONG(value) PyLong_FromLong(value)
#define PY_MAKE_CAPSULE(value, name, callback)  PyCapsule_New(value, name, callback)

#define PY_UNPACK_OBJ(T, name, args, index) getObjectCapsule<T>(PY_GET_OBJ(args, index), name)
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

    std::unique_ptr<Unknown::Graphics::Image> image =  std::make_unique<::Unknown::Graphics::Image>(std::string(fileName_cStr));
    PyObject* capsule = PY_MAKE_CAPSULE(image.release(), "Image", [](PyObject* a){});

    if(!capsule) {
        UK_LOG_ERROR_VERBOSE("Unable to form capsule");
        PyErr_PrintEx(1);
        return nullptr;
    }

    return capsule;
}

PyObject* renderRawImageHandler(PyObject* self, PyObject* args)
{
    PyObject* dataTuple = PY_GET_OBJ(args, 1);

    int XCoord = PY_GET_LONG(dataTuple, 0);
    int YCoord = PY_GET_LONG(dataTuple, 1);
    int angle = PY_GET_LONG(dataTuple, 2);
    PyObject* clipTuple = PyTuple_GetItem(dataTuple, 3);

    Unknown::Graphics::Image* image = PY_UNPACK_OBJ(Unknown::Graphics::Image, "Image", args, 0);

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
    Unknown::Timer* timer = new Unknown::Timer((float)timeStep);

    PyObject* capsule = PY_MAKE_CAPSULE(timer, "Timer", [](PyObject* a){});

    if(!capsule) {
        UK_LOG_ERROR("Unable to form capsule");
        PyErr_PrintEx(1);
        return nullptr;
    }

    return capsule;
}

PyObject* resetRawTimer(PyObject* self, PyObject* args)
{
    Unknown::Timer* timer = PY_UNPACK_OBJ(Unknown::Timer, "Timer", args, 0);

    if(timer) {
        timer->resetTimer();
    }

    Py_RETURN_NONE;
}

PyObject* checkRawTimer(PyObject* self, PyObject* args)
{
    Unknown::Timer* timer = PY_UNPACK_OBJ(Unknown::Timer, "Timer", args, 0);

    if(timer) {
        if(timer->isTickComplete()) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
        }
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject* registerRawEventHandler(PyObject* self, PyObject* args)
{
    Unknown::EventType type = (Unknown::EventType)PY_GET_LONG(args, 0);

    const char* handlerName_cStr =  PY_GET_UTF8(args, 1);

    PyObject* callback = PY_GET_OBJ(args, 2);

    ::Unknown::registerEventHandler(type, handlerName_cStr, [=](Unknown::Event& evnt) {
        PyObject* args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyLong_FromLong(evnt.key.SDLCode));
        PyTuple_SetItem(args, 1, PyLong_FromLong(0)); //keycode
        PyTuple_SetItem(args, 2, PyLong_FromLong(evnt.key.keyState));

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

    const char* message_cStr = PY_GET_UTF8(args, 1);

    Unknown::log(loglevelValue, {message_cStr});

    Py_RETURN_NONE;
}

PyObject* createRawSprite(PyObject* self, PyObject* args)
{
	Py_RETURN_NONE;
//    int typeValue = PY_GET_LONG(args, 0);
//
//    PyObject* data = PY_GET_OBJ(args, 1);
//
//    // All sprites have an x and a y coord
//
//    int xValue = PY_GET_LONG(data, 0);
//
//    int yValue = PY_GET_LONG(data, 1);
//
//    PyObject* capsule = nullptr;
//
//    if(typeValue == 0) // If is a regular sprite
//    {
//        Unknown::Sprite *sprite = new Unknown::Sprite(xValue, yValue);
//
//        capsule = PY_MAKE_CAPSULE(sprite, "Sprite", [](PyObject* a){});
//    }
//
//    if(typeValue == 1) // If is an image sprite
//    {
//        Unknown::Graphics::Image* imgValue = PY_UNPACK_OBJ(Unknown::Graphics::Image, "Image", data, 2);
//
//        Unknown::Graphics::ImageSprite* sprite = new Unknown::Graphics::ImageSprite(xValue, yValue, imgValue);
//
//        capsule = PY_MAKE_CAPSULE(sprite, "Sprite", [](PyObject* a){});
//    }
//
//    if(typeValue == 2) // If is an animated sprite
//    {
//        Unknown::Graphics::Animation* animationValue = PY_UNPACK_OBJ(Unknown::Graphics::Animation, "Animation", data, 2);
//
//        Unknown::Graphics::AnimatedSprite *sprite = new Unknown::Graphics::AnimatedSprite(xValue, yValue, animationValue);
//
//        capsule = PY_MAKE_CAPSULE(sprite, "Sprite", [](PyObject* a){});
//    }
//
//    if(!capsule) {
//        UK_LOG_ERROR_VERBOSE("Unable to form capsule");
//        PyErr_PrintEx(1);
//        return nullptr;
//    }
//
//    return capsule;
}

PyObject* getMousePos(PyObject *self, PyObject *args) {
    Unknown::Point<int> p = Unknown::getMouseLocation();
    PyObject* seq = PyTuple_Pack(2, PyLong_FromLong(p.x), PyLong_FromLong(p.y));

    return seq;
}

PyObject* rawSpriteCall(PyObject* self, PyObject* args) {
//    Unknown::Sprite* spr = PY_UNPACK_OBJ(Unknown::Sprite, "Sprite", args, 0);
//    int functionID = PY_GET_LONG(args, 1);
//    PyObject* data = PY_GET_OBJ(args, 2);
//
//    switch (functionID)
//    {
//        case 0: spr->render();break;
//        case 1: spr->init();break;
//        case 2: spr->move(PY_GET_LONG(data, 0), PY_GET_LONG(data, 1));break;
//        case 3:
//            return PY_MAKE_CAPSULE(spr->clone(), "Sprite", [](PyObject* sprite) {
//                Unknown::Sprite* s = getObjectCapsule<Unknown::Sprite>(sprite, "Sprite");
//                // TODO:
//                UK_LOG_INFO("Cleaned up sprite");
//            });
//        case 4:
//            return PY_MAKE_LONG(spr->getAngle());
//        case 5: spr->setAngle(PY_GET_FLOAT(data, 0));break;
//        //case 6: return PY_MAKE_CAPSULE(&spr->bounds, "Bounds", [](PyObject* bound){});
//        case 7: return PY_MAKE_CAPSULE(&spr->direction, "Direction", [](PyObject* dir){});
//        case 8: return PY_MAKE_CAPSULE(&spr->location, "Loc", [](PyObject* a){});
//        //case 9: spr->bounds = *PY_UNPACK_OBJ(Unknown::AABB, "Sprite", data, 0);break;
//        case 10: spr->direction = *PY_UNPACK_OBJ(Unknown::Vector, "Vector", data, 0);break;
//        case 11: spr->location = *PY_UNPACK_OBJ(Unknown::Point<double>, "Point", data, 0);break;
//
//    }
    Py_RETURN_NONE;
}

PyObject* rawVectorInterface(PyObject* self, PyObject* args) {
//    int functionID = PY_GET_LONG(args, 1);
//    PyObject* data = PY_GET_OBJ(args, 2);
//
//    if (functionID == 0) {
//        return PY_MAKE_CAPSULE(new Unknown::Vector(PY_GET_FLOAT(data, 0), PY_GET_FLOAT(data, 1)), "Vector", [](PyObject* a){}); //TODO
//    }
//
//    Unknown::Vector* vector = PY_UNPACK_OBJ(Unknown::Vector, "Vector", args, 0);
//
//    switch (functionID) {
//        case 1:
//        {
//            return PY_MAKE_FLOAT(vector->getLength());
//        }
//        case 2:
//        {
//            UK_LOG_ERROR("Normalisation of vectors not impl");
//            return PY_GET_OBJ(args, 0);
//        }
//        case 3:
//        {
//            PyObject* args_ = PyTuple_New(2);
//            PyTuple_SetItem(args_, 0, PY_MAKE_FLOAT(vector->x));
//            PyTuple_SetItem(args_, 1, PY_MAKE_FLOAT(vector->y));
//            return args_;
//        }
//    }

    Py_RETURN_NONE;
}

#include "SharedVariable.h"

PyObject* getSharedValue(PyObject* self, PyObject* args) {
    const char* name_c = PY_GET_UTF8(args, 0);
    std::string name(name_c);

    auto& variablelookup = ::Unknown::getUnknown().variablelookup;

    if(variablelookup.find(name) != variablelookup.end()) {
        Unknown::SharedVariable* x = variablelookup[name];
        auto& type = x->type();

        if(type == typeid(std::string)) {
            return PY_MAKE_UTF8(x->getValue<std::string>().c_str());
        }

        if(type == typeid(double)) {
            return PY_MAKE_FLOAT(x->getValue<double>());
        }
    } else {
        printf("[PY] Unknown variable: %s\n", name_c);
    }
    Py_RETURN_NONE;
}

PyObject* setSharedValue(PyObject* self, PyObject* args) {
    const char* name_c = PY_GET_UTF8(args, 0);
    PyObject* data = PY_GET_OBJ(args, 1);
    std::string name(name_c);

    auto& variablelookup = ::Unknown::getUnknown().variablelookup;

    if(variablelookup.find(name) != variablelookup.end()) {
        Unknown::SharedVariable* x = variablelookup[name];

        if(PyBool_Check(data)) {
            bool b = PY_GET_LONG(args, 1);
            *x = b;
        } else {
            if (PyFloat_Check(data)) {
                double in = PY_GET_FLOAT(args, 1);
                *x = in;
            }
        }

        if(PyUnicode_Check(data)) {
            const char* str = PY_GET_UTF8(args, 1);
            *x = std::string(str);
        }
    } else {
        printf("[PY] Unknown variable: %s\n", name_c);
    }
    Py_RETURN_NONE;
}

//TODO: test and add changes from reflex to repo
PyObject* makeObject(PyObject* self, PyObject* args) {
    PyObject* obj = PY_GET_OBJ(args, 0);

    printf("%s\n", PyUnicode_AsUTF8(PyObject_Str(args)));
    printf("%s\n", PyUnicode_AsUTF8(PyObject_Str(self)));

   // PyObject* name = PyDict_GetItemString(obj, "__UK_name");
   // UK_LOG_INFO("Created obj:", PyUnicode_AsUTF8(name));


    //auto type = rttr::type::get_by_name(name);

    //UK_LOG_INFO("Creating type", name);

//    if(type.is_valid()) {
//        UK_LOG_INFO("Valid type");
//    }

    if(!obj)
        printf("Invalid class\n");

    PyDict_SetItemString(obj, "Test", PyLong_FromDouble(1.0));

    return obj;
//    std::string name = std::string(PY_GET_UTF8(args, 0));
//    auto m1 = Reflex::getInstance().m1;
//
//    auto tmp = (*Reflex::getInstance().m1)[name];
//    void* ptr = tmp->newRawInstance();
//
//    UK_LOG_INFO("Created capsule of type", name, "with ptr:", Unknown::intToString((long int)ptr));
//
//    return PY_MAKE_CAPSULE(ptr, name.c_str(), [](PyObject* p){});
}

PyObject* setField(PyObject* self, PyObject* args) {
//    std::string classname = std::string(PY_GET_UTF8(args, 0));
//    std::string fieldName = std::string(PY_GET_UTF8(args, 1));
//    void* capsule = PyCapsule_GetPointer(PyTuple_GetItem(args, 2), classname.c_str());
//    PyObject* value = PyTuple_GetItem(args, 3);
//
//    if(!capsule) {
//        UK_LOG_ERROR_VERBOSE("Attempt to access field:", fieldName, "on null reference to", classname);
//        Py_RETURN_NONE;
//    }
//
//    std::shared_ptr<ClassInfoBase> classInfo = getClassInfo(classname);
//
//    auto field = classInfo->fields[fieldName];
//    std::type_index fieldType = field->getType(capsule);
//
//    if(fieldType == typeid(double)) {
//        double d = PyFloat_AsDouble(value);
//        printf("Set %s.%s to %lf\n", classname.c_str(), fieldName.c_str(), d);
//
//        field->setValue<decltype(d)>(capsule, d);
//    }

    Py_RETURN_NONE;
}

const rttr::type* currentType = nullptr;

#include "rttr/type.h"

PyObject* cstr(PyObject* self, PyObject* args) {
    // Self is null, args is empty
    printf("cstr args - %s\n", PyUnicode_AsUTF8(PyObject_Str(args)));

    UK_LOG_INFO("Creating obj");


    // Get the type for this virtual class
    rttr::type type = rttr::type::get_by_name(PyUnicode_AsUTF8(PyDict_GetItemString(self, "__UK_TYPE_NAME")));

    UK_LOG_INFO("Type:", type.get_name().to_string());


    // Create an instance of the class
    //TODO: handle different args other than empty
    rttr::variant instance = (*type.get_constructors().begin()).invoke();

    // Store in capsule
    PyDict_SetItemString(self, "__UK_CAPSULE", PyCapsule_New(instance.get_value<void*>(), type.get_name().to_string().c_str(), [](PyObject* d){
        printf("Destroying something\n");
    }));

    //TODO: look in mkobj and change to set/get attr
    // Update the properties with the ones from the class
    for(auto& field : type.get_properties()) {
        UK_LOG_INFO("Adding prop", field.get_name().to_string());
        PyDict_SetItemString(self, field.get_name().to_string().c_str(), PyLong_FromLong(field.get_value(instance).get_value<int>()));
    }

    printf("%s\n", PyUnicode_AsUTF8(PyObject_Str(self)));

    Py_RETURN_NONE;
}

PyObject* new_(PyObject* self, PyObject* args) {
    auto type = PY_GET_OBJ(args, 0);

    auto obj = PyObject_NEW(PyObject, type->ob_type);

    printf("new self - %s\n", PyUnicode_AsUTF8(PyObject_Str(self)));
    printf("new args - %s\n", PyUnicode_AsUTF8(PyObject_Str(args)));

    std::cout << std::endl;

    return obj;
}

PyObject* mkobj(PyObject* self, PyObject* args) {
    PyObject *obj = PY_GET_OBJ(args, 0);

    if(!currentType) {
        printf("Err\n");
        return obj;
    }
    UK_LOG_INFO("Creating type", currentType->get_name().to_string());

    // Add dummy fields
    for(auto& field : (*currentType).get_properties()) {
        UK_LOG_INFO("Adding prop", field.get_name().to_string());
        PyDict_SetItemString(obj, field.get_name().to_string().c_str(), Py_None);
    }

    // Add fake constructor
    PyMethodDef* cback = generatePyMethodDef("__init__", cstr, "");
    /**
     * TODO: this is not a bug, but very important to acknowledge
     * The constructor of each generated obj is **NOT** a member of the class that it constructs
     * it is instead a member of a dictionary, not an __ELEMENT__ but a __MEMBER__ of the dictionary instance
     */
    // TODO: this is a major hack, not a bug
    PyObject* callable = PyCFunction_NewEx(cback, obj, PyUnicode_FromString((*currentType).get_name().to_string().c_str()));
    PyDict_SetItemString(obj, "__init__", callable);


    PyMethodDef* newback = generatePyMethodDef("__new__", new_, "");
    PyObject* newcallable = PyCFunction_NewEx(newback, obj, PyUnicode_FromString((*currentType).get_name().to_string().c_str()));
    PyDict_SetItemString(obj, "__new__", newcallable);

    // Store enough info to recover type later (typename)
    PyDict_SetItemString(obj, "__UK_TYPE_NAME", PyUnicode_FromString(currentType->get_name().to_string().c_str()));

    for(auto& method : (*currentType).get_methods()) {
        UK_LOG_INFO("Adding method", method.get_name().to_string());
    }

    //tODO: replace the get/set attr func instead of copying state of values

    UK_LOG_INFO("-------");

    return args;
}

void Unknown::Python::Interpreter::loadScript(std::string name)
{
//    for(auto& type : rttr::type::get_types()) {
//        if(type.is_class()) {
//            PyObject* baseClasses = PyTuple_New(0);
//            PyObject* methodDict = PyDict_New();
//
//           // PyObject* classDefinition = PyObject_CallFunctionObjArgs((PyObject*) &PyType_Type, type.get_name().to_string().c_str(), baseClasses, methodDict);
//
//            PyObject *c = PyObject_CallFunctionObjArgs((PyObject*)&PyType_Type, PyBytes_FromString("Test"), PyTuple_New(0), methodDict, NULL);
//
//            if(!c)
//                printf("Failed to generate wrapper for class %s\n", type.get_name().to_string().c_str());
//
//            Py_CLEAR(baseClasses);
//            Py_CLEAR(methodDict);
//        }
//    }

//    MAKE_FUNC_MAPPING("raw_vector_interface", "Call a function on a vector", rawVectorInterface);
//    MAKE_FUNC_MAPPING("raw_sprite_interface", "Call a function on a sprite", rawSpriteCall);
//    registerMethod("Unknown", "register_hook", "Add a base hook", registerHookHandler);
//    registerMethod("Unknown", "create_raw_image", "Create an image capsule", createRawImageHandler);
//    registerMethod("Unknown", "render_raw_image", "Render an image capsule", renderRawImageHandler);
//    registerMethod("Unknown", "create_raw_timer", "Create a timer capsule", createRawTimer);
//    registerMethod("Unknown", "timer_reset", "Resets a timer capsule", resetRawTimer);
//    registerMethod("Unknown", "timer_isTickComplete", "Checks a timer capsule", checkRawTimer);
//    registerMethod("Unknown", "event_register_handler", "Register a key handler", registerRawEventHandler);
//    registerMethod("Unknown", "uk_log", "Print a string to stdout", logMessage);
//    registerMethod("Unknown", "create_raw_sprite", "Create a sprite capsule", createRawSprite);
//    registerMethod("Unknown", "get_mouse_pos", "Get mouse position", getMousePos);
//    registerMethod("Unknown", "raw_get_shared", "Get shared value", getSharedValue);
//    registerMethod("Unknown", "raw_set_shared", "Set shared value", setSharedValue);
//    MAKE_FUNC_MAPPING("uk_make_obj", "Create an instance of a class", makeObject);
//    MAKE_FUNC_MAPPING("uk_set_field", "Set a field in an object", setField);
//    //TODO: getfield, callfunc


    UK_LOG_INFO("Loading script", name);

    PyObject *testModule = PyImport_ImportModule(name.c_str());
    checkError(testModule);
    PyObject *testDict = PyModule_GetDict(testModule);

    // Add the new class to the module

    // The defintion for the mkobj func
    PyMethodDef* cback = generatePyMethodDef("A", mkobj, "");
    // The pycfunction for the mkobj func
    PyObject* callable = PyCFunction_NewEx(cback, (PyObject*)NULL, PyUnicode_FromString("Unknown"));

    // The types module
    PyObject* typesMod = PyImport_AddModule("types");

    if(!typesMod)
        printf("Failed to load types module\n");

    // Get dir(typesMod)
    PyObject* typesDict = PyModule_GetDict(typesMod);

    if(!typesDict)
        printf("Typesdict bad\n");

    // Get typesMod["new_class"]
    PyObject* new_classFunc = PyDict_GetItemString(typesDict, "new_class");

    if(!new_classFunc)
        printf("new_class bad\n");

    // For each of the types
    for(auto& type : rttr::type::get_types()) {
        if(type.is_class()) {
            UK_LOG_INFO("Adding dypy class", type.get_name().to_string());

            PyObject* baseClasses = PyTuple_New(0);
            PyObject* internal = PyDict_New();

            currentType = &type;

            PyObject *clz = PyObject_CallFunctionObjArgs(new_classFunc,
                                                         PyUnicode_FromString(type.get_name().to_string().c_str()),
                                                         baseClasses, internal, callable, NULL);

            PyDict_SetItemString(testDict, type.get_name().to_string().c_str(), clz);
        }
    }


    //PyObject* originalDict = PyModule_GetDict(testModule);
    //PyDict_SetItemString(originalDict, "TestMod", mod);
//
//
//    printf("Defining types\n");
//    PyObject* baseClasses = PyTuple_New(0);
//    PyObject* methodDict = PyDict_New();
//
//    PyRun_SimpleString()
//
//    PyObject* c = PyObject_CallFunctionObjArgs(PyMethod_PyImport_Import("types"), )
////    PyObject *c = PyObject_CallFunctionObjArgs((PyObject*)&PyType_Type, PyUnicode_FromString("Test1"), baseClasses, methodDict, NULL);
////
////    if(!c)
////        printf("Failed to generate wrapper for class\n");
//
//    PyModule_Add(testModule, "Test1", c);
//    PyModule_add
//
//    Py_CLEAR(baseClasses);
//    Py_CLEAR(methodDict);




    if (PyObject_HasAttrString(testModule, "init"))
    {
        PyObject *initFunction = PyObject_GetAttrString(testModule, "init");
        if (initFunction)
        {
            checkError(PyObject_CallObject(initFunction, NULL));
        }
    }
}