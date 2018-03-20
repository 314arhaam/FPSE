//
//  solidPhase.h
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef solidPhase_h
#define solidPhase_h

#define N_MAX 100000

#include "particle.h"
#include "collision.h"
#include "simulationUtilities.h"
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;
class solidPhase{
public:
	//collision _col_;
    const double g = -9.81;
    int numberOfParticles = 10;
    int N = 0;
    particle *particleList[N_MAX];
    particle x;
    collision _col_;
    solidPhase(int m, int n){
        numberOfParticles = m*n;
        int N = 0;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
            	particleList[N] = 
				new particle
	                        (
	                            1 + i*0.25,         //x
	                            1 + j*0.25,         //y
	                            0.1,      //Radius
	                            5 * pow(-1, i),       //u
	                            5 * pow(-1, i+1),       //v
	                            0.0,       //Omega
	                            2660.0    //rho
	                        );
			N++;
			}
    	}
    }
    solidPhase(int m){
    	numberOfParticles = m;
    	for (int i = 0; i<m; i++){
    		particleList[i] = 
				new particle
	                        (
	                            i + 0.2,         //x
	                            5,         //y
	                            0.15,      //Radius
	                            5*pow(-1, i),       //u
	                            -10,       //v
	                            0.0,       //Omega
	                            2660.0    //rho
	                        );
		}
	}
    void gravity(double dt){
        for (int i=0; i<numberOfParticles; i++) particleList[i]->v += -9.81*dt;
    }
    collision* collisionListGenerator(){
        collision *collisionPtr[N_MAX], *C[N_MAX], *collisionPtr1;
        double R12[2], V12[2], _T, A, B, Delta;
        for (int i=0; i<numberOfParticles; i++){
            collisionPtr[i] = new collision(particleList[i]);                         //wall collision data object
            for (int j = i+1; j<numberOfParticles; j++){
                R12[0] = particleList[i]->x - particleList[j]->x;
                R12[1] = particleList[i]->y - particleList[j]->y;
                V12[0] = particleList[i]->u - particleList[j]->u;
                V12[1] = particleList[i]->v - particleList[j]->v;
                A = -utility::dot_product(R12, V12);
                B = utility::dot_product(V12, V12);
                Delta =
						+ pow(A, 2) 
						- B*(pow(R12[0], 2) + pow(R12[1], 2)
						- pow((particleList[i]->radius + particleList[j]->radius), 2));
                if (A>=0 && Delta>=0){
                    _T = utility::utd(A-sqrt(Delta), B);
                    if (_T <= collisionPtr[i]->collisionTime){                                                         //finding minimum collision time
                        collisionPtr[i] = new collision(particleList[i], particleList[j], _T);
                    }
                }
            }
        }
        double min = std::numeric_limits<double>::max();
        for (int i = 0; i < numberOfParticles; i++){
        	if (collisionPtr[i]->collisionTime <= min){
        		min = collisionPtr[i]->collisionTime;
        		collisionPtr1 = collisionPtr[i];
			}
		}
		//delete collisionPtr;
        /*for (int i = 0; i<numberOfParticles; i++){
            collisionTimesList[indice + i + 1] = new collisionDict(i, (particleList[i]->distanceFromWall()->x), (particleList[i]->distanceFromWall()->y));
        }*/
        //collision COLLISION(collisionPtr1->primary, collisionPtr1->secondary, collisionPtr1->collisionTime);
        //delete collisionPtr1;
                    //std::cout<<"\nthechosencoltim"<<collisionPtr1->collisionTime;
                    //collision c(particleList[1]);
        //collision c = *collisionPtr1;
        //_col_ = c;
        //_col_ = *collisionPtr1;
		//delete collisionPtr;
		return collisionPtr1;//[0];
    }
    double run(double T = 2){
        double DT = 0.01, acctim, ROC = 0.99, Time = 0, dt;
        int timeStep = 0;
        collision* col;
        while (Time <= T){
            acctim = 0;
            col = collisionListGenerator();
            //collisionListGenerator();
			dt = col->collisionTime;
            //dt = _col_.collisionTime;
			acctim += ROC*dt;
            while (acctim < DT){
                for (int i = 0; i<numberOfParticles; i++) particleList[i]->move(ROC*dt);
					collisionDynamics(col);
		            col = collisionListGenerator();
		            //collisionListGenerator();
					dt = col->collisionTime;
		            //dt = _col_.collisionTime;
                acctim += ROC*dt;
            }
            for (int i = 0; i<numberOfParticles; i++) particleList[i]->move(DT - (acctim - ROC*dt));
				ofstream myfile("CSV//Output.csv." + std::to_string(timeStep));
				myfile<<"x, y, z, r, U,\n";
				for (int i = 0; i<numberOfParticles; i++){
					myfile<<"\n"<<particleList[i]->x<<", "<<particleList[i]->y<<", 0,"<<particleList[i]->radius<<" ,"<<sqrt(pow(particleList[i]->u, 2) + pow(particleList[i]->v, 2))<<",";
				}
				myfile.close();
				printf("\ndata is written in file %d and closed %f", timeStep, dt);
			gravity(DT);
            Time += DT;
            timeStep++;
        }
    }
};

#endif /* solidPhase_h */
