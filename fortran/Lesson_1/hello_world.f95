!-------------hello_world.f95--------------------------------------------------!
!
! Alright. First things first. Fortran is OLD. Like, super, duper old. See that
! ".f95" file extension? Yeah. That tells the fortran compiler which version of
! fortran we are using. This, along with the "f95" extension are the two most
! favored versions of fortran in use today; however, my old advisor used fortran
! from 1977... So not everyone is using the same version. In fact, you might as
! well just assume that the people you are working with will not be using the 
! same version of fortran as you are. I am going to be using fortran 95 for the
! purposes of these lessons, but let it be known that other versions of fortran
! may have drastically different syntax and things. 
!
! That said, fortran is so promenant in the scientific community, I felt 
! compelled to include it with the C++ and python. Again, those are the only
! languages I have ever seen actually used by people in the wild before...
!
! Now, to run this code, you will first need to compile it with a compiler. What
! is a compiler, you ask? Well, for our purposes... let's just say that it is a
! piece of software that turns your code into an executable command for the 
! computer to use. How do you use it? Well, like so:
!
! gfortran hello_world.f95 -o say_hi
! 
! This will provide a file in your directory named "say_hi"
! Now, you just need to execute it like so:
!
! ./say_hi
!
! And your terminal should spit out the phrase "Hello World!"
!
! Fantastic! Your first code is done. Now let's write the darned thing.
! Whippersnappers. 
!------------------------------------------------------------------------------!

! First, let's define a program... let's call it, "hello"

program hello

! Now let's tell fortran to print "Hello World!" to the terminal. Print is what
! we call posting text or code output to the terminal. It should not be confused
! with printing from a printer.

    print *, "Hello World!"

! Okay. "print" should make sense. So should the output "Hello World!"... but 
! what is up with that "*," ?
! Well, I'm glad you asked! Did I mention that fortran is old? Well, it is.
! In fact, for every other code I write, I will start every line in the code
! with 6 spaces. Why? Because Fortran is old. 
! The "*," is an abbreviation of "(*,*)"... not that that tells you much. 
! Before printing anything, fortran asks where to print it and how to print it.
! In other words, it asks for a file and a format.
! The first asterisk is the question of "where." We told it to print ANYWHERE...
! It's default is the terminal. Then it asked the format it should print in...
! We didn't give it a format, there was no second asterisk... so it just printed
! in a default format. Just the text. Nothing more, nothing less.
! And finally...

end program hello

! We ended the program "hello"
! And I think that's it! Now just compile and run it like I mentioned at the 
! top!

! Also, without all these exclamation point comments, fortran would be pretty
! boring, wouldn't it?

