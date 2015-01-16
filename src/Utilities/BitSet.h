#ifndef BIT_SET_H
#define BIT_SET_H

#include <iostream>
#include <string>

class BitSet
{
private:
	//class Bit
	//{
	//public:
	//	Bit(bool in_value, short in_index, BitSet* in_bitSet);
	//
	//	Bit& operator=(bool in_value);
	//	operator bool() const;
	//
	//	std::string toString() const;
	//
	//private:
	//	BitSet*	m_bitSet;
	//	short	m_index;
	//	bool	m_value;
	//};

public:
	BitSet();
	BitSet(std::string in_bits);
	BitSet(const BitSet& in_copy);

	void set(unsigned int in_index);
	void clear(unsigned int in_index);
	void invert(unsigned int in_index);
	
	void setMultiple(const BitSet& in_bitSet);
	void clearMultiple(const BitSet& in_bitSet);
	void invertMultiple(const BitSet& in_bitSet);

	void clearAll();

	bool isSet(unsigned int in_index)			const;
	bool containsAll(const BitSet& in_bitSet)	const;
	bool containsOne(const BitSet& in_bitSet)	const;
	
	operator unsigned int&();

	//Bit operator[](unsigned int in_index);

	unsigned int getSize() const;

	friend std::ostream& operator<<(std::ostream& out_cout,  BitSet& in_bitSet);

private:
	unsigned int m_bits;

	static unsigned int m_size;
};

#endif