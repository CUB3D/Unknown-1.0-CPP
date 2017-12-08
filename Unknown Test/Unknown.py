from collections import namedtuple

UK_UPDATE = 1
UK_RENDER = 0

rect = namedtuple("rect", "x y width height")

# Externally defined functions START
# Core
def register_hook(type, callback):
    pass

# Images
def create_raw_image(fileName):
    return 0
def render_raw_image(capsule, data):
    pass

# END

def register_update_handler(callback):
    register_hook(UK_UPDATE, callback)

def register_render_handler(callback):
    register_hook(UK_RENDER, callback)


class Image:
    __capsule = None
    def __init__(self, fileName):
        self.__capsule = create_raw_image(fileName)
    def render(self, x, y, angle=0, rect=None):
        render_raw_image(self.__capsule, (x, y, angle, rect))
