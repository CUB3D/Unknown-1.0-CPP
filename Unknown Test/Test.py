from Unknown import *

def onPlayer2Collide(colliding):
    sharedVars.p2onGround = colliding

def onPlayer1Collide(colliding):
    sharedVars.p1onGround = colliding


v = Vector()
#TODO: this crashes on python 3.7, works on 3.6
#v.x = 10

# swap the ongrounds so that one player can only jump while the other is on the ground ????


