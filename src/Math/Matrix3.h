#ifndef W_MATRIX3_H
#define W_MATRIX3_H


#include "Vector3.h"


#define m11 m_mat3[0]
#define m12 m_mat3[1]
#define m13 m_mat3[2]
#define m21 m_mat3[3]
#define m22 m_mat3[4]
#define m23 m_mat3[5]
#define m31 m_mat3[6]
#define m32 m_mat3[7]
#define m33 m_mat3[8]


namespace WMath
{

	template<typename T>
	class Matrix3
	{
	public:
		Matrix3();
		Matrix3(T in_m11, T in_m12, T in_m13, T in_m21, T in_m22, T in_m23, T in_m31, T in_m32, T in_m33);
		Matrix3(T in_mat[9]);
		Matrix3(const Matrix3& in_copy);

		Matrix3& operator=(const Matrix3& in_mat);
		Matrix3& operator=(T in_mat[9]);

		operator T*() const;

		const T*	operator[](unsigned int in_column) const;
		T*			operator[](unsigned int in_column);


		Vector3<T>	operator*(const Vector3<T> in_vec)	const;
		Matrix3		operator*(const Matrix3& in_mat)	const;
		Matrix3		operator*(T in_scalar)				const;
		Matrix3		operator/(T in_scalar)				const;

		Matrix3&	operator*=(const Matrix3& in_mat);
		Matrix3&	operator*=(T in_scalar);
		Matrix3&	operator/=(T in_scalar);

		Matrix3 getTranspose()	const;
		Matrix3 getInverse()	const;

		void transpose();
		void inverse();

		void setColumn(unsigned int in_column, Vector3<T> in_vec);
		void setColumn(unsigned int in_column, T in_vec[3]);

		template<typename T>
		friend Matrix3<T> operator*(T in_scalar, const Matrix3<T>& in_mat);

	private:
		T m_mat[9];
	};


	template<typename T>
	Matrix3<T>::Matrix3()
	{
		m11 = m22 = m33 = static_cast<T>(1);
		m12 = m13 = m21 = m23 = m31 = m32 = static_cast<T>(0);
	}


	template<typename T>
	Matrix3<T>::Matrix3(T in_m11, T in_m12, T in_m13, T in_m21, T in_m22, T in_m23, T in_m31, T in_m32, T in_m33)
	{
		m11 = in_m11;	m21 = in_m21;	m31 = in_m31;
		m12 = in_m12;	m22 = in_m22;	m32 = in_m32;
		m13 = in_m13;	m23 = in_m23;	m33 = in_m33;
	}


	template<typename T>
	Matrix3<T>::Matrix3(T in_mat[9])
	{
		*this = in_mat;
	}


	template<typename T>
	Matrix3<T>::Matrix3(const Matrix3& in_copy)
	{
		*this = in_copy;
	}


	template<typename T>
	Matrix3<T>& Matrix3<T>::operator=(const Matrix3& in_mat)
	{
		m11 = in_mat.m11;	m21 = in_mat.m21;	m31 = in_mat.m31;
		m12 = in_mat.m12;	m22 = in_mat.m22;	m32 = in_mat.m32;
		m13 = in_mat.m13;	m23 = in_mat.m23;	m33 = in_mat.m33;

		return *this;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::operator=(T in_mat[9])
	{
		m11 = in_mat[0];	m21 = in_mat[3];	m31 = in_mat[6];
		m12 = in_mat[1];	m22 = in_mat[4];	m32 = in_mat[7];
		m13 = in_mat[2];	m23 = in_mat[5];	m33 = in_mat[8];

		return *this;
	}


	template<typename T>
	Matrix3<T>::operator T*() const
	{
		return m_mat;
	}


	template<typename T>
	const T* Matrix3<T>::operator[](unsigned int in_column) const
	{
		assert(in_column < 3);

		return m_mat[in_column * static_cast<T>(3)];
	}


	template<typename T>
	T* Matrix3<T>::operator[](unsigned int in_column)
	{
		assert(in_column < 3);

		return m_mat[in_column * static_cast<T>(3)];
	}


	template<typename T>
	Vector3<T> Matrix3<T>::operator*(const Vector3<T> in_vec) const
	{
		return Vector3<T>
		(
			m11 * in_vec.x() + m21 * in_vec.y() + m31 * in_vec.z(),
			m12 * in_vec.x() + m22 * in_vec.y() + m32 * in_vec.z(),
			m13 * in_vec.x() + m23 * in_vec.y() + m33 * in_vec.z()
		)
	}


	template<typename T>
	Matrix3<T>	Matrix3<T>::operator*(const Matrix3& in_mat) const
	{
		Matrix3 m;

		for (int i = 0; i < 3; i++)				//column
		{
			for (int j = 0; j < 3; j++)			//row
			{
				for (int k = 0; k < 3; k++)		
				{
					m.m_mat[i * 3 + j] += m_mat[k * 3 + j] * in_mat.m_mat[i * 3 + k];
				}
			}
		}
		
		return m;
	}


	template<typename T>
	Matrix3<T> Matrix3<T>::operator*(T in_scalar) const
	{
		Matrix3 m;

		for (int i = 0; i < 9; i++)
		{
			m.m_mat[i] = m_mat[i] * in_scalar;
		}

		return m;
	}


	template<typename T>
	Matrix3<T> Matrix3<T>::operator/(T in_scalar) const
	{
		Matrix3 m;

		for (int i = 0; i < 9; i++)
		{
			m.m_mat[i] = m_mat[i] / in_scalar;
		}

		return m;
	}


	template<typename T>
	Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& in_mat)
	{
		return *this = *this * in_mat;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::operator*=(T in_scalar)
	{
		return *this = *this * in_scalar;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::operator/=(T in_scalar)
	{
		return *this = *this / in_scalar;
	}


	template<typename T>
	Matrix3<T> Matrix3<T>::getTranspose() const
	{
		return Matrix3<T>
		(
			m11, m21, m31,
			m12, m22, m32,
			m13, m23, m33,
		);
	}


	template<typename T>
	Matrix3<T> Matrix3<T>::getInverse() const
	{
		T invDet = static_cast<T>(1) / ( +m11 * (m22 * m33 - m32 * m23)
										 -m21 * (m12 * m33 - m32 * m13)
										 +m31 * (m12 * m23 - m22 * m13));

		//transposed cofactor(adjoint) divided by determinant
		return Matrix3 < T >
		(
			+(m22 * m33 - m32 * m23) * invDet,	//adj11 -> cof11
			-(m12 * m33 - m32 * m13) * invDet,	//adj12	-> cof21
			+(m12 * m23 - m22 * m13) * invDet,	//adj13	-> cof31
			-(m21 * m33 - m31 * m23) * invDet,	//adj21	-> cof12
			+(m11 * m33 - m31 * m13) * invDet,	//adj22	-> cof22
			-(m11 * m23 - m21 * m13) * invDet,	//adj23	-> cof32
			+(m21 * m32 - m31 * m22) * invDet,	//adj31	-> cof13
			-(m11 * m32 - m31 * m12) * invDet,	//adj32	-> cof23
			+(m11 * m22 - m21 * m12) * invDet	//adj33	-> cof33
		);
	}



	template<typename T>
	void Matrix3<T>::transpose()
	{
		T m12Tmp = m12;
		T m13Tmp = m13;
		T m23Tmp = m23;

		m12 = m21;
		m13	= m31;
		m23	= m32;

		m21 = m12Tmp;
		m31	= m13Tmp;
		m32	= m23Tmp;

	}

	template<typename T>
	void Matrix3<T>::inverse()
	{
		*this = getInverse();
	}


	template<typename T>
	void Matrix3<T>::setColumn(unsigned int in_column, Vector3<T> in_vec)
	{
		T* column = m_mat[in_column * 3];

		column[0] = in_vec[0];
		column[1] = in_vec[1];
		column[2] = in_vec[2];
	}


	template<typename T>
	void Matrix3<T>::setColumn(unsigned int in_column, T in_vec[3])
	{
		T* column = m_mat[in_column * 3];

		column[0] = in_vec[0];
		column[1] = in_vec[1];
		column[2] = in_vec[2];
	}


	template<typename T>
	Matrix3<T> operator*(T in_scalar, const Matrix3<T>& in_mat)
	{
		return in_mat * in_scalar;
	}


	typedef Matrix3<float>	Matrix3f;
	typedef Matrix3<double> Matrix3d;
}

#undef m11
#undef m12
#undef m13
#undef m21
#undef m22
#undef m23
#undef m31
#undef m32
#undef m33

#endif