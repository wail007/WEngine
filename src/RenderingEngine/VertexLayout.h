#ifndef W_VERTEX_LAYOUT_H
#define W_VERTEX_LAYOUT_H

#include "../Utilities/BitSet.h"

class VertexLayout
{
public:

	enum AttribIndex
	{
		POSITION,
		NORMAL,
		COLOR0,
		COLOR1,
		TEXTCOORD0,
		TEXTCOORD1,
		TEXTCOORD2,
		TEXTCOORD3,
		TANGENT,
		COUNT
	};

	VertexLayout();

	void setAttribute(AttribIndex in_attrib, unsigned int in_offset, unsigned int in_nbComponents);

	bool			isSet(AttribIndex in_attrib)			const;
	unsigned int	getOffset(AttribIndex in_attrib)		const;
	unsigned int	getnbComponents(AttribIndex in_attrib)	const;


private:
	BitSet	m_attribBits;

	unsigned int m_offset		[AttribIndex::COUNT];
	unsigned int m_nbComponents	[AttribIndex::COUNT];
};

#endif