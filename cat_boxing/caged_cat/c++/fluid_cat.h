/*-------------fluid_cat.h----------------------------------------------------//
* 
* Header files are incredibly important in c++ programming. It is certainly 
* worthwhile to learn how to write them in order to transport functions from one
* coding file to another. 
*
* This is a quite typical header file. In order to get a single output 
* executabl when you compile this program, you will need to compile all of the
* files in this directory that end in ".cpp". That means that this header file
* is not immediately compiled with the rest of the code; however, it is called
* in the codes, themselves... So the compiler will know what to do with what.
*
*-----------------------------------------------------------------------------*/

// First, we need to define the header file. This is usually done like so:

#ifndef FLUID_CAT_H
#define FLUID_CAT_H

// Why is it in all caps? I honestly do not know. That's just how I learned it 
// and it seems common. Also, it helps me identify the header file due to 
// special syntax. Syntax is always important in coding.

// Now all we need to do is copy all of the functions from our cpp file, in this
// case "fluid_cat_slim.cpp".

int generate_cat();

int fill_box();

void fill_truck();

// Now we just need to end the function

#endif
