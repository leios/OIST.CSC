/*-------------brownian.cpp---------------------------------------------------//
*
*              What Color is BROWNian Motion?
*
* Purpose: This will be a simple Brownian motion simulation. I will throw the
*          results into vbots and get out some 3-d motion and such.
*
*          I will then do some Doppler shift stuff to see how the color changes
*          based on the velocity of the initial particles (assuming they are 
*          emitting light and are moving relatively fast). 
*
*   State: Currently adding in the hard_sphere collisions. Woo!
*
*   Notes: I should massacre the vbots code and stick it into this by imbedding
*          python into c++ code. This is somewhat documented online. This would
*          mean that I could generate a series of png files rather than output
*          files in the end, saving a good bit or writing time and space.
*
*          When compiling with vbots support (for later), uncomment the 
*          following line:
*              #include <Python.h>
*          And add the following flag when compiling:
*              -I/usr/include/python3.4m
*          If the code still does not work, use this command to find flags:
*              python3.4-config --cflags
*          Note that this will have to work with blender nicely... 
*          TEST!!!
*
*   ERROR: For some reason, the particles are not moving every timestep...
*          I think this is the expected result when no collision occurs.
*
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
//#include <Python.h>

using namespace std;

/*----------------------------------------------------------------------------//
* STRUCTURES AND FUNCTIONS
*-----------------------------------------------------------------------------*/

struct part{
    double radius, mass, x, y, z, vx, vy, vz;             // Particle parameters
};

struct vox_cube{
    double x, y, z, intensity;
};

vector<part> simulate(double cube_length, vector<part> particles, int max_time,
                      double timestep);
vector<vox_cube> doppler(vector<part> motion_path);
vector<part> fill_box(int pnum, double cube_length, double max_vel, double r1,
                      double r2, double mass_1, double mass_2);
vector <part> hard_sphere(part part_1, part part_2, double timestep);

/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/

int main(){

    vector<part> particles = fill_box(400, 40, 1, 1, 5, 0.5, 0.5);
    vector<part> motion_path = simulate(40, particles, 10, 1);

    for (int i = 0; i < motion_path.size(); i++){
        cout << motion_path[i].x << endl;
    }
}

/*----------------------------------------------------------------------------//
* SUBROUTINES
*-----------------------------------------------------------------------------*/

// Function to fill the box with randomly positioned initial particles. Note 
// that I should be using random velocities too.
vector<part> fill_box(int pnum, double cube_length, double max_vel, double r1,
                      double r2, double mass_1, double mass_2){

    srand(time(0));
    vector<part> particles;
    part particle;

    // Let's go ahead and set the large particle in the middle
    particle.x = rand() % 10000 * 0.0001 * cube_length; 
    particle.y = rand() % 10000 * 0.0001 * cube_length; 
    particle.z = rand() % 10000 * 0.0001 * cube_length; 
    particle.vx = rand() % 10000 * 0.0001 * max_vel;
    particle.vy = rand() % 10000 * 0.0001 * max_vel;
    particle.vz = rand() % 10000 * 0.0001 * max_vel;
    particle.radius = r2;
    particle.mass = mass_2;

    particles.push_back(particle);

    // Random number generator
    for (int i= 0; i <= pnum; i++){

        particle.x = rand() % 10000 * 0.0001 * cube_length; 
            while (particle.x > (particles[0].x - r2) &&
                   particle.x < (particles[0].x + r2)){
                particle.x = rand() % 10000 * 0.0001 * cube_length;
                cout << "check " << i + 1 << endl;
            }

        particle.y = rand() % 10000 * 0.0001 * cube_length; 
            while (particle.y > particles[0].y - r2 && 
                   particle.y < particles[0].y + r2){
                particle.y = rand() % 10000 * 0.0001 * cube_length;
            }

        particle.z = rand() % 10000 * 0.0001 * cube_length; 
            while (particle.z > particles[0].z - r2 && 
                   particle.z < particles[0].z + r2){
                particle.z = rand() % 10000 * 0.0001 * cube_length;
            }

        particle.vx = rand() % 10000 * 0.0001 * max_vel;
        particle.vy = rand() % 10000 * 0.0001 * max_vel;
        particle.vz = rand() % 10000 * 0.0001 * max_vel;
        particle.radius = r1;
        particle.mass = mass_2;

        particles.push_back(particle);

    }

    for (int i = 0; i < particles.size(); i++){
        cout << i << '\t' << particles[i].x << endl;
    }

    return particles;
}

// This should deal with the interactions of the partiocles.
vector<part> simulate(double box_length, vector<part> particles, int max_time,
                      double timestep){

    // We will certainly have to do a hard sphere collision if any two particles
    // become sufficiently close to each other. We should go ahead and add in 
    // a vector of parts...
    vector<part> collision_out, motion_path;
    part particle;

    particle.x = 0; 
    particle.y = 0; 
    particle.z = 0; 
    particle.vx = 0;
    particle.vy = 0;
    particle.vz = 0;
    particle.radius = 0;
    particle.mass = 0;

    collision_out.push_back(particle);
    collision_out.push_back(particle);

    cout << "testing..." << endl;

    // So let's start by moving all the particles forward a single timestep
    for (int i = 0; i < max_time; i++){
        for (int ii = 0; ii < particles.size(); ii++){
            particles[ii].x = particles[ii].vx * timestep;
            if (particles[ii].x > box_length){
                particles[ii].x -= box_length;
            }

            if (particles[ii].x < 0){
                particles[ii].x += box_length;
            }

            particles[ii].y = particles[ii].vy * timestep;
            if (particles[ii].y > box_length){
                particles[ii].y -= box_length;
            }

            if (particles[ii].y < 0){
                particles[ii].y += box_length;
            }

            particles[ii].z = particles[ii].vz * timestep;
            if (particles[ii].z > box_length){
                particles[ii].z -= box_length;
            }

            if (particles[ii].z < 0){
                particles[ii].z += box_length;
            }

            // I really don't like all these nested loops...
            for (int iii = 0; iii < particles.size(); iii++){
                if (particles[ii].x > (particles[iii].x - 
                                       particles[iii].radius) &&
                    particles[ii].y > (particles[iii].y - 
                                       particles[iii].radius) &&
                    particles[ii].z > (particles[iii].z - 
                                       particles[iii].radius) &&
                    particles[ii].x < (particles[iii].x + 
                                       particles[iii].radius) &&
                    particles[ii].y < (particles[iii].y + 
                                       particles[iii].radius) &&
                    particles[ii].z < (particles[iii].z + 
                                       particles[iii].radius)){

                    collision_out = hard_sphere(particles[ii], particles[iii],
                                                timestep);

                    // Now, I might have mixed these guys up. Oops.
                    particles[ii] = collision_out[0];
                    particles[iii] = collision_out[1];
                }
            }


        }

    // Now we need to keep track of the motion path of the large particle. Each
    // element is a timestep
    motion_path.push_back(particles[0]);
    }

return motion_path;
}

// I may need to perform a "hard sphere collision" if the smaller particle is
// within the radius of the larger particle. I think I'll assume that the radius
// of the smaller particle is sufficiently small that I don't have to worry 
// about it. I will also assume that the larger particle's radius will fluctuate
// by an amount that varies with the timestep such that it will "catch" all the
// particles after they have already pierced the shell.
vector<part> hard_sphere(part part_1, part part_2, double timestep){

    // Creating the solutions vector
    vector<part> collision_out;

    vector <part> soln;
    
    part particle;

    particle.x = 0; 
    particle.y = 0; 
    particle.z = 0; 
    particle.vx = 0;
    particle.vy = 0;
    particle.vz = 0;
    particle.radius = 0;
    particle.mass = 0;

    soln.push_back(particle);
    soln.push_back(particle);


    // This is a time-driven simulation, we will need to define a global 
    // variable to ultimately find the final velocity.

    double del_vx = part_2.vx - part_1.vx;
    double del_vy = part_2.vy - part_1.vy;
    double del_vz = part_2.vz - part_1.vz;
    double del_x = part_2.x - part_1.x;
    double del_y = part_2.y - part_1.y;
    double del_z = part_2.z - part_1.z;
    double sigma = part_1.radius + part_2.radius;

    double J = (2 * part_1.mass * part_2.mass *
               ((del_vx * del_x) + (del_vy * del_y) + (del_vz * del_z)) /
               (sigma * (part_1.mass + part_2.mass)));
         
    // Now we need to perform the collision

    soln[0].vx = part_1.vx + (J * del_x) / (sigma * part_1.mass);
    soln[0].vy = part_1.vy + (J * del_y) / (sigma * part_1.mass);
    soln[0].vz = part_1.vz + (J * del_z) / (sigma * part_1.mass);
    soln[1].vx = part_2.vx + (J * del_x) / (sigma * part_2.mass);
    soln[1].vy = part_2.vy + (J * del_y) / (sigma * part_2.mass);
    soln[1].vz = part_2.vz + (J * del_z) / (sigma * part_2.mass);

    soln[0].mass = part_1.mass;
    soln[0].radius = part_1.radius;
    soln[1].mass = part_2.mass;
    soln[1].radius = part_2.radius;

    soln[0].x = part_1.x + (soln[0].vx * timestep);
    soln[0].y = part_1.y + (soln[0].vy * timestep);
    soln[0].z = part_1.z + (soln[0].vz * timestep);
    soln[1].x = part_2.x + (soln[1].vx * timestep);
    soln[1].y = part_2.y + (soln[1].vy * timestep);
    soln[1].z = part_2.z + (soln[1].vz * timestep);

    // Now, it could be that the particle shoots off the side of the box.
    // Let's fix that.

    for (int q = 0; q <= 1; q++){

        while (soln[q].x > 40){
            soln[q].x -= 40;
        }

        while (soln[q].x < 0){
            soln[q].x += 40;
        }

        while (soln[q].y > 40){
            soln[q].y -= 40;
        }

        while (soln[q].y < 0){
            soln[q].y += 40;
        }

        if (soln[q].z > 40){
            soln[q].z -= 40;
        }

        if (soln[q].z < 0){
            soln[q].z += 40;
        }

    }

    return soln;
}


// The doppler shift stuff will return a 64 X 64 X 64 grid of voxels to use.
// This will have to be written to a file to be used by vbots.
vector<vox_cube> doppler(vector<part> motion_path){
}
