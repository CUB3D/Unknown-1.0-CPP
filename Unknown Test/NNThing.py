from Unknown import *
import math

import tensorflow as tf

def make_net():
    global inp_x, train, sess, predictions, loss
    inp_x = tf.placeholder(tf.float32, shape=[1, 1])
    expected = tf.constant([[0]], dtype=tf.float32)

    linear_model = tf.layers.Dense(units=1)
    predictions = linear_model(inp_x)
    sess = tf.Session()
    init = tf.global_variables_initializer()
    sess.run(init)

    loss = tf.losses.mean_squared_error(labels=expected, predictions=predictions)
    optimiser = tf.train.GradientDescentOptimizer(0.0001)
    train = optimiser.minimize(loss)

    for x in range(1000):
        sess.run((train, loss), {inp_x: [[0]]})

make_net()

img = Image("Player.png")

spr = ImageSprite(0, 0, img)

timer = Timer(0.2)

kb_left = Keybind(0x40000050, "left")
kb_right = Keybind(0x4000004F, "right")
kb_up = Keybind(0x40000052, "up")
kb_down = Keybind(0x40000051, "down")
x = 0

PLAYER_SPEED_HORIZONTAL = 4
PLAYER_SPEED_VERTICAL = 4


#TODO: Need a way to set direction vector, maybe add some option to the json entities to enable a force_(1,1) dir vector mode. Add add functions to call loader funcs from py


def render():
    spr.render()


def distance_from_mouse():
    # TODO: named tuple
    mouseX = get_mouse_pos()[0]
    distance = math.sqrt((x - mouseX)**2)
    return 1024 / distance


def update():
    if kb_left.isPressed: # Left
        spr.move(-PLAYER_SPEED_HORIZONTAL, 0)
    if kb_right.isPressed: # Right
        spr.move(PLAYER_SPEED_HORIZONTAL, 0)
    if kb_down.isPressed: # Down
        spr.move(0, PLAYER_SPEED_VERTICAL)
    if kb_up.isPressed: # Up
        spr.move(0, -PLAYER_SPEED_VERTICAL)

    mousePos = distance_from_mouse()
    if mousePos == 0:
        return
    _, deltaLoss = sess.run((train, loss), {inp_x: [[mousePos]]})
    nextPrediction = 1/sess.run(predictions, {inp_x: [[mousePos]]})[0][0]
    if not math.isfinite(nextPrediction):
        make_net()
    global x
    print(f"{deltaLoss}, {nextPrediction}, {mousePos}, {x}")
    spr.move(nextPrediction, 0)
    x += nextPrediction



def init():
    print("Hello, World!")
    #create_raw_sprite(spr, ())
    register_render_handler(render)
    register_update_handler(update)