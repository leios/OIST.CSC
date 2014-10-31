#-------------falling_ball.py--------------------------------------------------#
#
# This is the first homework assignment with bonus
# 
# Purpose: To find the time it would take for a ball to hit the ground after 
#          Being dropped from a height of 5 meters
#
# This might have been a bit of a challenging first question
#
# This is the second (more or less intuitive) method. It works like so:
#    Rather than calculating the change in position each time while taking into
#    account the change in velocity, we instead query the change in time due to
#    just the acceleration formula. The idea is that at some given timestep,
#    we can find an analytical solution for time (when given position). We just
#    need to find what that time is. So let's try all of them starting with 0,
#    and that time upwards with some small timestep (0.01, here). 
#
#    This provides a much shorter code, but it makes less physical sense.
#
#------------------------------------------------------------------------------#

# First, let's initialize some variable we will know we will need:
# Note: the time_step can be set to anything you want. The smaller, the better!

t = 0
init_pos = 5
time_step = 0.01

# Let me explain the next parameter. We do not care about the ball's position, 
# Instead we care about the end result of the previous queried position and 
# whether that result was less than 0. If it was, then we take that time. For 
# the definition, it doesn't matter what we define q_p_ball as, so long as it is
# greater than 0. It will be redefined in the loop.

q_p_ball = 10

# Now for the wile loop I talked about in lecture
while q_p_ball > 0:

    # First, let's calculate our change in position using only the acceleration
    # formula. Note that we hardcode the initial position here because we do not
    # care about the changing position, just the changing time.

    p_ball = init_pos - (0.5*10*t*t)

    # and now... let's update our time variable

    t = t + time_step

    # ... and redefine q_p_ball before going back to the top of the loop.

    q_p_ball = p_ball

# Now that we are out of the loop, let's print the time!

print(t - time_step)
