#------------frog_found.py-----------------------------------------------------#
#
# Purpose: This file randomly generates numbers and checks to see if those
#          numbers are under the curve for a simple exponential decay model.
#          The output of this file is a simple double that represents the age
#          of a frog to be used in this week's homework assignment.
#
# I believe this assignment should be significantly easier than the previous 
# one, even if the system is somewhat more difficult to describe.
#
#------------------------------------------------------------------------------#

# First, let's import the appropriate functions. 

from random import random
from math import exp

# Now let's define the function to be read in.
def find_frog():

    # We will create two random variables, x and y and read those in to the 
    # exponential function. If the random y number is under the exponential 
    # curve, then  we output the year. Otherwise, we use a while loop to keep
    # searching for an appropriate value.

    # first, we need to initialize the "end flag" variable:
    end = 0

    # Now for the while loop!
    while end != 1:

        # The random value is generated between 0 and 1, so let's multiply that
        # number by the maximum number we expect to see. In this case, 5 for x
        # and 100 for y.
        rand_x = random() * 5
        rand_y = random() * 100

        # This is a bit of tricky logic. We generated two random variables a
        # second ago. Now we put the x value into our exponential and ask 
        # whether the y value is also within the exponential. If it is, we flip
        # the end flag and end the loop. Otherwise, we just keep going by 
        # picking other random numbers to test.
        if rand_y < 100*exp(-1 * rand_x):
            rand_num = rand_x
            end += 1
    return rand_num

# The following is a long comment. Delete the 3 apostrophes to use this part of
# the code. It will generate 100 random numbers and output them to your 
# terminal. Make sure to recomment this part out after using it, though.

'''
for i in range(0,100):
    rand = find_frog()
    print(rand)
'''
