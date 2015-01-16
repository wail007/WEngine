#include "BitSet.h"
#include <iostream>
#include <string>
#include <assert.h>

///////////////////////////////////////////////////////////////////////////////////

unsigned int BitSet::m_size = 32;

///////////////////////////////////////////////////////////////////////////////////

BitSet::BitSet()
	:m_bits(0)
{

}

BitSet::BitSet(std::string in_bits)
	: m_bits(0)
{
	assert(in_bits.size() <= m_size);

	unsigned int lastIndex = in_bits.size() - 1;

	for (int i = lastIndex; i >= 0; i--)
	{
		if (in_bits[i] == '1')
			set(lastIndex - i);
	}
}

BitSet::BitSet(const BitSet& in_copy)
{
	m_bits = in_copy.m_bits;
}

void BitSet::set(unsigned int in_index)
{
	m_bits |= (1 << in_index);
}

void BitSet::clear(unsigned int in_index)
{
	m_bits &= ~(1 << in_index);
}

void BitSet::invert(unsigned int in_index)
{
	m_bits ^= (1 << in_index);
}

void BitSet::setMultiple(const BitSet& in_bitSet)
{
	m_bits |= in_bitSet.m_bits;
}

void BitSet::clearMultiple(const BitSet& in_bitSet)
{
	m_bits &= ~in_bitSet.m_bits;
}

void BitSet::invertMultiple(const BitSet& in_bitSet)
{
	m_bits ^= ~in_bitSet.m_bits;
}

void BitSet::clearAll()
{
	m_bits = 0;
}

bool BitSet::isSet(unsigned int in_index) const
{
	return (m_bits & (1 << in_index)) != 0;
}

bool BitSet::containsAll(const BitSet& in_bitSet) const
{
	return (m_bits & in_bitSet.m_bits) == in_bitSet.m_bits;
}

bool BitSet::containsOne(const BitSet& in_bitSet) const
{
	return (m_bits & in_bitSet.m_bits) > 0;
}

//BitSet::Bit BitSet::operator[](unsigned int in_index)
//{
//	return BitSet::Bit	(	(bool)(m_bits & (1 << in_index)),
//							in_index,
//							this
//						);
//}

BitSet::operator unsigned int&()
{
	return m_bits;
}

unsigned int BitSet::getSize() const
{
	return m_size;
}

std::ostream& operator<<(std::ostream& out_cout, BitSet& in_bitSet)
{
	for (int i = in_bitSet.m_size - 1; i >= 0; i--)
	{
		out_cout << in_bitSet.isSet(i);
	}
	return out_cout;
}

//////////////////////////////////////////////////////////////////////////////////

//BitSet::Bit::Bit(bool in_value, short in_index, BitSet* in_bitSet)
//	:m_value(in_value), m_index(in_index), m_bitSet(in_bitSet)
//{
//
//}
//
//BitSet::Bit& BitSet::Bit::operator=(bool in_value)
//{
//	m_value = in_value;
//
//	if (m_bitSet)
//	{
//		if (m_value)
//			m_bitSet->set(m_index);
//		else
//			m_bitSet->clear(m_index);
//	}
//
//	return *this;
//}
//
//BitSet::Bit::operator bool() const
//{
//	return m_value;
//}
//
//std::string BitSet::Bit::toString() const
//{
//	return m_value ? "1" : "0";
//}