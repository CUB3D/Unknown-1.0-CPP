from Unknown import *

img = Image("Player.png")
x = 0
y = 0

def render():
    img.render(x, y)

def update():
    global x
    global y
    x += 20
    if x >= 200:
        y+= 4
        x = 0


def init():
    print("Hello, World!")
    register_render_handler(render)
    register_update_handler(update)
