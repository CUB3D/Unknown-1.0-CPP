from collections import namedtuple

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


def print(*args):
    uk_log(LL_INFO, "[PY] {}".format(" ".join(args)))
# END


# Sprites
def create_raw_sprite(type, data):
    return 0

def raw_sprite_interface(sprite, ID, args):
    pass


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

    def __init__(self, x, y, noCapsuleGen=False):
        if not noCapsuleGen:
            self._capsule = create_raw_sprite(ST_STD, (x, y))

    def move(self, speedX, speedY):
        raw_sprite_interface(self._capsule, 1, (speedX, speedY))

    def render(self):
        raw_sprite_interface(self._capsule, 2, ())


class ImageSprite(Sprite):

    def __init__(self, x, y, image):
        super().__init__(0, 0, noCapsuleGen=True)
        self._capsule = create_raw_sprite(ST_IMAGE, (x, y, getattr(image, "_Image__capsule")))


class AnimatedSprite(Sprite):

    def __init__(self, x, y, animation):
        super().__init__(0, 0, noCapsuleGen=True)
        super()._capsule = create_raw_sprite(ST_ANIMATION, (x, y, animation))

