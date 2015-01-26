#ifndef W_VECTOR_4
#define W_VECTOR_4

#include "MathUtil.h"
#include <iostream>
#include <assert.h>

#define X m_vec[0]
#define Y m_vec[1]
#define Z m_vec[2]
#define W m_vec[3]


namespace WMath
{

	template<typename T>
	class Vector4
	{
	public:
		Vector4();
		Vector4(T in_x, T in_y, T in_z, T in_w);
		Vector4(T in_vec[4]);
		Vector4(const Vector4& in_copy);


		Vector4& operator=(const Vector4& in_copy);
		Vector4& operator=(T in_vec[4]);

		T	operator[](unsigned int in_index) const;
		T&	operator[](unsigned int in_index);

		Vector4 operator-() const;

		Vector4 operator+(const Vector4& in_vec) const;
		Vector4 operator-(const Vector4& in_vec) const;

		Vector4 operator*(T in_t) const;
		Vector4 operator/(T in_t) const;

		Vector4& operator+=(const Vector4& in_vec);
		Vector4& operator-=(const Vector4& in_vec);

		Vector4& operator*=(T in_t);
		Vector4& operator/=(T in_t);

		operator T*();
		operator T*() const;

		inline T x() const { return m_vec[0]; }
		inline T y() const { return m_vec[1]; }
		inline T z() const { return m_vec[2]; }
		inline T w() const { return m_vec[3]; }

		inline T& x() { return m_vec[0]; }
		inline T& y() { return m_vec[1]; }
		inline T& z() { return m_vec[2]; }
		inline T& w() { return m_vec[3]; }

		T norm()	const;
		T normSqr() const;

		void normalize();

		template<typename T>
		friend Vector4<T> dot(const Vector4<T>& in_vec1, const Vector4<T>& in_vec2);

		template<typename T>
		friend Vector4<T> distance(const Vector4<T>& in_vec1, const Vector4<T>& in_vec2);

		template<typename T>
		friend Vector4<T> operator*(T in_t, const Vector4<T>& in_vec);

		template<typename T>
		friend std::ostream& operator<<(std::ostream& out_o, const Vector4<T>& in_vec);

	private:

		T m_vec[4];
	};



	template<typename T>
	Vector4<T>::Vector4()
	{
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}


	template<typename T>
	Vector4<T>::Vector4(T in_x, T in_y, T in_z, T in_w)
	{
		X = in_x;
		Y = in_y;
		Z = in_z;
		W = in_w;
	}


	template<typename T>
	Vector4<T>::Vector4(T in_vec[4])
	{
		*this = in_vec;
	}


	template<typename T>
	Vector4<T>::Vector4(const Vector4<T>& in_copy)
	{
		*this = in_copy;
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator=(const Vector4<T>& in_copy)
	{
		X = in_copy.X;
		Y = in_copy.Y;
		Z = in_copy.Z;
		W = in_copy.W;

		return *this;
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator=(T in_vec[3])
	{
		X = in_vec[0];
		Y = in_vec[1];
		Z = in_vec[2];
		W = in_vec[3];

		return *this;
	}


	template<typename T>
	T	Vector4<T>::operator[](unsigned int in_index) const
	{
		assert(in_index < 4);
		return m_vec3[in_index];
	}


	template<typename T>
	T&	Vector4<T>::operator[](unsigned int in_index)
	{
		assert(in_index < 4);
		return m_vec3[in_index];
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-() const
	{
		return Vector4(-X, -Y, -Z, -W);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator+(const Vector4<T>& in_vec) const
	{
		return Vector4
		(
			X + in_vec.X,
			Y + in_vec.Y,
			Z + in_vec.Z,
			W + in_vec.W
		);
	}


	template<typename T>
	Vector4<T> Vector4<T>::operator-(const Vector4<T>& in_vec) const
	{
		return Vector4
		(
			X - in_vec.X,
			Y - in_vec.Y,
			Z - in_vec.Z,
			W - in_vec.W
		);
	}


	template<typename T>
	Vector4<T> Vector4<T>::operator*(T in_t) const
	{
		return Vector4
		(
			X * in_t,
			Y * in_t,
			Z * in_t,
			W * in_t
		);
	}


	template<typename T>
	Vector4<T> Vector4<T>::operator/(T in_t) const
	{
		in_t = static_cast<T>(1) / in_t;	//in_t should not be zero

		return Vector4
		(
			X * in_t,
			Y * in_t,
			Z * in_t
			W * in_t
		);
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& in_vec)
	{
		X += in_vec.X;
		Y += in_vec.Y;
		Z += in_vec.Z;
		W += in_vec.W;

		return *this;
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& in_vec)
	{
		X -= in_vec.X;
		Y -= in_vec.Y;
		Z -= in_vec.Z;
		W -= in_vec.W;

		return *this;
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator*=(T in_t)
	{
		X *= in_t;
		Y *= in_t;
		Z *= in_t;
		W *= in_t;

		return *this;
	}


	template<typename T>
	Vector4<T>& Vector4<T>::operator/=(T in_t)
	{
		in_t =  static_cast<T>(1) / in_t;	//in_t should not be zero

		X *= in_t;
		Y *= in_t;
		Z *= in_t;
		W *= in_t;

		return *this;
	}


	template<typename T>
	Vector4<T>::operator T*()
	{
		return m_vec;
	}

	template<typename T>
	Vector4<T>::operator T*() const 
	{
		return (T*)m_vec;
	}


	template<typename T>
	T Vector4<T>::norm() const
	{
		return WMath::sqrt(X*X + Y*Y + Z*Z + W*W);
	}

	template<typename T>
	T Vector4<T>::normSqr() const
	{
		return X*X + Y*Y + Z*Z + W*W;
	}

	template<typename T>
	void Vector4<T>::normalize()
	{
		T invNorm =  static_cast<T>(1) / norm();

		X *= invNorm;
		Y *= invNorm;
		Z *= invNorm;
		W *= invNorm;
	}

	template<typename T>
	T dot(const Vector4<T>& in_vec1, const Vector4<T>& in_vec2)
	{
		return	in_vec1.X * in_vec2.X +
				in_vec1.Y * in_vec2.Y +
				in_vec1.Z * in_vec2.Z +
				in_vec1.W * in_vec2.W;
	}

	template<typename T>
	T distance(const Vector4<T>& in_vec1, const Vector4<T>& in_vec2)
	{
		T dx = in_vec1.X – in_vec2.X;
		T dy = in_vec1.Y – in_vec2.Y;
		T dz = in_vec1.Z – in_vec2.Z;
		T dw = in_vec1.W – in_vec2.W;

		return WMath::sqrt(dx*dx + dy*dy + dz*dz + dw*dw);
	}

	template<typename T>
	Vector4<T> operator*(T in_t, const Vector4<T>& in_vec)
	{
		return *this * in_t;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& out_o, const Vector4<T>& in_vec)
	{
		return out_o << "(" << in_vec.X << ", " << in_vec.Y << ", " << in_vec.Z << ", " << in_vec.W << ")";
	}

	typedef Vector4<float>	Vector4f;
	typedef Vector4<double>	Vector4d;
}

#undef X
#undef Y
#undef Z
#undef W

#endif