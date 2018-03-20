//
//  main.cpp
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include "simulationUtilities.h"
#include "collision.h"
#include "particle.h"
#include "physics.h"
#include "solidPhase.h"

int main(int argc, const char * argv[]) {
    particle p(6, 7);
    solidPhase a(5, 20);
    a.run(3);
    return 0;
}
