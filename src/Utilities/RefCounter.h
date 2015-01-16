#ifndef W_REF_COUNT_H
#define W_REF_COUNT_H


class RefCounter
{
	template<typename T> friend class StrongPtr;

public:
	unsigned int getRefCount() const;

protected:
	RefCounter();

	RefCounter(const RefCounter& in_copy);

	virtual ~RefCounter();

	void addRef();
	void release();

private:
	unsigned int m_refCount;	//number of StrongPtr referencing this object
};


#endif