/*-------------simple.cpp-----------------------------------------------------//
*
* Purpose: This file is a simple example of how we can simulate the defomation
*          of balls with a newton-solver algorithm. I have referred to RK4 a 
*          few tiems and may implement it if this ends up becoming too slow in
*          the future, but I think it should be fine.
*
*   ERROR: There is currently an error in the simulate function. It is due to
*          A rather trivial geometrical miscalculation. I cannot determine the
*          velocity in the direction of motion, which is necessary for Hooke's
*          Law stuff. I have calculated all the necessary thetas... but am too
*          tired to figure out where they need to go to get everything to work
*          out. I will come back to this when I have time.
*
*          Note: the error presents itself as a bunch of NaN's in the point 
*          vector after the simulate command. I believe it reads in the 
*          positions correctly, though. Because everything is timestep 
*          dependent, though... when part of the first timestep screws up, it
*          all goes downhill.
*
*          Note 2: memory allocation error to boot. I think this is related. I
*          will probably just rewrite the simulate function.
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

/*----------------------------------------------------------------------------//
* STRUCTURES AND FUNCTIONS
*-----------------------------------------------------------------------------*/
using namespace std;

// Structure to point to the closest points in each direction
// I might actually use pointer later, but not for now.
struct closest{
    int up,down,forw,back,left,right;
};

// Class to hold all values of particles.
class point{
    public:
        int step_num;                                  // Time-step number. 
        double x, y, z;                                // Position in x, y, z
        double v_x, v_y, v_z;                          // Velocity in x, y, z
        closest next;                                  // Closest points
};

// Class for all the parameters for hooke's law
class hook_param{
    public:
        double timestep, spring_const, rest_l, mass;
};

vector <double> hookes(double dist, double velocity, hook_param params);
void test(hook_param params);
vector <point> create_sphere(double radius, double rest_length,
                             double init_v_x, double init_v_y, 
                             double init_v_z);
vector <point> simulate(vector <point> curr_sphere, hook_param params);
void write_file(vector<point> points);
void clear_output();


/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/
int main(){

    clear_output();
    hook_param params;
    params.timestep     = 0.0001;
    params.mass         = 0.001;
    params.spring_const = 1;
    params.rest_l       = 10;

//    test(params);

    double radius = 5.0;
    double rest_length = 0.5 * radius; 
    double init_v_x, init_v_z, init_v_y;
    vector <point> points;

    init_v_x = 0; init_v_y = 0; init_v_z = 0;
    points = create_sphere(radius, rest_length, init_v_x, init_v_y, init_v_z); 
    write_file(points);

    // ERROR... I think we get a lot of NaN's because there is no value in that
    // direction...
    points = simulate( points, params);
    write_file(points);

}

/*----------------------------------------------------------------------------//
* SUBROUTINES / FUNCTIONS
*-----------------------------------------------------------------------------*/

// Simple solver for Hooke's law. I could use RK4, but this'll do for now.
vector<double> hookes(double dist, double velocity, hook_param params){

    vector<double> both;

    dist += (velocity * params.timestep) 
            + params.timestep * params.timestep
            *(0.5 * params.spring_const * (params.rest_l - dist) / params.mass);
    velocity += params.timestep*(params.spring_const * 
                                (params.rest_l - dist) / params.mass);

    both.push_back(dist); both.push_back(velocity);

    return both;
}

// Test for Hooke's function... and potentially RK4 in a bit. 
void test(hook_param params){

    vector<double> solution;
    double distance = 9.0,velocity = 0;

    solution.push_back(distance);
    solution.push_back(velocity);
    for (int i = 0; i < 100; i++){
        solution = hookes(solution[0],solution[1],params);
        cout << solution[0] << '\t' << solution[1] << endl;
        
    }
}

// Populate sphere of points. Brutish, sure... but it'll do.
// Note: make reat_length a multiple of radius. That makes things easier.
// Also: Checked
vector <point> create_sphere(double radius, double rest_length,
                             double init_v_x, double init_v_y, 
                             double init_v_z){

    // The idea here is simple. We will start at the corner of our sphere and
    // create points in x, then y, then z that are each rest_length atart from
    // one another. Whenever any of these parameters are
    // outside of the radius of our sphere, we move to the next parameter.
    // The end result should be a vector of points, moving at our initial vel.

    vector<point> points;                               // All points
    point dummy;                                        // Dummy point
    int count = 0;                                      // Just a count

    cout << "Populating sphere..." << endl;

    for (double ix = -radius; ix <= (radius); ix = ix+ rest_length){
        for (double iy = -radius; iy <= (radius); iy = iy + rest_length){
            for (double iz = -radius; iz <= (radius); iz = iz + rest_length){

                if (((ix * ix) + (iy * iy) + (iz * iz)) <= radius*radius){
                    dummy.step_num = count;
                    dummy.x = ix;
                    dummy.y = iy;
                    dummy.z = iz;
                    dummy.v_x = init_v_x;
                    dummy.v_y = init_v_y;
                    dummy.v_z = init_v_z;
                    points.push_back(dummy);
                    count++;
                }

                
            }

        }

    }

    // Now I need to figure out which ones are closest to each other.
    // Note: if I want to use this code later, I can easily break this f(x) 
    //       in half.

    cout << "Finding closest particles..." << endl;

    double x, y, z;

    for (int i = 0; i < points.size(); i++){
        x = points[i].x;
        y = points[i].y;
        z = points[i].z;

        // Let's find the maximum count number (fcount)
        double count_up, count_down;
        int fcount;

        count_up = radius*radius - (x+rest_length)*(x+rest_length);
        count_down = radius*radius - (x-rest_length)*(x-rest_length);

        if (count_down > count_up){
            fcount = count_down;
        }
        else{
            fcount = count_up;
        }

        for (int ii = 0; ii < fcount; ii++){

            // UP
            if ( points[i].z == points[i + ii].z){
                points[i].next.up = i+ii;
            }

            // RIGHT
            if ( points[i].y == points[i + ii].y){
                points[i].next.right = i+ii;
            }

            // FORW
            if ( points[i].x == points[i + ii].x){
                points[i].next.forw = i+ii;
            }

            if ( i >= ii){

                // DOWN
                if ( points[i].z == points[i - ii].z){
                    points[i].next.down = i-ii;
                }

                // LEFT
                if ( points[i].y == points[i - ii].y){
                    points[i].next.left = i-ii;
                }

                // BACK
                if ( points[i].x == points[i - ii].x){
                    points[i].next.back = i-ii;
                }

            }

        }

    }
    return points;
}

// Now I need to prepare each point so that it reads into my Hooke's law f(x).
vector <point> simulate(vector <point> curr_sphere, hook_param params){

    int dir;
    double del_x, del_y, del_z, del_tot;

    // I'll need these thetas... probably.
    double theta_xz, theta_yz, theta_xy, theta_zy, theta_zx, theta_yx;

    // I need to get the velocities from each component in the spring direction
    double del_vx, del_vy, del_vz, vel_tot;

    vector <double> solution;

    solution.push_back(1.000);     solution.push_back(1.000);

    for (int i = 0; i < curr_sphere.size(); i++){
        for (int ii = 0; ii < 6; ii++){
            cout << "x position is: " <<  curr_sphere[i].x << endl;

            // Setting which direction to check
            if (ii == 0){
                if (curr_sphere[i].next.up >= 0){
                    dir = curr_sphere[i].next.up;
                }
            }
            else dir = i;

            if (ii == 1){
                if (curr_sphere[i].next.down >= 0){
                    dir = curr_sphere[i].next.down;
                }
                else dir = i;
            }

            if (ii == 2){
                if (curr_sphere[i].next.left >= 0){
                    dir = curr_sphere[i].next.left;
                }
                else dir = i;
            }

            if (ii == 3){
                if (curr_sphere[i].next.right >= 0){
                    dir = curr_sphere[i].next.right;
                }
                else dir = i;
            }

            if (ii == 4){
                if (curr_sphere[i].next.forw >= 0){
                    dir = curr_sphere[i].next.forw;
                }
                else dir = i;
            }

            if (ii == 5){
                if (curr_sphere[i].next.back >= 0){
                    dir = curr_sphere[i].next.back;
                }
                else dir = i;
            }

            // Finding all necessary parameters between two points
            del_x = curr_sphere[i].x - curr_sphere[dir].x;
            del_y = curr_sphere[i].y - curr_sphere[dir].y;
            del_z = curr_sphere[i].z - curr_sphere[dir].z;
            if ( del_x != 0 && del_y != 0 && del_z !=0){
                theta_xy = atan( del_y / del_x);
                theta_zy = atan( del_y / del_z);
                theta_zx = atan( del_x / del_z);
                theta_yx = atan( del_x / del_y);
                theta_xz = atan( del_z / del_x);
                theta_yz = atan( del_z / del_x);
            }
            else{
                theta_xy = 0;
                theta_zy = 0;
                theta_zx = 0;
                theta_yx = 0;
                theta_xz = 0;
                theta_yz = 0;

            }
            cout << del_x << '\t' << dir << '\t' << del_y << '\t' << del_z
                 << '\t' << theta_xy << '\t' << theta_zy << endl;

            del_tot = (del_x*del_x) + (del_y*del_y) + (del_z*del_z);
            cout << del_tot << endl;

            del_vx = curr_sphere[i].v_x - curr_sphere[dir].v_x;
            del_vy = curr_sphere[i].v_y - curr_sphere[dir].v_y;
            del_vz = curr_sphere[i].v_z - curr_sphere[dir].v_z;
            cout << del_vx << '\t' << del_vy << '\t' << del_vz << endl;

            vel_tot = sqrt (del_vx*del_vx + del_vy*del_vy + del_vz*del_vz);

            // Now solving Hooke's Law
            solution[0] = del_tot;     solution[1] = vel_tot;

            solution = hookes(solution[0], solution[1], params);

            // Intereting solution
            del_x = solution[0] * cos(theta_xy);
            del_y = solution[0] * sin(theta_xy);
            del_z = solution[0] * cos(theta_zy);
            del_vx = solution[1] * cos(theta_xy);
            del_vy = solution[1] * sin(theta_xy);
            del_vz = solution[1] * cos(theta_zy);

            // Adding the change in distance...
            curr_sphere[i].x += (0.5 * del_x);
            curr_sphere[i].y += (0.5 * del_y);
            curr_sphere[i].z += (0.5 * del_z);
            curr_sphere[dir].x += (0.5 * del_x);
            curr_sphere[dir].y += (0.5 * del_y);
            curr_sphere[dir].z += (0.5 * del_z);

            // Adding the change in velocity...
            curr_sphere[i].v_x += (0.5 * del_vx);
            curr_sphere[i].v_y += (0.5 * del_vy);
            curr_sphere[i].v_z += (0.5 * del_vz);
            curr_sphere[dir].v_x += (0.5 * del_vx);
            curr_sphere[dir].v_y += (0.5 * del_vy);
            curr_sphere[dir].v_z += (0.5 * del_vz);

        }

        // Adding the change in distance due to overall velocity of point
        curr_sphere[i].x += params.timestep * curr_sphere[i].v_x;
        curr_sphere[i].y += params.timestep * curr_sphere[i].v_y;
        curr_sphere[i].z += params.timestep * curr_sphere[i].v_z;

    }

return curr_sphere;
}

// Now I need a function to write everything to a file.
void write_file(vector<point> points){

    ofstream output("/storage/output/out.dat", 
                    std::ofstream::out | std::ofstream::app);
    if (output.is_open()){
        for (int i = 0; i < points.size(); i++){
            output << points[i].x << '\t' << points[i].y << '\t' 
                   << points[i].z << '\t' << points[i].v_x << '\t'
                   << points[i].v_y << '\t' << points[i].v_z 
                   << endl;
        }
        
        output.close();
    }
    else cout << "Cannot open output file. Sorry. =/" << endl;

}

// I may need to clear the output at the start of each run...
void clear_output(){
    ofstream output("/storage/output/out.dat");
    if (output.is_open()){
        output.clear();
        output.close();
    }
    else cout << "Cannot open output file. Sorry. =/" << endl;

}
