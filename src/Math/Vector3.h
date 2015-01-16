#ifndef W_VECTOR_3
#define W_VECTOR_3

#include "MathUtil.h"
#include <iostream>
#include <assert.h>

#define X m_vec[0]
#define Y m_vec[1]
#define Z m_vec[2]

namespace WMath
{

	template<typename T>
	class Vector3
	{
	public:
		Vector3();
		Vector3(T in_x, T in_y, T in_z);
		Vector3(T in_vec[3]);
		Vector3(const Vector3& in_copy);


		Vector3& operator=(const Vector3& in_copy);
		Vector3& operator=(T in_vec[3]);

		bool operator==(const Vector3& in_vec) const;
		bool operator!=(const Vector3& in_vec) const;

		T	operator[](unsigned int in_index) const;
		T&	operator[](unsigned int in_index);

		Vector3 operator-() const;

		Vector3 operator+(const Vector3& in_vec) const;
		Vector3 operator-(const Vector3& in_vec) const;

		Vector3 operator*(T in_t) const;
		Vector3 operator/(T in_t) const;

		Vector3& operator+=(const Vector3& in_vec);
		Vector3& operator-=(const Vector3& in_vec);

		Vector3& operator*=(T in_t);
		Vector3& operator/=(T in_t);

		operator T*() const;

		inline T x() const;
		inline T y() const;
		inline T z() const;

		inline T& x();
		inline T& y();
		inline T& z();

		T norm()	const;
		T normSqr() const;

		void normalize();

		template<typename T>
		friend Vector3<T> normalize(const Vector3<T>& in_vec);

		template<typename T>
		friend Vector3<T> dot(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2);

		template<typename T>
		friend Vector3<T> cross(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2);

		template<typename T>
		friend Vector3<T> distance(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2);

		template<typename T>
		friend Vector3<T> operator*(T in_t, const Vector3<T>& in_vec);

		template<typename T>
		friend std::ostream& operator<<(std::ostream& out_o, const Vector3<T>& in_vec);

	private:

		T m_vec[3];
	};



	template<typename T>
	Vector3<T>::Vector3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}


	template<typename T>
	Vector3<T>::Vector3(T in_x, T in_y, T in_z)
	{
		X = in_x;
		Y = in_y;
		Z = in_z;
	}


	template<typename T>
	Vector3<T>::Vector3(T in_vec[3])
	{
		*this = in_vec;
	}


	template<typename T>
	Vector3<T>::Vector3(const Vector3<T>& in_copy)
	{
		*this = in_copy;
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator=(const Vector3<T>& in_copy)
	{
		X = in_copy.X;
		Y = in_copy.Y;
		Z = in_copy.Z;

		return *this;
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator=(T in_vec[3])
	{
		X = in_vec[0];
		Y = in_vec[1];
		Z = in_vec[2];

		return *this;
	}


	template<typename T>
	bool Vector3<T>::operator==(const Vector3<T>& in_vec) const
	{
		return	X - tolerance<T>() < in_vec.X && in_vec.X < X + tolerance<T>() &&
				Y - tolerance<T>() < in_vec.Y && in_vec.Y < Y + tolerance<T>() &&
				Z - tolerance<T>() < in_vec.Z && in_vec.Z < Z + tolerance<T>();
	}

	template<typename T>
	bool Vector3<T>::operator!=(const Vector3<T>& in_vec) const
	{
		return !(*this == in_vec);
	}


	template<typename T>
	T	Vector3<T>::operator[](unsigned int in_index) const
	{ 
		assert(in_index < 3);
		return m_vec3[in_index];
	}


	template<typename T>
	T&	Vector3<T>::operator[](unsigned int in_index)
	{ 
		assert(in_index < 3);
		return m_vec3[in_index];
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-() const
	{ 
		return Vector3(-X, -Y, -Z); 
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3<T>& in_vec) const
	{
		return Vector3
		(
			X + in_vec.X,
			Y + in_vec.Y,
			Z + in_vec.Z
		);
	}


	template<typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3<T>& in_vec) const
	{
		return Vector3
		(
			X - in_vec.X,
			Y - in_vec.Y,
			Z - in_vec.Z
		);
	}


	template<typename T>
	Vector3<T> Vector3<T>::operator*(T in_t) const
	{
		return Vector3
		(
			X * in_t,
			Y * in_t,
			Z * in_t
		);
	}


	template<typename T>
	Vector3<T> Vector3<T>::operator/(T in_t) const
	{
		in_t = (T)1 / in_t;	//in_t should not be zero

		return Vector3
		(	
			X * in_t,
			Y * in_t,
			Z * in_t
		);
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& in_vec)
	{
		X += in_vec.X;
		Y += in_vec.Y;
		Z += in_vec.Z;

		return *this;
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& in_vec)
	{
		X -= in_vec.X;
		Y -= in_vec.Y;
		Z -= in_vec.Z;

		return *this;
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(T in_t)
	{
		X *= in_t;
		Y *= in_t;
		Z *= in_t;

		return *this;
	}


	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(T in_t)
	{
		in_t = (T)1 / in_t;	//in_t should not be zero

		X *= in_t;
		Y *= in_t;
		Z *= in_t;

		return *this;
	}


	template<typename T>
	Vector3<T>::operator T*() const  
	{ 
		return m_vec;
	}
	

	template<typename T>
	inline T Vector3<T>::x() const 
	{ 
		return m_vec[0];
	}


	template<typename T>
	inline T Vector3<T>::y() const
	{ 
		return m_vec[1];
	}


	template<typename T>
	inline T Vector3<T>::z() const
	{ 
		return m_vec[2];
	}


	template<typename T>
	inline T& Vector3<T>::x()
	{ 
		return m_vec[0];
	}


	template<typename T>
	inline T& Vector3<T>::y()
	{ 
		return m_vec[1];
	}


	template<typename T>
	inline T& Vector3<T>::z()
	{ 
		return m_vec[2];
	}


	template<typename T>
	T Vector3<T>::norm() const
	{
		return WMath::sqrt(X*X + Y*Y + Z*Z);
	}

	template<typename T>
	T Vector3<T>::normSqr() const
	{
		return X*X + Y*Y + Z*Z;
	}

	template<typename T>
	void Vector3<T>::normalize()
	{
		T invNorm = (T)1 / norm();

		X *= invNorm;
		Y *= invNorm;
		Z *= invNorm;
	}

	template<typename T>
	Vector3<T> normalize(const Vector3<T>& in_vec)
	{
		T invNorm = (T)1 / in_vec.norm();

		return Vector3<T>
		(
			in_vec.X * invNorm,
			in_vec.Y * invNorm,
			in_vec.Z * invNorm
		);
	}

	template<typename T>
	T dot(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2)
	{
		return	in_vec1.X * in_vec2.X + 
				in_vec1.Y * in_vec2.Y +
				in_vec1.Z * in_vec2.Z;
	}

	template<typename T>
	Vector3<T> cross(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2)
	{
		return Vector3<T>	
		(
			in_vec1.Y*in_vec2.Z - in_vec1.Z*in_vec2.Y,
			in_vec1.Z*in_vec2.X - in_vec1.X*in_vec2.Z,
			in_vec1.X*in_vec2.Y - in_vec1.Y*in_vec2.X
		);
	}

	template<typename T>
	T distance(const Vector3<T>& in_vec1, const Vector3<T>& in_vec2)
	{
		T dx = in_vec1.X – in_vec2.X;
		T dy = in_vec1.Y – in_vec2.Y;
		T dz = in_vec1.Z – in_vec2.Z;

		return WMath::sqrt(dx*dx + dy*dy + dz*dz);
	}

	template<typename T>
	Vector3<T> operator*(T in_t, const Vector3<T>& in_vec)
	{
		return Vector3<T>
		(
			in_vec.X * in_t, 
			in_vec.Y * in_t, 
			in_vec.Z * in_t
		);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out_o, const Vector3<T>& in_vec)
	{
		return out_o << "(" << in_vec.X << ", " << in_vec.Y << ", " << in_vec.Z << ")";
	}

	typedef Vector3<float>	Vector3f;
	typedef Vector3<double>	Vector3d;
}

#undef X
#undef Y
#undef Z

#endif