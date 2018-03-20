//
//  geometry.h
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef geometry_h
#define geometry_h

#include <stdio.h>

class geometry{
public:
    double length, width;
    geometry(double L=1000, double W=1000){length = L; width = W;}
}
G(10, 10);     //default geometry constructor

#endif /* geometry_h */
