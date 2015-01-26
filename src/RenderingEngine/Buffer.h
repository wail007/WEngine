#ifndef W_BUFFER_H
#define W_BUFFER_H


class Buffer
{
public:
	virtual ~Buffer();

	int			getNbElements()		const;
	int			getElementSize()	const;
	int			getNbBytes()		const;
	const char* getData()			const;
	
	void setNbElements(int in_nbElements);	

	char*	m_data;


	Buffer();
	Buffer(int in_nbElements, int in_elementSize);

	int		m_nbElements;
	int		m_elementSize;
	int		m_nbBytes;

	
};



#endif
