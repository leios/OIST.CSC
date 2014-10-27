from random import randint

def generate_cat():
    cat_size = randint(1,100)
    return cat_size


def fill_box():
    box_size = 400
    empty_room = 400
    j = 0

    while empty_room > 0:

        cat = generate_cat()
        empty_room = empty_room - cat
        j = j + 1
    return j


def fill_truck():

    truck_size = 40
    cat_num = 0
    i = 0

    while i <= truck_size:
    
        cats_in_box = fill_box()
        cat_num = cat_num + cats_in_box
        i = i + 1

    print("There are ", cat_num, " cats in our truck. Let's move out!")

