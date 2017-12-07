UK_UPDATE = 0
UK_RENDER = 1

def register_hook(type, callback):
    pass

def register_update_handler(callback):
    register_hook(UK_RENDER, callback)

def register_render_handler(callback):
    register_hook(UK_UPDATE, callback)
