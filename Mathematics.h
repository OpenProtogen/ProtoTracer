#pragma once
#include <math.h> 
#include <WString.h>

class Mathematics {
public:
	static float MPI;

	static float Constrain(float value, float minimum, float maximum);
	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static String DoubleToCleanString(float value);
	static bool IsNaN(float);
	static bool IsInfinite(float);
	static bool IsFinite(float);
	static int Sign(float);
  static int RoundUpWindow(int value, int multiple);

  static float CosineInterpolation(float, float, float);
};
