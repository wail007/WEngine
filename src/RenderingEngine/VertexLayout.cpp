#include "VertexLayout.h"

VertexLayout::VertexLayout()
	:m_attribBits()
{
	memset(m_offset, 0, AttribIndex::COUNT);
	memset(m_nbComponents, 0, AttribIndex::COUNT);
}

void VertexLayout::setAttribute(AttribIndex in_attrib, unsigned int in_offset, unsigned int in_nbComponents)
{
	m_attribBits.set(in_attrib);

	m_offset[in_attrib]			= in_offset;
	m_nbComponents[in_attrib]	= in_nbComponents;
}

bool VertexLayout::isSet(AttribIndex in_attrib) const
{
	return m_attribBits.isSet(in_attrib);
}

unsigned int VertexLayout::getOffset(AttribIndex in_attrib) const
{
	return m_offset[in_attrib];
}

unsigned int VertexLayout::getnbComponents(AttribIndex in_attrib) const
{
	return m_nbComponents[in_attrib];
}