///////////////////////////////////////////////////////////////////////////
/// @file Delegate.h
/// @author Wail Khemir
/// @date 2015-01-04
/// @version 1.0
///
/// @addtogroup Utilities
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef W_DELEGATE_H
#define W_DELEGATE_H


template <typename ReturnType, typename... Params>
///////////////////////////////////////////////////////////////////////////
/// @class	Delegate
///
/// @brief	-Similar to C# delegates.
///			-Can hold any function pointer with any return type and any number of arguments (and types).
///			-Can hold pointer to a :	functions, static method, method, const method, virtual method, template function, template method.
///			-Cannot hold pointer to constructor or destructor.
///			
///			All Delegates with the same return type and same number and type of arguments are considered 
///			to be of the same type. Otherwise, they are of different types. 
///
/// @date 2015-01-04
///////////////////////////////////////////////////////////////////////////
class Delegate
{
	template <typename T, typename ReturnType, typename... Params> friend class DelegateFactory;

	typedef ReturnType(*FuncPtr)(void*, Params...);

public:
	Delegate()
		: m_object(0), m_callback(0)
	{

	}


	Delegate(const Delegate& in_copy)
		: m_object(in_copy.m_object), m_callback(in_copy.m_callback)
	{

	}

	Delegate& operator=(const Delegate& in_copy)
	{
		if (this != &in_copy)
		{
			m_callback	= in_copy.m_callback;
			m_object	= in_copy.m_object;
		}

		return *this;
	}

	ReturnType operator()(Params... in_params) const
	{
		return (*m_callback)(m_object, in_params...);
	}

	bool operator==(const Delegate<ReturnType, Params...>& in_delegate)
	{
		return (m_object == in_delegate.m_object && m_callback == in_delegate.m_callback);
	}

	bool operator!=(const Delegate<ReturnType, Params...>& in_delegate)
	{
		return !operator==(in_delegate);
	}

	operator bool() const
	{
		return m_callback != 0;
	}

	bool operator!() const
	{
		return !(operator bool());
	}

private:

	Delegate(void* in_object, FuncPtr in_callback)
		: m_object(in_object), m_callback(in_callback)
	{

	}

	void*		m_object;
	FuncPtr		m_callback;
};



template <typename T, typename ReturnType, typename... Params>
///////////////////////////////////////////////////////////////////////////
/// @class	DelegateFactory
///
/// @brief	-Helper class which helps to construct a Delegate.
///			-Should not be used directly.
///			-Use the MAKE_DELEGATE macro instead
///
/// @date 2015-01-04
///////////////////////////////////////////////////////////////////////////
class DelegateFactory
{
public:
	template <ReturnType(*Function)(Params...)>
	inline static Delegate<ReturnType, Params...> CreateDelegate(int in_zero = 0)
	{
		return Delegate<ReturnType, Params...>(0, &FunctionWrapper<Function>);
	}

	template <ReturnType(T::*Method)(Params...)>
	inline static Delegate<ReturnType, Params...> CreateDelegate(T* in_object)
	{
		return Delegate<ReturnType, Params...>(in_object, &MethodWrapper<Method>);
	}

	template <ReturnType(T::*ConstMethod)(Params...)const>
	inline static Delegate<ReturnType, Params...> CreateDelegate(T* const in_object)
	{
		return Delegate<ReturnType, Params...>(in_object, &ConstMethodWrapper<ConstMethod>);
	}

private:
	template <ReturnType(*Function)(Params...)>
	static ReturnType FunctionWrapper(void* in_object, Params... in_params)
	{
		return (*Function)(in_params...);
	}

	template <ReturnType(T::*Method)(Params...)>
	static ReturnType MethodWrapper(void* in_object, Params... in_params)
	{
		return (static_cast<T*>(in_object)->*Method)(in_params...);
	}

	template <ReturnType(T::*ConstMethod)(Params...)const>
	static ReturnType ConstMethodWrapper(void* in_object, Params... in_params)
	{
		return (static_cast<T* const>(in_object)->*ConstMethod)(in_params...);
	}
};


//DelegateFactory requires that <typename T> be a class (T is the type of the class instance to which the function pointer belongs to).
//Since global functions and static methods have no class instances, the NullObject class is used as a template argument to make it work.
class NullObject{};


//The three functions below are only used for automatic template argument deduction purposes. 
//The compiler can automatically deduct template arguments from function arguments in a template function
//For more information on template type deduction, see: http://en.cppreference.com/w/cpp/language/template_argument_deduction
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename ReturnType, typename... Params>
inline DelegateFactory<NullObject, ReturnType, Params...>  MakeDelegateFactory(ReturnType(*in_functionPtr)(Params...), int in_zero = 0)
{
	return DelegateFactory<NullObject, ReturnType, Params...>();
}

template <typename T, typename ReturnType, typename... Params>
inline DelegateFactory<T, ReturnType, Params...>  MakeDelegateFactory(ReturnType(T::*in_methodPtr)(Params...), T* in_thisPtr)
{
	return DelegateFactory<T, ReturnType, Params...>();
}

template <typename T, typename ReturnType, typename... Params>
inline DelegateFactory<T, ReturnType, Params...>  MakeDelegateFactory(ReturnType(T::*in_constMethodPtr)(Params...)const, T* in_thisPtr)
{
	return DelegateFactory<T, ReturnType, Params...>();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Macro for creating Delegates
//
//Usage exemple:
//	
//	void helloWorld();
//	void print(string in_toPrint);
//	int sum(int a, int b)
//
//	class Integer
//	{
//	public:
//		static string className();
//		void add(int a);
//	private:
//		int m_integer;
//	}
//
//	//For global functions
//	Delegate<void>			d1 = MAKE_DELEGATE(helloWorld, 0);
//	Delegate<void,string>	d2 = MAKE_DELEGATE(print, 0);
//	Delegate<int,int,int>	d3 = MAKE_DELEGATE(sum, 0);
//
//	//For static functions
//	Delegate<string>		d4 = MAKE_DELEGATE(Integer::className, 0);
//
//	//For methods
//	Integer i;
//	Delegate<void, int>		d5 = MAKE_DELEGATE(&Integer::add, &i);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAKE_DELEGATE(funcPrt, thisPtr)	(MakeDelegateFactory(funcPrt, thisPtr).CreateDelegate<funcPrt>(thisPtr))


#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////