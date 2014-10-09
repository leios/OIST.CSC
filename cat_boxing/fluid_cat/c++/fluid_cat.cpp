/*-------------fluid_cat.cpp--------------------------------------------------//
*
* Purpose: to simulate a cat boxing algorith with fluid-like cats. 
*          Assumptions made can be found in the README file
*
* Note: In this file, we will learn about functions and looping structures
*       If you are not familiar with some of this file, such as the headings and
*       some small parts of C++ syntax, be sure to check out the "hello world"
*       code. That should answer any questions you have.
*
* That is all
*
*-----------------------------------------------------------------------------*/

// following syntax from "Hello World" ...

#include <iostream>
#include <stdlib.h>

// stdlib.h calls the library that holds the random number generator of c++

using namespace std;

// Remember how we just started with the main function last time? Yeah. We are 
// Not going to do that this time. Let's start by generating the cats!
// like "main," our "generate_cat" function does not need any arguments

int generate_cat(){
    
    // Great! We have started our function. Now, what do we want to do? Well
    // we want to take c++'s random number generator and output and approximate
    // cat volume. Easy, right? But wait! How do we know that our cat volume is
    // accurate? Well, for this case, it doesn't have to be! 
    // Instead of trying to get "real" values, let's imagine our cats are on a
    // scale from 1 to 100. If they are a 1, they are just a cute little kitten,
    // and if they are a 100... well... they are not a cute little kitten any
    // more. This type of approximation is actually really common in code--
    // especially because integer values (counting numbers) are easy to use

    int cat_size = rand() % 100 +1;

    // What did I just do? Well, I used the c++ rand() function for generate
    // a random number, then I used a mathematical function you might not be 
    // familiar with called the modulus operator (%). Remember in 3rd grade when
    // you divided 101 by 100 and got a remander of 1? Well, we are doing the 
    // same thing here. Because the rand function spits out a number between 1 
    // and some insanely large RAND_MAX number set by your compiler, we can 
    // assume that the number is random and between 1 and 100. But wait! C++ 
    // starts counting at 0, so in order to get the range to truly be between 1
    // and 100, we need to add 1. So we did.
    // What does "int" mean? well, it means that the output of this parameter
    // is an integer. Note that it was also used in the function, "int 
    // generate_cat".  

    return cat_size;

    // finally, we return the cat size between 1 and 100. By "return," I mean
    // that we send the value of "cat_size" to wherever it was called from.
    // I think this will make more sense by the end of this code.

}


// Now we need a function to place the cats in a box

int fill_box(){

    // This function starts like the last one. I hope you are starting to get 
    // the hang of funtions.

    int box_size = 400, empty_room = 400, j = 0;

    // So, since our cats are not "real values," there is no reason our box 
    // needs to be either. We'll just say it can fit 4 really big cats.
    // We also created another parameter: empty_room -- set to 400 because the
    // entire box is empty!
    // we also create a random variable "j." This will be used later.

    while (empty_room > 0){

        // Welcome to your first loop! In this case, it is a "while" loop. It
        // will keep going, so long as there is still empty room in the box.
        
        int cat = generate_cat();
        
        // Remember how we returned "cat_size" last time? Yeah, we need that 
        // now. So let's read it in here and call it "cat."

        empty_room = empty_room - cat;

        // This is a statement that redefines "empty_room." Now it is whatever
        // it was before, less the cat's size.
        // once these operations are done, it wraps back up to the top and 
        // checks to see if "empty_room" is still larger than 0. If it is, it 
        // does this again. Woo!

        j = j + 1; 
        
        // remember j? Well, it's back! This time, it's counting cats!
        // every time the loop loops back, it will add another number to j.
        // and every time the loop loops back, another cat is added to the box.
        // this means that j represents the number of cats in each box!

    }

    return j;

    // this time we are returning j... which represents the number of cats in
    // a full box. I hope that makes sense!

}


// Now for the final function before main!

void fill_truck(){

    // This time, we do not need to worry about the type of function because we
    // are not returning anything at all. So, we say the type of function is
    // "void." Let's do this!

    // Let's pretend the truck can hold 40 boxes. Well, let's create the truck
    // size and use another while loop. While we are at it, let's keep track
    // of all the cats we are stuffing in the truck!

    int truck_size = 40, cat_num = 0, i = 0;

    // We also created the random variable "i." This time, the variable will be
    // used to keep track of the number of boxes in the truck!
 
    while (i <= truck_size){

    int cats_in_box = fill_box();
    cat_num = cat_num + cats_in_box;

    i++;
    
    // from previous logic, you should be able to follow up to the last line,
    // i++. This just means "add 1 to i!" It's only meant to be used in loops,
    // though. So be careful!
    }

    cout << "There are " << cat_num << " cats in our truck. Let's move out!"
         << endl;

}

// Now for main! fortunately, because we created so many functions, there is not
// much to be done here.

int main(){

    fill_truck();

    // Yup. That's it. Just calling the function "fill_truck."

}
