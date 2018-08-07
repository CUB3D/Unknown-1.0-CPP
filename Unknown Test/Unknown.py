from collections import namedtuple
import functools

#DONE: images, hooks, logging, timers, keybinds

UK_UPDATE = 1
UK_RENDER = 0

ET_MOUSEBUTTON = 0
ET_KEYPRESS = 1
ET_WINDOW_RESIZE = 2

LL_INFO = 0
LL_WARN = 1
LL_ERROR = 2

ST_STD = 0
ST_IMAGE = 1
ST_ANIMATION = 2


rect = namedtuple("rect", "x y width height")
event = namedtuple("event", "SDLCode keycode keyState")


# Core
def register_hook(type, callback):
    pass

def uk_make_obj(name):
    pass

def uk_set_field(classname, fieldname, capsule, val):
    pass


# Images
def create_raw_image(fileName):
    return 0


def render_raw_image(capsule, data):
    pass
# END


# Timer
def create_raw_timer(time):
    return 0


def timer_reset(capsule):
    pass


def timer_isTickComplete(capsule):
    pass
# END


# Handlers
def register_update_handler(callback):
    register_hook(UK_UPDATE, callback)


def register_render_handler(callback):
    register_hook(UK_RENDER, callback)


def register_keyboard_handler(callback, name=None):
    if name is None:
        name = callback.__name__
    event_register_handler(ET_KEYPRESS, name, lambda SDLCode,keyCode,keyState: callback(event(SDLCode,keyCode,keyState)))


def event_register_handler(type, name, callback):
    pass
# END


# Logging
def uk_log(loglevel, message):
    pass


def print(*args, sep=' ', end='\n', file=None):
    output = sep.join([str(x) for x in args]) + end
    uk_log(LL_INFO, "[PY] {}".format(output))
# END


# Sprites
def create_raw_sprite(type, data):
    return 0


def raw_sprite_interface(sprite, ID, args):
    pass
# END


# Mouse
def get_mouse_pos():
    return (0, 0)
# END


# Variables
def raw_get_shared(name):
    pass

def raw_set_shared(name, value):
    pass
# END

# global variables
class _sharedVars:
    def __getattr__(self, item):
        return raw_get_shared(item)

    def __setattr__(self, key, value):
        raw_set_shared(key, value)



sharedVars = _sharedVars()
# END

# Vector
def raw_vector_interface(capsule, ID, args):
    return 0
# END

# Actual functional classes
class Keybind:
    isPressed = False
    keyCode = 0

    def __init__(self, keycode, name):
        register_keyboard_handler(self.onKeyEvent, name)
        self.keyCode = keycode

    def onKeyEvent(self, evnt):
        if evnt.SDLCode == self.keyCode:
            self.isPressed = evnt.keyState


# Dummy capsule caller classes
class Image:
    __capsule = None

    def __init__(self, fileName):
        self.__capsule = create_raw_image(fileName)

    def render(self, x, y, angle=0, rect=None):
        render_raw_image(self.__capsule, (x, y, angle, rect))


class Timer:
    __capsule = None

    def __init__(self, time=1):
        self.__capsule = create_raw_timer(time)

    def isTickComplete(self):
        return timer_isTickComplete(self.__capsule)

    def resetTimer(self):
        timer_reset(self.__capsule)


class Sprite:
    _capsule = None
    _interface = None

    def __init__(self, x, y, noCapsuleGen=False):
        if not noCapsuleGen:
            self._capsule = create_raw_sprite(ST_STD, (x, y))
        self._interface = functools.partial(raw_sprite_interface, self._capsule)

    def move(self, speedX, speedY):
        self._interface(2, (speedX, speedY))

    def render(self):
        self._interface(0, ())

    def __setattr__(self, key, value):
        if key == "direction":
            self._interface(10, (value._capsule,))
        else:
            self.__dict__[key] = value


class ImageSprite(Sprite):

    def __init__(self, x, y, image):
        self._capsule = create_raw_sprite(ST_IMAGE, (x, y, getattr(image, "_Image__capsule")))
        super().__init__(0, 0, noCapsuleGen=True)


class AnimatedSprite(Sprite):

    def __init__(self, x, y, animation):
        super()._capsule = create_raw_sprite(ST_ANIMATION, (x, y, animation))
        super().__init__(0, 0, noCapsuleGen=True)


"""class Vector:
    _capsule = None
    __interface = None

    def __init__(self, x=0, y=0):
        self._capsule = raw_vector_interface(None, 0, (float(x), float(y)))
        self.__interface = functools.partial(raw_vector_interface, self._capsule)

    def getLength(self):
        return self.__interface(1, ())

    def normalise(self):
        return self.__interface(2, ())

    def getPosition(self):
        return self.__interface(3, ())

    def __getattr__(self, item):
        if item == "x":
            return self.getPosition()[0]
        if item == "y":
            return self.getPosition()[1]

    def __mul__(self, other):
        return self

    def __add__(self, other):
        return self
"""

class Vector:
    _capsule = None
    def __init__(self):
        self.__dict__["_capsule"] = uk_make_obj("Vector")

    def __setattr__(self, key, value):
        if key == "_capsule":
            super().__setattr__(key, value)
        uk_set_field("Vector", key, self._capsule, value)


