/*-------------caged_cat.cpp--------------------------------------------------//
*
* Purpose: To place cats in cages and place those cages in a truck in the most
*          Efficient way possible. 
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include "fluid_cat.h"

// See that line? The one with the "fluid_cat.h" just above? Yeah, that's a 
// little important. In order to link files from one code to another, you use
// a "header" file (thus the ".h" extension). It is certainly worthwhile to look
// into that file and see what you can learn!

using namespace std;

// the other two lines should make sense. We are including a module to allow us
// to stream output to the terminal and we are using standard notation

// Now comes a somewhat challenging part, planning out the code. In truth, this
// shouldn't be too bad. We just need to generate a random cat, place that cat
// in an appropriately sized box, and place that box in a truck. The third step
// might be a bit of a challenge, though.

// So let's break it down step by step.
// First function: box_cat. This function will take a random cat size and place
// it into the appropriately sized cage. In scientific applications, this 
// process is known as "binning" data, because you are taking data and placing
// it in bins (or in this case, you are placing cats in cages). It is a very 
// useful tool to know how to use!

// This function is not too bad. It will take in a cat size and spit out an 
// integer value (either 1, 2, or 3) that designates the size of the cage. 
// for the purposes of this approximation, small boxes are 1/3 the size of large
// boxes. The medium sized boxes are 2/3 the size of the large boxes. 

int box_cat(){

    int cage_size;
    // First, we need to create an integer variable for the size of the cages.
    // Now, let's call the function from our previous example: the fluid cat 
    // approximation. What function do we need? Well, the one that generates
    // random cats, of course! This is what the header file is for, calling
    // functions from other files and using them whenever you want.

    int cat_size = generate_cat();

    // Cool, we have a cat size. Now all we need to do is place them into boxes.
    // How would we do that in real life? Simple! If the cat is large, we place
    // it in a large box. If it is small, we place it in a small box. If it is
    // a moderate size, we place it in a moderately sized box. Luckily for us, 
    // c++ (and most other languages) understand the word "if." While coding, an
    // "if" statement tells the computer to do something when certain condition
    // are met. 

    // If I remember correctly, we set our car_size to be in a range from 1 to 
    // 100. Now that I think about it, this is not a plasible scale... but who
    // cares? If our cats are between 1 and 100, then we have 3 "size ranges"
    // to worry about: cat_size <= 33, 33 < catsize <= 66, and 
    // 66 < cat_size <= 100. Note that the "<=" means "less than or equal to."
    // It is similar to every other comparative sign, like "<", ">", "==", and
    // ">=". We just need to cover the full range between 1 and 100.

    if (cat_size <= 33){
        cage_size = 1;
    }

    // look carefully at this syntax. The squirrelly brackets "{}" open and
    // close the statement, while the parentheses designate the condition 
    // necessary to go into the loop.

    // Now let's do this twice more!

    if (cat_size > 33 && cat_size <= 66){
        cage_size = 2;
    }

    // Check that "if" statement out! Multiple conditions? That's what I call
    // a good time!

    if (cat_size > 66 && cat_size <= 100){
        cage_size = 3;
    }

    // Now all we need to do is return the cage_size and feed that into the next
    // section: placing it in the truck. *dramatic music*

    return cage_size;
}

// Let's think about this function. We want to place boxes of certain sizes into
// a truck. It doesn't sound bad, right? Well... it can be. There are an awful
// large number of configurations that are simply inefficient. I guess the best
// bet for our first attempt at filling the truck is to parse the inside of the
// truck into three columns: one for large, medium, and small boxes. In this 
// case, we can assume that the truck can hold 4 large boxes, 6 medium boxes, 
// and 12 small boxes. 

// What happens with the extra boxes? Well, we'll just throw them to the side
// and leave them for the next truck. I think it would be interesting to count 
// the number of caged cats that we will be leaving at the side of the road,
// though. So let's do that too.

int organize_cats(int& is_full, int& large_count, 
                  int& med_count, int& small_count){

    // I have made this function dependent on the variable "is_full", which is
    // just a query of whether the truck is full or not. If is_full reads the
    // number "3", it is full of small, medium, and large cages. I have also 
    // made the function dependent on the large, medium, and small counts to
    // keep track of how many cats have passed through our robot's claws.

    // But wait! What's up with the "&" character at the end of the "int" 
    // arguments? Well, I'm glad you asked! Those are notifiers to the compiler
    // to let it know that it does not have to recreate those variables. They 
    // are somewhere else in the code. This way, we can return all of those
    // integer values at the end. If this is confusing, don't worry! It'll be
    // easier to understand with time!

    // So, first things first, let's establish the appropriate variables.

    int large_num = 4, med_num = 6, small_num = 12;

    // Now, let's place a cat in a cage.

    int cage_size = box_cat();

    // There are three possibilities: 
    //     The cage is large (3) 
    //     The cage is medium-sized (2)
    //     The cage is small (1)
    // We need an "if" statement to deal with all three cases. But what do we do
    // after that? Well, the first "if" statement will be for us to establish
    // the box size in this function. We then need to place it in the 
    // appropriate position. In this case, though, that doesn't really matter. 
    // We just need to know that we can fit 4 large, 6 medium-sized, and 12 
    // small boxes in the truck. If we have all that can fit of a particular
    // type of box, we also need to pass that information along. We'll use a 
    // fourth "if" statement for this.

    if (cage_size == 3){

        // This corresponds to large boxes. Let's first update the count.

        large_count = large_count + 1; 

        // now we need an additional statement to let us know when the part of
        // truck designated to store large boxes is full

        if (large_count == 4){

            is_full = is_full + 1;

        }
    }

    // Now we need to do it twice more for the other cage sizes

    if (cage_size == 2){

        med_count = med_count + 1;

        if (med_count == 6){
            is_full = is_full + 1;
        }

    }

    if (cage_size == 1){

        small_count++;

        if (small_count == 12){
            is_full++;
        }
    }

    // Now we just need to return our values!

    return is_full, small_count, large_count, med_count;
}

// Now let's start the main function!

int main(){


    // First, let's create the variable to check whether the truck is full.

    int is_full = 0, large_count = 0, med_count = 0, small_count = 0;

    // Now let's create a loop to keep perfomring calculations until the truck
    // is full.

    while (is_full < 3){

        organize_cats(is_full, large_count, med_count, small_count);

    }

    cout << "The truck is full! Let's move out and leave "
         << large_count - 4 << " large cats, "
         << med_count - 6 << " medium-sized cats, and "
         << small_count - 12 << " small cats behind! Who needs 'em?"
         << endl;
}
