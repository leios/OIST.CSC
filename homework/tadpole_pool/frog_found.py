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
from random import random
from math import exp

def find_frog():

    end = 0
    while end != 1:
        rand_x = random() * 2.5
        rand_y = random() * 100
        if rand_y < 100*exp(-1 * rand_x):
            rand_num = rand_x
            end += 1
    return rand_num

rand = find_frog()
print(rand)
