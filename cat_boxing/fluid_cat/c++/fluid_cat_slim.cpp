#include <iostream>
#include <stdlib.h>

using namespace std;

int generate_cat(){
    
    int cat_size = rand() % 100 +1;

    return cat_size;

}


int fill_box(){

    int box_size = 400, empty_room = 400, j = 0;

    while (empty_room > 0){
        
        int cat = generate_cat();

        empty_room = empty_room - cat;

        j = j + 1; 

    }

    return j;

}


void fill_truck(){

    int truck_size = 40, cat_num = 0, i = 0;
 
    while (i <= truck_size){

    int cats_in_box = fill_box();
    cat_num = cat_num + cats_in_box;

    i++;
    
    }

    cout << "There are " << cat_num << " cats in our truck. Let's move out!"
         << endl;

}


int main(){

    fill_truck();

}
