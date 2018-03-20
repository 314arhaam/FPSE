//
//  physics.h
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef physics_h
#define physics_h

#include "collision.h"

/*double collisionDynamics(collision dict){//here, collisionDict is correct. read more about upCasting
    if (dict.wallNum == 0 || dict.wallNum == 1){
        dict.primary.u = -dict.primary.u*eps_w;
    }
    else if (dict.wallNum == 2 || dict.wallNum == 3){
        dict.p;
        this->v = -this->v*eps_w;
    }
    return 0;
}*/

double collisionDynamics(collision *dict){
	double *Vp, eps_p = 0.8;
	Vp = new double[2]{dict->primary->u, dict->primary->v};
	double theta;
	if (dict->isWall == true){
		if (dict->wallNum == 0 || dict->wallNum == 1){
        	//dict->primary->u = -dict->primary->u*0.8;
        	theta = M_PI/2;
    	}
    	else if (dict->wallNum == 2 || dict->wallNum == 3){
        	//dict->primary->v = -dict->primary->v*0.8;
        	theta = 0;
    	}
		double *rotated_velocity_primary = utility::rotate(Vp, theta), S0, B[2], C0;
	    S0 = (rotated_velocity_primary[0] + dict->primary->omega*dict->primary->radius);
	    B[0] = 1/dict->primary->Mass + pow(dict->primary->radius, 2)/dict->primary->momentOfInertia;
		rotated_velocity_primary[0] += -S0/(B[0]*dict->primary->Mass);
		C0 = rotated_velocity_primary[1];
		B[1] = 1/dict->primary->Mass;
		rotated_velocity_primary[1] += -(1 + eps_p)*C0/(B[1]*dict->primary->Mass);
		dict->primary->omega += -S0*dict->primary->radius/(B[0]*dict->primary->momentOfInertia);
		double *a = utility::rotate(rotated_velocity_primary, -theta);
	    dict->primary->u = a[0];
	    dict->primary->v = a[1];
	}
	else{
	double *Vs;
	Vs = new double[2]{dict->secondary->u, dict->secondary->v};
	theta = atan(utility::true_divide(dict->primary->x - dict->secondary->x, dict->primary->y - dict->secondary->y));
    double
	    *rotated_velocity_primary = utility::rotate(Vp, theta),
        *rotated_velocity_secondary = utility::rotate(Vs, theta),
        S0, B[2], C0;
    //Calculation of dynamics
    S0 = (rotated_velocity_primary[0] + dict->primary->omega*dict->primary->radius) - (rotated_velocity_secondary[0] - dict->secondary->omega*dict->secondary->radius);
    B[0] = 1/dict->primary->Mass + pow(dict->primary->radius, 2)/dict->primary->momentOfInertia + 1/dict->secondary->Mass + pow(dict->secondary->radius, 2)/dict->secondary->momentOfInertia;
    rotated_velocity_primary[0] += -S0/(B[0]*dict->primary->Mass);
    rotated_velocity_secondary[0] += S0/(B[0]*dict->secondary->Mass);
    C0 = rotated_velocity_primary[1] - rotated_velocity_secondary[1];
    B[1] = 1/dict->primary->Mass + 1/dict->secondary->Mass;
    rotated_velocity_primary[1] += -(1 + eps_p)*C0/(B[1]*dict->primary->Mass);
    rotated_velocity_secondary[1] += (1 + eps_p)*C0/(B[1]*dict->secondary->Mass);
    
	dict->primary->omega += -S0*dict->primary->radius/(B[0]*dict->primary->momentOfInertia);
    dict->secondary->omega += -S0*dict->secondary->radius/(B[0]*dict->secondary->momentOfInertia);
    
	//dict->primary->vPtr = utility::rotate(rotated_velocity_primary, theta);
	double *b = utility::rotate(rotated_velocity_primary, -theta);
    dict->primary->u = b[0];
    dict->primary->v = b[1];
    //dict->primary->velocityVector[0] = dict->primary->u;
    //dict->primary->velocityVector[1] = dict->primary->v;
    double *c = utility::rotate(rotated_velocity_secondary, -theta);
    dict->secondary->u = c[0];
    dict->secondary->v = c[1];
    //dict->secondary->velocityVector[0] = dict->secondary->u;
    //dict->secondary->velocityVector[1] = dict->secondary->v;
    
	/*simple dyn
	double t = dict->primary->v;
    dict->primary->v = dict->secondary->v;
    dict->secondary->v = t;*/
    delete Vs, Vp;
	}
    return 1;
}
#endif /* physics_h */
