#ifndef W_MATRIX4_H
#define W_MATRIX4_H


#include "Vector4.h"


#define m11 m_mat[0]
#define m12 m_mat[1]
#define m13 m_mat[2]
#define m14 m_mat[3]
#define m21 m_mat[4]
#define m22 m_mat[5]
#define m23 m_mat[6]
#define m24 m_mat[7]
#define m31 m_mat[8]
#define m32 m_mat[9]
#define m33 m_mat[10]
#define m34 m_mat[11]
#define m41 m_mat[12]
#define m42 m_mat[13]
#define m43 m_mat[14]
#define m44 m_mat[15]


namespace WMath
{

	template<typename T>
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(T in_m11, T in_m12, T in_m13, T in_14, T in_m21, T in_m22, T in_m23, T in_24, T in_m31, T in_m32, T in_m33, T in_34, T in_m41, T in_m42, T in_m43, T in_44);
		Matrix4(T in_mat[16]);
		Matrix4(const Matrix4& in_copy);

		Matrix4& operator=(const Matrix4& in_mat);
		Matrix4& operator=(T in_mat[16]);

		operator T*() const;

		const T*	operator[](unsigned int in_column) const;
		T*			operator[](unsigned int in_column);


		Vector4<T>	operator*(const Vector4<T> in_vec)	const;
		Matrix4		operator*(const Matrix4& in_mat)	const;
		Matrix4		operator*(T in_scalar)				const;
		Matrix4		operator/(T in_scalar)				const;

		Matrix4&	operator*=(const Matrix4& in_mat);
		Matrix4&	operator*=(T in_scalar);
		Matrix4&	operator/=(T in_scalar);

		Matrix4 getTranspose()	const;
		//Matrix4 getInverse()	const;

		void transpose();
		//void inverse();

		void setColumn(unsigned int in_column, Vector4<T> in_vec);
		void setColumn(unsigned int in_column, T in_vec[4]);
		void setColumn(unsigned int in_column, Vector3<T> in_vec);

		template<typename T>
		friend Matrix4<T> operator*(T in_scalar, const Matrix4<T>& in_mat);

	private:
		T m_mat[16];
	};


	template<typename T>
	Matrix4<T>::Matrix4()
	{
		m11 = m22 = m33 = m44 = static_cast<T>(1);
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = static_cast<T>(0);
	}


	template<typename T>
	Matrix4<T>::Matrix4(T in_m11, T in_m12, T in_m13, T in_m14, T in_m21, T in_m22, T in_m23, T in_m24, T in_m31, T in_m32, T in_m33, T in_m34, T in_m41, T in_m42, T in_m43, T in_m44)
	{
		m11 = in_m11;	m21 = in_m21;	m31 = in_m31;	m41 = in_m41;
		m12 = in_m12;	m22 = in_m22;	m32 = in_m32;	m42 = in_m42;
		m13 = in_m13;	m23 = in_m23;	m33 = in_m33;	m43 = in_m43;
		m14 = in_m14;	m24 = in_m24;	m34 = in_m34;	m44 = in_m44;
	}


	template<typename T>
	Matrix4<T>::Matrix4(T in_mat[16])
	{
		*this = in_mat;
	}


	template<typename T>
	Matrix4<T>::Matrix4(const Matrix4& in_copy)
	{
		*this = in_copy;
	}


	template<typename T>
	Matrix4<T>& Matrix4<T>::operator=(const Matrix4& in_mat)
	{
		for (int i = 0; i < 16; i++)
			m_mat[i] = in_mat.m_mat[i];

		return *this;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::operator=(T in_mat[9])
	{
		for (int i = 0; i < 16; i++)
			m_mat[i] = in_mat[i];

		return *this;
	}


	template<typename T>
	Matrix4<T>::operator T*() const
	{
		return (T*)m_mat;
	}


	template<typename T>
	const T* Matrix4<T>::operator[](unsigned int in_column) const
	{
		assert(in_column < 4);

		return m_mat[in_column * static_cast<T>(4)];
	}


	template<typename T>
	T* Matrix4<T>::operator[](unsigned int in_column)
	{
		assert(in_column < 4);

		return m_mat[in_column * static_cast<T>(4)];
	}


	template<typename T>
	Vector4<T> Matrix4<T>::operator*(const Vector4<T> in_vec) const
	{
		Vector4<T> v;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				v[i] += m_mat[j * 4 + i] * in_vec[j];
			}
		}

		return v;
	}


	template<typename T>
	Matrix4<T>	Matrix4<T>::operator*(const Matrix4& in_mat) const
	{
		Matrix4 m;

		for (int i = 0; i < 4; i++)				//column
		{
			for (int j = 0; j < 4; j++)			//row
			{
				for (int k = 0; k < 4; k++)
				{
					m.m_mat[i * 4 + j] += m_mat[k * 4 + j] * in_mat.m_mat[i * 4 + k];
				}
			}
		}

		return m;
	}


	template<typename T>
	Matrix4<T> Matrix4<T>::operator*(T in_scalar) const
	{
		Matrix4 m;

		for (int i = 0; i < 16; i++)
		{
			m.m_mat[i] = m_mat[i] * in_scalar;
		}

		return m;
	}


	template<typename T>
	Matrix4<T> Matrix4<T>::operator/(T in_scalar) const
	{
		Matrix4 m;

		for (int i = 0; i < 16; i++)
		{
			m.m_mat[i] = m_mat[i] / in_scalar;
		}

		return m;
	}


	template<typename T>
	Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& in_mat)
	{
		return *this = *this * in_mat;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::operator*=(T in_scalar)
	{
		return *this = *this * in_scalar;
	}

	template<typename T>
	Matrix4<T>& Matrix4<T>::operator/=(T in_scalar)
	{
		return *this = *this / in_scalar;
	}


	template<typename T>
	Matrix4<T> Matrix4<T>::getTranspose() const
	{
		return Matrix4<T>
		(
			m11, m21, m31, m41,
			m12, m22, m32, m42,
			m13, m23, m33, m43,
			m14, m24, m34, m44,
		);
	}


	//template<typename T>
	//Matrix4<T> Matrix4<T>::getInverse() const
	//{
	//	T invDet = static_cast<T>(1) / (+ m11 * (m22*(m33*m44-m43*m34) + m32*(m43*m24-m23*m44) + m42*(m23*m34 - m33*m24))
	//									- m21 * (m12*(m33*m44-m43*m34) + m32*(m43*m14-m13*m44) + m42*(m13*m34 - m33*m14))
	//									+ m31 * (m12*(m23*m44-m43*m24) + m22*(m43*m14-m13*m44) + m42*(m13*m24 - m23*m14))
	//									- m41 * (m12*(m23*m34-m33*m24) + m22*(m33*m14-m13*m34) + m32*(m13*m24 - m23*m14)));
	//	
	//	
	//	//transposed cofactor(adjoint) divided by determinant
	//	return Matrix4 < T >
	//	(
	//		+(m22 * m33 - m32 * m23) * invDet,	//adj11 -> cof11
	//		-(m12 * m33 - m32 * m13) * invDet,	//adj12	-> cof21
	//		+(m12 * m23 - m22 * m13) * invDet,	//adj13	-> cof31
	//											//adj14 -> cof41
	//		-(m21 * m33 - m31 * m23) * invDet,	//adj21	-> cof12
	//		+(m11 * m33 - m31 * m13) * invDet,	//adj22	-> cof22
	//		-(m11 * m23 - m21 * m13) * invDet,	//adj23	-> cof32
	//											//adj24 -> cof42
	//		+(m21 * m32 - m31 * m22) * invDet,	//adj31	-> cof13
	//		-(m11 * m32 - m31 * m12) * invDet,	//adj32	-> cof23
	//		+(m11 * m22 - m21 * m12) * invDet	//adj33	-> cof33
	//											//adj34 -> cof43
	//											//adj41 -> cof14
	//											//adj42 -> cof24
	//											//adj43 -> cof34
	//											//adj44 -> cof44
	//	);
	//}



	template<typename T>
	void Matrix4<T>::transpose()
	{
		T m12Tmp = m12;
		T m13Tmp = m13;
		T m14Tmp = m14;
		T m23Tmp = m23;
		T m24Tmp = m24;
		T m34Tmp = m34;

		m12 = m21;
		m13 = m31;
		m14 = m41;
		m23 = m32;
		m24	= m42;
		m34	= m43;

		m21 = m12Tmp;
		m31 = m13Tmp;
		m41 = m14Tmp;
		m32	= m23Tmp;
		m42	= m24Tmp;
		m43	= m34Tmp;
	}

	//template<typename T>
	//void Matrix4<T>::inverse()
	//{
	//	*this = getInverse();
	//}


	template<typename T>
	void Matrix4<T>::setColumn(unsigned int in_column, Vector4<T> in_vec)
	{
		T* column = m_mat[in_column * 4];

		column[0] = in_vec[0];
		column[1] = in_vec[1];
		column[2] = in_vec[2];
		column[3] = in_vec[3];
	}


	template<typename T>
	void Matrix4<T>::setColumn(unsigned int in_column, T in_vec[4])
	{
		T* column = m_mat[in_column * 4];

		column[0] = in_vec[0];
		column[1] = in_vec[1];
		column[2] = in_vec[2];
		column[3] = in_vec[3];
	}


	template<typename T>
	void Matrix4<T>::setColumn(unsigned int in_column, Vector3<T> in_vec)
	{
		T* column = m_mat[in_column * 3];

		column[0] = in_vec[0];
		column[1] = in_vec[1];
		column[2] = in_vec[2];
	}



	template<typename T>
	Matrix4<T> operator*(T in_scalar, const Matrix4<T>& in_mat)
	{
		return in_mat * in_scalar;
	}


	typedef Matrix4<float>	Matrix4f;
	typedef Matrix4<double> Matrix4d;
}


#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44

#endif