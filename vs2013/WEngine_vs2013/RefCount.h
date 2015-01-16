void* operator=(void* in_ptr, const RefCount& in_this);

class RefCount
{
public:
	void addRef();
	void release();

	unsigned int getRefCount() const;


protected:
	RefCount();

	RefCount(const RefCount& in_copy);

	virtual ~RefCount();

private:
	unsigned int m_refCount;
};