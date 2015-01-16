//#include "utilities/BitSet.h"
#include "../Utilities/StrongPtr.h"
#include "../Utilities/Delegate.h"
#include <iostream>
#include <string>

using namespace std;

class Integer : RefCounter
{
public:

	static string getName()
	{
		return  "Integer";
	}

	Integer()
		:val(-5)
	{
	}

	virtual std::string toString() const
	{
		return "Integer";
	}

	int val;
};

class Integer2 : public Integer
{
public:
	Integer2()
		:Integer(), val2(10)
	{
		val = 5;
	}

	virtual std::string toString() const
	{
		return "Integer2";
	}

	int val2;
};

void helloWorld()
{
	cout << "Hello world" << endl;
}

int main()
{
	/*BitSet physics = "00000111";
	BitSet entityComponents = "00000000000000000000000010100010";


	cout << "physics: " << physics << endl;
	cout << "entityComponents: " << entityComponents << endl;

	if (entityComponents.containsOne(physics))
		cout << "true" << endl;
	else
		cout << "false" << endl;*/

	//cout << "Ineger size: " << sizeof(Integer) << endl;
	//cout << "Ineger2 size: " << sizeof(Integer2) << endl;
	//
	//
	//Integer* i = new Integer2[10];//(Integer*)malloc(sizeof(Integer2)*10);
	//i[1].val = -25;
	//
	//cout << "Index size: " << (((Integer2*)i)[0]).val2 << endl;
	//cout << "Index size: " << &(i[0].val) << endl;

	Integer* i = new Integer2;

	Delegate<string> d = MAKE_DELEGATE(&Integer::toString, i);

	//(MakeDelegateFactory(&Integer::toString, i).CreateDelegate<&Integer::toString>(i))
	//(MakeDelegateFactory(&Integer::toString, i).CreateDelegate<&Integer::toString, i>())

	cout << d() << endl;

	delete i;
}