#-------------falling_ball.py--------------------------------------------------#
#
# This is the first homework assignment with bonus
# 
# Purpose: To find the time it would take for a ball to hit the ground after 
#          Being dropped from a height of 5 meters
#
# This might have been a bit of a challenging first question
#
#------------------------------------------------------------------------------#

# First, let's initialize some variable we will know we will need:
# Note: the time_step can be set to anything you want. The smaller, the better!

t = 0
p_ball = 5
vel = 0
time_step = 0.01

# Now for the wile loop I talked about in lecture
while p_ball > 0:

    # First, let's calculate our change in position using only the kinematic
    # equation. Note: For a rough approximation, the velocity can be ignored.
    # Because I did not want to complicate things, I did not have the velocity
    # in the e-mail I initially sent you and instead offered adding in the 
    # velocity as bonus

    p_ball = p_ball - (vel*time_step) - (0.5*10*time_step*time_step)

    # Now let's update our velocity, which depends on acceleration    

    vel = vel + 10*time_step

    # and finally, let's update our time variable

    t = t + time_step

# Now that we are out of the loop, let's print the time!

print(t - time_step)
