/*-------------hello_world.cpp------------------------------------------------//
* 
* Getting your computer to say "Hello World!" is the most traditional way to 
* start any programming class. I figured we could go ahead and start there 
* before getting into some really cool coding stuff. 
*
* So, C++ is a bit of an odd language. Many would consider it clunky. Check out
* The README file if you want to learn a bit about how commenting works, but 
* suffice it to say that this whole block will be neglected entirely by the 
* compiler. But wait! What's a compiler?
*
* for our purposes, let's say the compiler is the thing that transforms your
* code into something that can be executed later on. This means that after
* compiling your code like so:
*
* g++ hello_word.cpp -o say_hi
*
* You will find a file in your directory called "say_hi". In order to execute
* The file, you will simply type:
*
* ./say_hi
*
* Go ahead and try it! It should work out just fine, and you should see the 
* following output:
* 
* Hello World!
*
* Which is pretty cool! Now for the code:
------------------------------------------------------------------------------*/
// Every C++ file starts with including the appropriate goodies to get your
// program running. In our case, we only need one: iostream. The thing that lets
// you output things to your terminal.

#include <iostream>

// Now we need to estalish some sort of dialect of the C++ language to use. 
// In this case, the standard dialect will do:

using namespace std;

// Finally, we need to create a function, but not just any function... the 
// MAIN FUNCTION. this function is necessary in every C++ file and  essentially
// IS the entire program. Sure, you can have mini functions outside of main...
// but that's a story for another day.

int main(){

// Woah, woah! Hold the phone! What did I just do? I initiallized the function
// "main". Sure, but how do you do that? Well, note the two parentheses '()',
// In these parentheses, I would place anything the function depends on. In this
// case, it depends on nothing, it is a lone wolf! so there is nothing to put
// there...
// But what about the squirrelly bracket '{'? Well, that starts a function in
// C++. note that the end of the function there will be another one facing the 
// other way to close it, '}'.
// Now to move on.

cout << "Hello World!" << endl;

// Alright, you're joshing me, right? What the heck does THAT ^ mean? Well...
// "cout" is read as "c-out". It means we are using c to send something out.
// there is another function called "cin" which means "c-in". We will be using
// that in due time. 
// the two less than signs "<<" just means that we are throwing something out.
// Remember how you learned a while back to tell which side of the sign was 
// greater than the other side? The alligator always wants the larger side,
// right? Well, same here... except the alligator is the terminal. Whichever
// side is bigger is the side coming from or going to the terminal. 
// So you have the terminal munching on the "Hello World!" but then it's 
// munching on... wait. what is that? "endl"... What does that even mean?
// note that endl is not in quotes. That means that endl is a function. What 
// does the function do? well, it "end"s "l". What's l? it means line.
// So we have a function that tells c to output "Hello World!" and then end the
// line... that's all fine and dandy... but what's up with that stupid 
// semi-colon?
// Okay. That's a little different. The semi-colon tells the COMPILER to end the
// line. This means that we could have spread that "Hello World!" command across
// as many lines of code as we wanted, until the compiler runs across a 
// colon, it will always assume it is reading 1 line of code. That's pretty 
// cool!
// finally:

}

// This ends the function "main"
// ... although, I think I mentioned that before.
