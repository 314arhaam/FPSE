//
//  simulationUtilities.h
//  DPM
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef simulationUtilities_h
#define simulationUtilities_h

#include <limits>
#include <cmath>

namespace utility
{
	double true_divide(double x, double y)
	{
		return y==0 ? std::numeric_limits<double>::max() : x/y;
	}
	double utd(double x, double y)
	{
		return (x*y <= 0) ? std::numeric_limits<double>::max() : true_divide(x, y);
	}
	int argMin(double array[], int length)
	{
		int argMin = 0;
		double *min = new double(array[argMin]);
		for (int i = 0; i < length; i++)
			{
				if (*min > array[i])
					{
						argMin = i;
						min = new double(array[argMin]);
					}
			}
		delete min;
		return argMin;
	}
	double *rotate(double vector[], double theta)
	{
		double* rotated = new double[2];
		rotated[0] = vector[0]*cos(theta) - vector[1]*sin(theta);
		rotated[1] = vector[0]*sin(theta) + vector[1]*cos(theta);
		return rotated;
	}
	double dot_product(double v1[], double v2[])
	{
		return v1[0]*v2[0] + v1[1]*v2[1];
	}
}

#endif /* simulationUtilities_h */
