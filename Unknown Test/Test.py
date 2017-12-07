from Unknown import *

def update():
    print("Update")

def render():
    print("Render")

def init():
    print("Hello, World!")
    register_update_handler(update)
    register_render_handler(render)
