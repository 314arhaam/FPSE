//
//  particle.hpp
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef particle_h
#define particle_h

#include <stdio.h>
#include <cmath>
#include "geometry.h"
#include "collision.h"
struct list{
    double T;
    int a;
    char* s;
};
struct Geom{
	double length = 2;
	double width = 2;
} geom;
class particle{
public:
    //geometry *gPtr;
    double x, y, radius, u, v, omega, density,
    volume, momentOfInertia, Mass, eps_w = 0.8, eps_p = 0.8, velocityVector[2], *vPtr;
    /*Constructor of particle*/
    particle(){
	}
	particle(
				double X,
				double Y,
				//geometry *A,
				double Radius = 0.01,
				double U = 0,
				double V = 0,
				double Omega = 0,
				double Density = 2600
            )
            {
                x = X;
                y = Y;
                u = U;
                v = V;
                radius = Radius;
                density = Density;
                omega = Omega;
                velocityVector[0] = u;
                velocityVector[1] = v;
                vPtr = velocityVector;
                this->physicalProps();
            }
    void move(double dt){
        this->x += this->u*dt;
        this->y += this->v*dt;
        //std::cout<<"\nv =		"<<y;
    }
    list nearestWall(){
        list L;
        double wallTime[4];
        double U[4] = { -this->u, this->u, -this->v, this->v };
        double D[4] = { this->x - this->radius, -this->x + 3 - this->radius, this->y - this->radius, -this->y + 8 - this->radius};
        for (int i = 0; i < 4; i++){
            wallTime[i] = utility::utd(D[i], U[i]);
        }
        L.a = utility::argMin(wallTime, 4);
        L.T = wallTime[L.a];
        return L;
    }
private:
    void physicalProps(){
        volume = (4/3)*M_PI*pow(radius, 3);
        Mass = density*volume;
        momentOfInertia = 0.4*Mass*pow(radius, 2);
    }
};


#endif /* particle_h */
