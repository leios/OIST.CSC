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
*-----------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

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
                      double box_length, double timestep);
vector<vox_cube> dopper(vector<part> particles);
vector<part> fill_box(int pnum, double cube_length, double max_vel, double r1,
                      double r2, double mass_1, double mass_2);
vector <part> hard_sphere(part part_1, part part_2);

/*----------------------------------------------------------------------------//
* MAIN
*-----------------------------------------------------------------------------*/

int main(){

    vector<part> particles = fill_box(40, 40, 40, 1, 5, 0.5, 0.5);
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
vector<part> simulate(double cube_length, vector<part> particles, int max_time,
                      double box_length, double timestep){

    // We will certainly have to do a hard sphere collision if any two particles
    // become sufficiently close to each other. We should go ahead and add in 
    // a vector of parts...
    vector<part> collision_out;
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

                    collision_out = hard_sphere(particles[ii], particles[iii]);
                }
            }


        }
    }
}

// UNFINISHED!!!
// I may need to perform a "hard sphere collision" if the smaller particle is
// within the radius of the larger particle. I think I'll assume that the radius
// of the smaller particle is sufficiently small that I don't have to worry 
// about it. I will also assume that the larger particle's radius will fluctuate
// by an amount that varies with the timestep such that it will "catch" all the
// particles after they have already pierced the shell.
vector<part> hard_sphere(part part_1, part part_2){

    // Creating the solutions vector
    vector<part> collision_out;

    part soln_1, soln_2;

    // First we need to track the change in velocities

    return collision_out;
}


// The doppler shift stuff will return a 64 X 64 X 64 grid of voxels to use.
// This will have to be written to a file to be used by vbots.
vector<vox_cube> dopper(vector<part> particles){
}
