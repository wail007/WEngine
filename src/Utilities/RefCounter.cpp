#include "RefCounter.h"
#include <assert.h>


RefCounter::RefCounter()
	:m_refCount(0)
{

}

RefCounter::RefCounter(const RefCounter& in_copy)
	: m_refCount(0)
{

}

RefCounter::~RefCounter()
{
	
}

void RefCounter::addRef()
{
	++m_refCount;
}

void RefCounter::release()
{
	assert(m_refCount > 0);

	if (--m_refCount == 0) 
		delete this;
}

unsigned int RefCounter::getRefCount() const
{
	return m_refCount;
}