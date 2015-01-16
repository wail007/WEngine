#ifndef W_STRONG_POINTER
#define W_STRONG_POINTER

#include "RefCounter.h"


template <typename T>
class StrongPtr
{
public:
	StrongPtr();
	StrongPtr(RefCounter* in_ref);
	StrongPtr(const StrongPtr<T>& in_copy);
	~StrongPtr();
	
	StrongPtr<T>& operator=(const StrongPtr<T>& in_ptr);
	StrongPtr<T>& operator=(RefCounter* in_ref);
	
	T*	operator->()	const;	//x->member
	T&	operator*()		const;	//*x, (*x).member
	operator T*()		const;	//T* y = x;

	template <typename T>
	friend void ReleaseStrongPtr(StrongPtr<T>& in_ptr);

private:
	T* m_ptr;
};


template <typename T>
void ReleaseStrongPtr(StrongPtr<T>& in_ptr)
{
	if (in_ptr)
	{
		in_ptr->release();
		in_ptr.m_ptr = 0;
	}
}


template <typename T>
StrongPtr<T>::StrongPtr()
	:m_ptr(0)
{

}

template <typename T>
StrongPtr<T>::StrongPtr(RefCounter* in_ref)
{
	m_ptr = (T*)in_ref;
	in_ref->addRef();
}

template <typename T>
StrongPtr<T>::StrongPtr(const StrongPtr<T>& in_copy)
{
	m_ptr = in_copy.m_ptr;
	in_copy->addRef();
}

template <typename T>
StrongPtr<T>::~StrongPtr()
{
	ReleaseStrongPtr(*this);
}

template <typename T>
StrongPtr<T>& StrongPtr<T>::operator=(const StrongPtr<T>& in_ptr)
{
	return operator=(in_ptr.m_ptr);
}

template <typename T>
StrongPtr<T>& StrongPtr<T>::operator=(RefCounter* in_ref)
{
	if (m_ptr != in_ref)
	{
		ReleaseStrongPtr(*this);

		if (in_ref)
		{
			m_ptr = (T*)in_ref;
			in_ref->addRef();
		}
	}

	return *this;
}

template <typename T>
T* StrongPtr<T>::operator->() const
{
	return m_ptr;
}

template <typename T>
T& StrongPtr<T>::operator*() const
{
	return *m_ptr;
}

template <typename T> 
StrongPtr<T>::operator T*() const
{
	return m_ptr;
}

#endif