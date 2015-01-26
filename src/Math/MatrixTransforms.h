#ifndef W_MATRIX_TRANSFORMS_H
#define W_MATRIX_TRANSFORMS_H

#include "Matrix3.h"
#include "Matrix4.h"

namespace WMath
{
	template<typename T>
	Matrix3<T> rotate(T in_angleRad, const Vector3<T>& in_axis)
	{
		const Vector3<T> v = normalize(in_axis);

		const T s = WMath::sin(in_angleRad);
		const T c = WMath::cos(in_angleRad);

		const T oneMinusCos = 1 - c;

		return Matrix3<T>
		(
			v.x() * v.x() * oneMinusCos + c,
			v.x() * v.y() * oneMinusCos + v.z() * s,
			v.x() * v.z() * oneMinusCos - v.y() * s,
			v.x() * v.y() * oneMinusCos - v.z() * s,
			v.y() * v.y() * oneMinusCos + c,
			v.y() * v.z() * oneMinusCos + v.x() * s,
			v.x() * v.z() * oneMinusCos + v.y() * s,
			v.y() * v.z() * oneMinusCos - v.x() * s,
			v.z() * v.z() * oneMinusCos + c
		);
	}


	template<typename T>
	void rotate(Matrix3<T>& in_mat, T in_angleRad, const Vector3<T>& in_axis)
	{
		const Vector3<T> n = normalize(in_axis);

		const T s = WMath::sin(in_angleRad);
		const T c = WMath::cos(in_angleRad);

		for (int i = 0; i < 3; i++)
		{
			Vector3<T> v			= in_mat[i];
			Vector3<T> vParallel	= dot(v, n) * n;

			in_mat.setColumn(i, (v - vParallel)*c + cross(n, v)*s + vParallel);
		}
	}


	template<typename T>
	Matrix4<T> rotate(T in_angleRad, const Vector3<T>& in_axis)
	{
		const Vector3<T> v = normalize(in_axis);

		const T s = WMath::sin(in_angleRad);
		const T c = WMath::cos(in_angleRad);

		const T oneMinusCos = 1 - c;

		return Matrix4<T>
		(
			v.x() * v.x() * oneMinusCos + c,
			v.x() * v.y() * oneMinusCos + v.z() * s,
			v.x() * v.z() * oneMinusCos - v.y() * s,
			0,
			v.x() * v.y() * oneMinusCos - v.z() * s,
			v.y() * v.y() * oneMinusCos + c,
			v.y() * v.z() * oneMinusCos + v.x() * s,
			0,
			v.x() * v.z() * oneMinusCos + v.y() * s,
			v.y() * v.z() * oneMinusCos - v.x() * s,
			v.z() * v.z() * oneMinusCos + c
			0,
			0,0,0,1
		);
	}


	template<typename T>
	void rotate(Matrix4<T>& in_mat, T in_angleRad, const Vector3<T>& in_axis)
	{
		const Vector3<T> n = normalize(in_axis);

		const T s = WMath::sin(in_angleRad);
		const T c = WMath::cos(in_angleRad);

		for (int i = 0; i < 3; i++)
		{
			const Vector3<T> v = in_mat[i];
			const Vector3<T> vParallel = dot(v, n) * n;

			in_mat.setColumn(i, (v - vParallel)*c + cross(n, v)*s + vParallel);
		}
	}


	template<typename T>
	Matrix4<T> translate(const Vector3<T>& in_vec)
	{
		return Matrix4<T>
		(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			in_vec.x(), in_vec.y(), in_vec.z(), 1
		);
	}


	template<typename T>
	void translate(Matrix4<T>& in_mat, const Vector3<T>& in_vec)
	{
		T* v = in_mat[3];

		v[0] += in_vec[0];
		v[1] += in_vec[1];
		v[2] += in_vec[2];
	}



	template<typename T>
	Matrix4<T> scale(const Vector3<T>& in_vec)
	{
		return Matrix4<T>
		(
			1 * in_vec.x()	, 0					, 0					, 0,
			0				, 1 * in_vec.y()	, 0					, 0,
			0				, 0					, 1 * in_vec.z()	, 0,
			0				, 0					, 0					, 1
		);
	}


	template<typename T>
	void scale(Matrix4<T>& in_mat, const Vector3<T>& in_vec)
	{
		in_mat[0][0] *= in_vec[0];
		in_mat[1][1] *= in_vec[1];
		in_mat[2][2] *= in_vec[2];
	}


	template<typename T>
	Matrix4<T> lookAt(const Vector3<T>& in_pos, const Vector3<T>& in_dir, const Vector3<T>& in_up = [0, 1, 0])
	{
		const Vector3<T> z = normalize(-in_dir);			//we use a right handed coordinate system. Camera is looking at -z
		const Vector3<T> x = normalize(cross(in_up, z));
		const Vector3<T> y = cross(z, x);					//z and x are perpendicular so the magnitude is preserved by the cross product.
															//no need to normalize since z and x are unit vectors.

		const Vector3<T> t = -in_pos;	//camera is located at the center


		// v = TRv' <=> v' = (TR)^(-1) * v = R^(-1) * T^(-1) * v
		//where v is in world space, v' is in camera space
		//T is a translation matrix, R is a rotation matrix
		return Matrix4<T>
		(
			x.x(),		y.x(),		z.x(),		0,
			x.y(),		y.y(),		z.y(),		0,
			x.z(),		y.z(),		z.z(),		0,
			dot(x,t),	dot(y, t),	dot(z, t),	1
		);
	}


	template<typename T>
	Matrix4<T> frustrum(T in_left, T in_right, T in_bottom, T in_top, T in_near, T in_far)
	{
		//
		//	|	2n/(r-l)	0			(r+l)/(r-l)		0			|
		//	|	0			2n/(t-b)	(t+b)/(t-b)		0			|
		//	|	0			0			-(f+n)/(f-n)	-2fn/(f-n)	|
		//	|	0			0			-1				0			|
		//

		return Matrix4 < T >
		(
			static_cast<T>(2) * in_near / (in_right-in_left), 
			0, 0, 0, 0, 
			static_cast<T>(2) * in_near / (in_top - in_bottom), 
			0, 0,
			(in_right + in_left) / (in_right - in_left), 
			(in_top + in_bottom) / (in_top - in_bottom), 
			-(in_far + in_near) / (in_far - in_near), 
			-1,	0, 0, 
			static_cast<T>(2)*in_far*in_near / (in_near-in_far), 
			0
		);
	}

	template<typename T>
	Matrix4<T> perspective(T in_fovyRad, T in_aspectRatio, T in_near, T in_far)
	{
		//
		//	|	1/ar*tan(fov/2)		0				0				0			|
		//	|	0					1/tan(fov/2)	0				0			|
		//	|	0					0				(-n-f)/(n-f)	2fn/(n-f)	|
		//	|	0					0				-1				0			|
		//


		const invTanHalfFov = static_cast<T>(1) / WMath::tan(in_fovyRad / static_cast<T>(2));

		return Matrix4<T>
		(
			invTanHalfFov / in_aspectRatio, 0, 0, 0,
			0, invTanHalfFov, 0, 0,
			0, 0, (in_near + in_far) / (in_far - in_near), -1,
			0, 0, static_cast<T>(2)*in_far*in_near / (in_near-in_far)
		);
	}

}

#endif