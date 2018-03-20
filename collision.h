//
//  collision.h
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef collision_h
#define collision_h

#include "particle.h"

class collision{
public:
    int wallNum;
    double collisionTime;
    bool isWall = true;
    particle *primary, *secondary = NULL;
    collision(){
	}
	collision(particle* A){
    	primary = A;
    	list* L = new list(primary->nearestWall());
    	wallNum = L->a;
    	collisionTime = L->T;
    	delete L;
	}
    collision(particle* A, int wall_number, double collision_time){
        primary = A;
        wallNum = wall_number;
        collisionTime = collision_time;
    }
    collision(particle* A, particle* B, double collision_time){
        collisionTime = collision_time;
        primary = A;
        secondary = B;
        isWall = false;
    }
};
#endif /* collision_h */
