call fill_truck()
end program
subroutine fill_truck()
    implicit none

    integer :: truck_size = 40, cat_num = 0, i = 0, cats_in_box

    do while (i <= truck_size)

        call fill_box(cats_in_box)
        cat_num = cat_num + cats_in_box
        i = i + 1

    end do

    print *, "There are ", cat_num, " cats in our truck. Let's move out!"

end subroutine fill_truck

subroutine fill_box(cats_in_box)
    implicit none

    integer :: box_size = 400, empty_room = 400, j = 0 
    integer :: cat_size = 0, cats_in_box
    real    :: rand_num

    do while (empty_room > 0)
        
        call random_number(rand_num)
        cat_size = floor(rand_num*100)

        empty_room = empty_room - cat_size
        j = j + 1


    end do

    cats_in_box = j
    return

end subroutine fill_box
