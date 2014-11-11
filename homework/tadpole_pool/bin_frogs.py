#-------------bin_frogs.py-----------------------------------------------------#
#
# Purpose: To place frogs of all different ages into bins according to their 
#          age. This is a homework assignment for our python class
#
# Method: I will use a for loop to gra 100 frogs, call frog_found.py to 
#         generate the necessary random age, and then keep track of all the 
#         frog's ages. It should be similar to what we did in class or the 
#         cat boxing example.
#
#------------------------------------------------------------------------------#

# Let's go ahead and import all the functions from our frog_found file.
# Of course, there is only one function, so if you want to be more explicit, go
# ahead and call the function inside frog_found.py, "find_frog". 

from frog_found import *

# Now we need to define our variables. Let's create a bin for each frog year:

y_1 = y_2 = y_3 = y_4 = y_5 = 0

# Now let's pull 100 frogs and use the frog_find function from before.
# The easiest way to do this is with a for loop.

for i in range(0,100):

    # First, lets call our function from the other file

    frog = find_frog()

    # Now, depending on what that frog value is, we will place it in the
    # appropriate bin. IT'S IF STATEMENT TIME! 
    # ...
    # That sounded better in my head.

    if frog < 1:
        y_1 += 1

    elif frog >=1 and frog < 2:
        y_2 += 1

    elif frog >=2 and frog < 3:
        y_3 += 1

    elif frog >=3 and frog < 4:
        y_4 += 1

    else:
        y_5 += 1

# Now let's print it to our terminal

print("We have ",y_1," one-year-old frogs, ",y_2, " two-year-old frogs, ",
      y_3," three-year-old frogs, ",y_4," four-year-old frogs, and ",
      y_5, " old frog farts. I mean, these guys are ready to croak.")
