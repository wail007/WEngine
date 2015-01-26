#ifndef W_MATH_UTIL_H
#define W_MATH_UTIL_H

#include <cmath>
#include <cfloat>
#include <stdlib.h>




namespace WMath
{
	///////////////////////////////Some constants/////////////////////////
const double PI					= 3.141592653589793;
const double TWO_PI				= 6.283185307179586;
const double HALF_PI			= 1.570796326794897;
const double INV_PI				= 0.318309886183791;
const double INV_TWO_PI			= 0.159154943091895;

const double SQRT_2				= 1.414213562373095;
const double INV_SQRT_2			= 0.707106781186547;

const float	 MAX_FLOAT			= FLT_MAX;
const double MAX_DOUBLE			= DBL_MAX;

const float  EPSILON_FLOAT		= FLT_EPSILON;
const double EPSILON_DOUBLE		= DBL_EPSILON;

const float  TOLERANCE_FLOAT	= 1e-06f;
const double TOLERANCE_DOUBLE	= 1e-08	;
	//////////////////////////////////////////////////////////////////////


	///////////////Epsilon values for simple and doule precision//////////
	template<typename Real> inline Real tolerance();

	template<> inline float tolerance<float>()
	{
		return TOLERANCE_FLOAT;
	}

	template<> inline double tolerance<double>()
	{
		return TOLERANCE_DOUBLE;
	}
	//////////////////////////////////////////////////////////////////////

	template<typename Real> Real degToRad(Real in_deg) { return in_deg * 0.017453292519943; }
	template<typename Real> Real radToDeg(Real in_rad) { return in_rad * 57.295779513082321;}

	/////////////////////Trigonometric functions//////////////////////////
	template<typename Real> Real sin(Real in_rad) { return std::sin(in_rad); }
	template<typename Real> Real cos(Real in_rad) { return std::cos(in_rad); }
	template<typename Real> Real tan(Real in_rad) { return std::tan(in_rad); }
						    
	template<typename Real> Real arcSin(Real in_val) { return std::asin(in_val); }
	template<typename Real> Real arcCos(Real in_val) { return std::acos(in_val); }
	template<typename Real> Real arcTan(Real in_val) { return std::atan(in_val); }

	template<typename Real> Real arcTan2(Real in_x, Real in_y) { return std::atan2(in_y, in_x); }
	//////////////////////////////////////////////////////////////////////



	////////////////////////Power Functions///////////////////////////////
	//template<typename Numeric>	Numeric	pow(Numeric in_base, Numeric in_exp);
	//template<typename Real>		Real	exp(Real in_val);
	//template<typename Real>		Real	sqr(Real in_val);
	template<typename Real> inline Real	sqrt(Real in_val);

	template<> inline float sqrt(float in_val)
	{
		return std::sqrtf(in_val);
	}

	template<> inline double sqrt(double in_val)
	{
		return std::sqrt(in_val);
	}

	//template<typename Real>		Real	invSqrt(Real in_val);
	////////////////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////Utility functions///////////////////////////
	//template<typename Numeric>	Numeric sign(Numeric in_val);
	//template<typename Numeric>	Numeric clamp(Numeric in_val, Numeric in_min, Numeric in_max);
	//template<typename Numeric>	Numeric abs(Numeric in_val);
	//template<typename Real>		Real	ceil(Real in_val);
	//template<typename Real>		Real	floor(Real in_val);
	//template<typename Real>		Real	mod(Real in_op1, Real in_op2);
	//void seedRand(unsigned int in_seed)
	//{
	//	srand(in_seed);
	//}

	template<typename Real>	Real intervalRand(Real in_min, Real in_max)
	{
		return in_min + (in_max - in_min) * ((Real)rand() / (Real)RAND_MAX);
	}
	////////////////////////////////////////////////////////////////////////
	







};


#endif
