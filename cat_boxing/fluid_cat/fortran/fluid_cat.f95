!!-------------fluid_cat.cpp--------------------------------------------------!!
!
! Purpose: to simulate a cat boxing algorith with fluid-like cats. 
!          Assumptions made can be found in the README file
!
! Note: In this file, we will learn about functions and looping structures
!       If you are not familiar with some of this file, such as the headings and
!       some small parts of C++ syntax, be sure to check out the "hello world"
!       code. That should answer any questions you have.
!
! That is all
!
!!----------------------------------------------------------------------------!!

! So, if you have gone over this simulation on c++ or python, you might have 
! noticed that we created functions first and implemented them afterwards. We 
! can do that here, but I'm going to mix things up for clarity. Let's say we 
! want a code that fills a truck with cats. Well, in Fortran, most people use
! "subroutines" instead of "functions." What's the difference? Not much. I just
! like the word "subroutine," so I'll be using that.

! So. Let's call a subroutine "fill_truck," which fills the truck with cats

call fill_truck()

! Note: the two parentheses mean that the subroutine fill_truck does not require
! any additional parameters. This makes everything simple.

end program

! Woah. Woah! Wait a minute. Did we just end the program? Yeah, we did. 
! Subroutines are called subroutines because they are supposed to come after the
! program ends. It's weird. Just know that that's what's customary in fortran.
! Now let's create that subroutine!

subroutine fill_truck()
    implicit none

! What does "implicit none," mean? Well, fortran is old... super, super old. So
! old, in fact, that older versions of fortran force any variables starting with
! i, j, k, l, or m to all be integers. Was this ever useful? I guess so. I am 
! not sure when, though. Just make sure that whenever you make new functions
! that you use this command. It'll make everything easier.

    integer :: truck_size = 40, cat_num = 0, i = 0, cats_in_box

! First, let's define all the variables we need. Take note that we are not using
! "real" number here. We are just saying that a truck can fit 4 boxes of cats.
! That's good enough for now.

    do while (i <= truck_size)

    ! Welcome to your first loop! So, in this case, we are filling the truck.
    ! Remember that the truck can only fit 40 boxes, so we created a loop that
    ! will fill a box with cats and then place that box in a truck 40 times. 
    ! The "do while" loop will just keep going until i, which is an integer we
    ! will be using to count how many times the loop has done it's business,
    ! is greater than the number of boxes that can fit in the truck. Once that
    ! happens, we'll high-tail it out of there!

        call fill_box(cats_in_box)
        
        ! We are going to need another subrouting that fills a box with cats.
        ! In this case, the subroutine will be modifying a variable, that 
        ! variable is "cats_in_box." once it is done with that variable, it will
        ! release it into the wild... or back here anyway

        cat_num = cat_num + cats_in_box

        ! Now we need to keep track of all the cats in the truck. This means we
        ! need an iterative statement that takes "cat_num" and redefines it 
        ! based on it's previous value and the value just modified by the 
        ! subroutine "fill_box," which we will create in a second.

        i = i + 1
    
        ! This adds 1 to the value of i. It keeps track of how many iterations
        ! of the while loop we have been though!

    end do

    ! This statement ends the do loop we just used. 
    ! Now let's print a statement saying how many cats we have in our box!

    print *, "There are ", cat_num, " cats in our truck. Let's move out!"

    ! finally, let's end our subroutine

end subroutine fill_truck


! Now let's create the subroutine "fill_box"

subroutine fill_box(cats_in_box)
    implicit none

    integer :: box_size = 400, empty_room = 400, j = 0 
    integer :: cat_size = 0, cats_in_box
    real    :: rand_num

    ! The above statement is the same as the last function. It just creates or
    ! redefines necessary variables for the subroutine. Note: We are not using
    ! "real values" for our truck size, so there is no reason to use real values
    ! for our cat or box sizes either. Let's just say that a fully-grown cat 
    ! measures to be an integer value of 100, while a little kitten is a 1. 
    ! Also: 4 fully grown cats can fit into a single box.
    ! I would like to point out that because we need a random number, we also 
    ! created another variable that is a real number "rand_num"

    do while (empty_room > 0)
        
        ! This will keep going until "empty_room" is under 0... which means 
        ! there is no longer any room in the box!


        ! First, let's randomly generate a cat of some size between 1 and 100.
        ! This isn't too bad. There is a subroutine that is common to all of 
        ! fortran to do it called "random_number()"

        call random_number(rand_num)

        ! This will make "rand_num" a random real number between 0 and 1, now we
        ! just have to assign that value to a cat

        cat_size = floor(rand_num*100)

        ! We multiply it by 100 and then round it down with "floor." 
        ! Now let's create another while loop to fill the box!

        empty_room = empty_room - cat_size

        j = j + 1

        ! These statements should make sense from the previous subroutine. Let
        ! me know if they do not!

    end do

    cats_in_box = j

    return

! this returns all the variables we messed with in the subroutine... 
! namely "cats_in_box"

end subroutine fill_box

! And that should be that! Let's compile it and se what happens!
