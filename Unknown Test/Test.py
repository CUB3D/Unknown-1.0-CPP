from Unknown import *

img = Image("Player.png")

spr = ImageSprite(0, 0, img)
direction = Vector(1, 1)
print(direction.getPosition()[0])

kb_left = Keybind(0x40000050, "left")
kb_right = Keybind(0x4000004F, "right")
kb_up = Keybind(0x40000052, "up")
kb_down = Keybind(0x40000051, "down")

PLAYER_SPEED_HORIZONTAL = 4
PLAYER_SPEED_VERTICAL = 4

def hello():
    print("Hello, World")


def render():
    pass
    #spr.render()


def update():
    if kb_left.isPressed: # Left
        spr.move(-PLAYER_SPEED_HORIZONTAL, 0)
    if kb_right.isPressed: # Right
        spr.move(PLAYER_SPEED_HORIZONTAL, 0)
    if kb_down.isPressed: # Down
        spr.move(0, PLAYER_SPEED_VERTICAL)
    if kb_up.isPressed: # Up
        spr.move(0, -PLAYER_SPEED_VERTICAL)


register_render_handler(render)
register_update_handler(update)
