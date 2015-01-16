#ifndef W_QUATERNION_H
#define	W_QUATERNION_H

#include "MathUtil.h"
#include "Vector3.h"
#include <iostream>
#include <assert.h>

#define W m_quat[0]
#define X m_quat[1]
#define Y m_quat[2]
#define Z m_quat[3]

namespace WMath
{
	template<typename T>
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(T in_w, T in_x, T in_y, T in_z);
		Quaternion(T in_quat[4]);
		Quaternion(T in_angleRad, const Vector3<T>& in_axis);
		Quaternion(const Quaternion& in_copy);


		Quaternion& operator=(const Quaternion& in_copy);
		Quaternion& operator=(T in_quat[4]);

		bool operator==(const Quaternion& in_quat) const;
		bool operator!=(const Quaternion& in_quat) const;

		T	operator[](unsigned int in_index) const;
		T&	operator[](unsigned int in_index);

		Quaternion operator*(const Quaternion& in_quat) const;
	
		Quaternion& operator*=(const Quaternion& in_quat);
		
		operator T*() const;

		inline T w() const { return W; }
		inline T x() const { return X; }
		inline T y() const { return Y; }
		inline T z() const { return Z; }

		inline T& w() { return W; }
		inline T& x() { return X; }
		inline T& y() { return Y; }
		inline T& z() { return Z; }

		Quaternion	getConjugate()		const;
		Quaternion	getInverse()		const;
		T			getRotationAngle()	const;
		Vector3<T>	getRotationAxis()	const;

		void setRotation(T in_angleRad, const Vector3<T>& in_vec);

		T norm()	const;
		T normSqr() const;

		void normalize();

		template<typename T>
		friend T dot(const Quaternion<T>& in_quat1, const Quaternion<T>& in_quat2);

		template<typename T>
		friend std::ostream& operator<<(std::ostream& out_o, const Quaternion<T>& in_quat);

	private:

		T m_quat[4];
	};



	template<typename T>
	Quaternion<T>::Quaternion()
	{
		//identity quaternion;
		W = 1; 
		X = 0;
		Y = 0;
		Z = 0;
	}


	template<typename T>
	Quaternion<T>::Quaternion(T in_w, T in_x, T in_y, T in_z)
	{
		W = in_w;
		X = in_x;
		Y = in_y;
		Z = in_z;
	}


	template<typename T>
	Quaternion<T>::Quaternion(T in_quat[4])
	{
		*this = in_quat;
	}

	template<typename T>
	Quaternion<T>::Quaternion(T in_angleRad, const Vector3<T>& in_axis)
	{
		T halfAngle = in_angleRad / (T)2;
		T halfAngleSin = WMath::sin(halfAngle);

		W = WMath::cos(halfAngle);
		X = halfAngleSin * in_axis.x();
		Y = halfAngleSin * in_axis.y();
		Z = halfAngleSin * in_axis.z();
	}

	template<typename T>
	Quaternion<T>::Quaternion(const Quaternion<T>& in_copy)
	{
		*this = in_copy;
	}


	template<typename T>
	Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& in_copy)
	{
		W = in_copy.W;
		X = in_copy.X;
		Y = in_copy.Y;
		Z = in_copy.Z;

		return *this;
	}


	template<typename T>
	Quaternion<T>& Quaternion<T>::operator=(T in_quat[4])
	{
		W = in_quat[0];
		X = in_quat[1];
		Y = in_quat[2];
		Z = in_quat[3];

		return *this;
	}


	template<typename T>
	bool Quaternion<T>::operator==(const Quaternion<T>& in_quat) const
	{
		return	W - tolerance<T>() < in_quat.W && in_quat.W < W + tolerance<T>() &&
				X - tolerance<T>() < in_quat.X && in_quat.X < X + tolerance<T>() &&
				Y - tolerance<T>() < in_quat.Y && in_quat.Y < Y + tolerance<T>() &&
				Z - tolerance<T>() < in_quat.Z && in_quat.Z < Z + tolerance<T>();
	}

	template<typename T>
	bool Quaternion<T>::operator!=(const Quaternion<T>& in_quat) const
	{
		return !(*this == in_quat);
	}


	template<typename T>
	T	Quaternion<T>::operator[](unsigned int in_index) const
	{
		assert(in_index < 4);
		return m_quat[in_index];
	}


	template<typename T>
	T&	Quaternion<T>::operator[](unsigned int in_index)
	{
		assert(in_index < 4);
		return m_quat[in_index];
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& in_quat) const
	{
		return Quaternion<T>
		(
			W*in_quat.W – X*in_quat.X – Y*in_quat.Y – z*in_quat.Z,
			W*in_quat.X + X*in_quat.W + Z*in_quat.Y – y*in_quat.Z,
			W*in_quat.Y + Y*in_quat.W + X*in_quat.Z – z*in_quat.X,
			W*in_quat.Z + Z*in_quat.W + Y*in_quat.X – x*in_quat.Y
		);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& in_quat)
	{
		*this = *this * in_quat;
	}


	template<typename T> 
	Quaternion<T>::operator T*() const 
	{
		return m_quat;
	}


	//For a rotation quaternion(normalized), the conjugate and
	//inverse quternions are equal and represent the opposite rotation.
	template<typename T>
	Quaternion<T> Quaternion<T>::getConjugate() const
	{
		return Quaternion<T>(W, -X, -Y, -Z);
	}

	//For a rotation quaternion(normalized), the conjugate and
	//inverse quternions are equal and represent the opposite rotation.
	template<typename T>
	Quaternion<T> Quaternion<T>::getInverse() const
	{
		T invNorm = (T)1 / norm();

		return Quaternion<T>(W*invNorm, -X*invNorm, -Y*invNorm, -Z*invNorm);
	}

	template<typename T>
	T Quaternion<T>::getRotationAngle() const
	{
		return WMath::arcCos(W) * (T)2;
	}

	template<typename T>
	Vector3<T>	Quaternion<T>::getRotationAxis() const
	{
		//W			= cos(theta/2)
		//(X,Y,Z)	= rotationAxis * sin(theta/2)

		//cos^2(theta) + sin^2(theta) = 1
		//sin^2(theta/2) = 1 - W^2
		//sin(theta/2) = sqrt(1 - W^2)

		T invSinHalfTheta = (T)1 / WMath::sqrt( (T)1 - W*W );

		return Vector3<T>(X*invSinHalfTheta, Y*invSinHalfTheta, Z*invSinHalfTheta);

		return 
	}


	template<typename T>
	void Quaternion<T>::setRotation(T in_angleRad, const Vector3<T>& in_axis)
	{
		const T halfTheta		= in_angleRad / (T)2;
		const T sinHalfTheta	= WMath::sin(halfTheta);

		W = WMath::cos(halfTheta);

		X = in_axis.x() * sinHalfTheta;
		Y = in_axis.y() * sinHalfTheta;
		Z = in_axis.z() * sinHalfTheta;
	}


	template<typename T>
	T Quaternion<T>::norm() const
	{
		return WMath::sqrt(W*W + X*X + Y*Y + Z*Z);
	}

	template<typename T>
	T Quaternion<T>::normSqr() const
	{
		return W*W + X*X + Y*Y + Z*Z;
	}

	template<typename T>
	void Quaternion<T>::normalize()
	{
		T invNorm = (T)1 / norm();

		W *= invNorm;
		X *= invNorm;
		Y *= invNorm;
		Z *= invNorm;
	}

	template<typename T>
	T dot(const Quaternion<T>& in_quat1, const Quaternion<T>& in_quat2)
	{
		return	in_quat1.W * in_quat2.W +
				in_quat1.X * in_quat2.X +
				in_quat1.Y * in_quat2.Y +
				in_quat1.Z * in_quat2.Z;
	}


	template<typename T>
	std::ostream& operator<<(std::ostream& out_o, const Quaternion<T>& in_quat)
	{
		Vector3<T>	axis	= in_quat.getRotationAxis();
		T			angle	= in_quat.getRotationAngle();

		return out_o << "( cos(" << angle << "/2), " << axis << " * sin(" << angle << "/2) )";
	}

	typedef Quaternion<float>	Quaternionf;
	typedef Quaternion<double>	Quaterniond;
}

#undef W
#undef X
#undef Y
#undef Z

#endif