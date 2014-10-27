#-------------caged_cat.py-----------------------------------------------------#
#
# Purpose: To give te cats we previously worked on cages and then stuff them 
#          into a truck. This is a step up from last time where we just assumed
#          the cats were fluid and shoved them into a box. We will also keep
#          track of all the cats we must leave on the side of the road to fill
#          the truck optimally (leaving some cats for the next truck).
#
# Assumptions: 
#    1. 1 cat per cage, 3 cage sizes
#    2. The truck can hold 4 large, 6 medium-sized, and 12 small cages
#    3. The truck will be filled optimally. Any cats left over will wait for
#       the next truck. 
#
# I think that's it! So let's get to it!
#------------------------------------------------------------------------------#

# First things, first. We are going to need to generate a randomly sized cat 
# again, so let's import our last file, which has been copied to this directory.

from fluid_cat_slim import *

# Note the syntax. The "*" symbol means that we are importing all the functions
# from the file "fluid_cat_slim.py". Also note that the ".py" extension is no
# present. That might trip you up in the future.

# Like last time, we'll start function by function. We'll box the cats and place
# them in the truck

def box_cat():

    # Remember the "generate_cat" function from last time. We need that.

    cat_size = generate_cat()

    # Now we have a cat of some given size. Let's place that cat in a box.

    if cat_size <= 33:
        cage_size = 1

    # Did you see that? That was an "if statement"! It works as you would 
    # expect. When the condition is met, the action in the statement will
    # be performed. Simple as that. In this case, "cage_size" will be defined as
    # 1. That is all.

    if cat_size > 33 and cat_size <= 66:
        cage_size = 2

    # Here we are showing off an "if statement" with mutliple conditions

    if cat_size > 66 and cat_size <=100:
        cage_size = 3

    # Honestly, we didn't need the upper limit of 100, but it's in there for
    # clarity's sake.

    # Alright! one function done! now all we need to do is return cage_size
    return cage_size

# Now, let's think about this upcoming function a bit. We want to count all the
# left over cats, so we will need a counter for each of those. On top of that,
# we will need a counter to let us knoe when the truck is full of large, 
# medium-sized, and small boxes. This means that this function should be 
# dependent on those 4 variables.

def organize_cats(is_full, large_count, med_count, small_count):

    # Let's go ahead and define the maximum number of large, medium-sized, and 
    # small boxes our truck can hold

    large_num = 4 
    med_num = 6
    small_num = 12

    # Now let's place a cat in a cage

    cage_size = box_cat()

    # There are 3 possibilities, at this point:
    #    The cage is large (3)
    #    The cage is medium, sized (2)
    #    The cage is small (1)
    # We need an "if statement" to deal with each of these possibilities and we
    # need to update the large, small, and med counts along with the is_full 
    # parameter each time

    if cage_size == 3:

        large_count = large_count + 1

        # Now we need to take into account the possibility that the truck is
        # full of large boxes

        if large_count == 4:
            is_full = is_full + 1

    # Now we are back to 4 spaces for the next "if statement"

    if cage_size == 2: 
        med_count = med_count + 1

        if med_count == 6:
            is_full = is_full + 1

    if cage_size == 1:
        small_count = small_count +1

        if small_count == 12:

            is_full = is_full + 1

    # now we just need to return everything

    return is_full, large_count, med_count, small_count

# now for the main event!

# first, let's initialize the variables we need:

is_full = large_count = med_count = small_count = 0

# Now we need a "while loop" to drive all the "if statements". 
# In this while loop, we will be constantly redefining our variables, so we must
# create a list and set that equal to the new list being generate by the 
# functions above. You'll see how this is done in a second.

while is_full < 3:
    
    is_full, large_count, med_count, small_count = \
        organize_cats(is_full, large_count, med_count, small_count)

# See that slash at the end? Yeah, that means that the line continues.
# It's mainly a formatting thing.

# Once the while loop is finished, we can go from there.

print("The truck is full! Let's move out and leave ", large_count - 4,
      " large cats, ", med_count - 6," medium-sized, cats and ",
      small_count - 12," small cats behind! Who needs 'em?")

