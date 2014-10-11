#-------------fluid_cat.cpp----------------------------------------------------#
#
# Purpose: to simulate a cat boxing algorith with fluid-like cats. 
#          Assumptions made can be found in the README file
#
# Note: In this file, we will learn about functions and looping structures
#       If you are not familiar with some of this file, such as the headings and
#       some small parts of C++ syntax, be sure to check out the "hello world"
#       code. That should answer any questions you have.
#
# That is all
#
#------------------------------------------------------------------------------#

# Let's pull things from libraries that we will need. The only one I can think 
# of right now is "randint" from the "random" python library. You will see this
# in the future. Definitely

from random import randint

# So let's first define a function that generates randomly sized cats

def generate_cat():
    
    # this syntax is important! the colon means everything that follows and is
    # spaced appropriately is a part of the function we just created, in this
    # case, "generate_cat." The parentheses are where we would place ojects that
    # the function is dependent on. Unfortunately, we do not need to place 
    # anything here right now, but we might in the future!
    
    # Remember that "randint" function we just pulled from python's "random"
    # library? Let's use that to make a randomly sized cats. Now, these cats do
    # not need "real" values. In fact, let's just say that a really, really 
    # large cat is at a value of 100... meanwhile a little kitten would be at 1.
    
    cat_size = randint(1,100)
    
    # The randint function creates a random integer (counting number) from the
    # first to the second number, in this case 1 to 100. Let's call this number
    # "cat_size."

    return cat_size

    # "return" means that whenever we call this function from now on, the output
    # will be "cat_size." You will see this quite soon, actually.
    
    
# Now let's create another function to place the cats in a box

def fill_box():

    # This function is just like the last one. I hope functions are starting to
    # make some more sense.
 
    box_size = 400
    empty_room = 400
    j = 0

    # So, since our cats are not "real values," there is no reason for our box
    # size to be real values either. We'll just say that our box can fit 4 
    # really big cats. We also created another parameter: empty_room -- set to 
    # 400 because the entire box is empty!
    # We also created a random variable "j." This will be used later. Trust me.

    while empty_room > 0:

        # Welcome to your first loop! In this case, it is a "while" loop. It
        # will keep going, so long as there is still empty room in the box.

        cat = generate_cat()
 
        # Remember how we returned "cat_size" last time? Yeah, we need that now.
        # So let's read it in here and call it "cat."

        empty_room = empty_room - cat

        # This is a statement that redefines "empty_room." Now it is whatever it
        # was before, less the cat's size.
        # Once these operations are done, it wraps back to the top and checks to
        # see if "empty_room" is still larger than 0. If it is, it does this
        # again! Woo!

        j = j + 1

        # Remember j? Well, it's back! this time, it's counting cats! Every time
        # the loop loops back, it will add another number to j. Every time the
        # loop loops back, another cat is added to the box. This means that "j"
        # represents the number of cats in each box. That's pretty cool!

    return j

    # this time we are returning j... Which represents the number of cats in a
    # full box. I hope that makes sense!

# Now for the final function before main!

def fill_truck():

    # Let's pretend the truck can hold 40 boxes. Well, let's create the truck
    # size and use another while loop. While we are at it, let's keep track of
    # all the cats we are stuffing into the truck!

    truck_size = 40
    cat_num = 0
    i = 0

    # We will use another random variable, "i." This time, the variable will be
    # used to keep track of the number of boxes in the truck! Woo!

    while i <= truck_size:
    
        cats_in_box = fill_box()
        cat_num = cat_num + cats_in_box

        i = i + 1

        # So, you should be able to follow all the logic in this function.
        # Let me know if it gives you trouble!

    print("There are ", cat_num, " cats in our truck. Let's move out!")

    # This print statement is a little different than what you might have seen
    # last time. The commas mean we are printing more things with the same 
    # statement. When you run the code, you'll see what it means.

# Now for the main function! Fortunately, because we created so many functions, 
# There is not much to be done here!

fill_truck()

# Yup. That's it.

