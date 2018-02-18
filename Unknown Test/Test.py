from Unknown import *

img = Image("Player.png")

spr = ImageSprite(0, 0, img)

timer = Timer(0.2)

kb_left = Keybind(0x40000050, "left")
kb_right = Keybind(0x4000004F, "right")
kb_up = Keybind(0x40000052, "up")
kb_down = Keybind(0x40000051, "down")

PLAYER_SPEED_HORIZONTAL = 4
PLAYER_SPEED_VERTICAL = 4

#TODO: Need a way to set direction vector

def render():
    spr.render()

def update():
    if kb_left.isPressed: # Left
        spr.move(-PLAYER_SPEED_HORIZONTAL, 0)
    if kb_right.isPressed: # Right
        spr.move(PLAYER_SPEED_HORIZONTAL, 0)
    if kb_down.isPressed: # Down
        spr.move(0, PLAYER_SPEED_VERTICAL)
    if kb_up.isPressed: # Up
        spr.move(0, -PLAYER_SPEED_VERTICAL)

def onKeyboardEvent(keyData):
    pass




def init():
    print("Hello, World!")
    register_render_handler(render)
    register_update_handler(update)
    # event_register_handler(1, "Test", onKeyboardEvent)
    register_keyboard_handler(onKeyboardEvent)
