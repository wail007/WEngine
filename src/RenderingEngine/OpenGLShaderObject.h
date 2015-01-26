#ifndef W_OPENGL_SHADER_OBJECT_H
#define W_OPENGL_SHADER_OBJECT_H

#include "LibOpenGL.h"
#include <string>

enum ShaderType
{
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	COUNT
};

class ShaderObject
{
public:
	ShaderObject();
	ShaderObject(const std::string& in_src, ShaderType in_type);
	~ShaderObject();

	int			getHandle() const;
	ShaderType	getType()	const;

	void setSrc	(const std::string& in_src);
	void setType(ShaderType in_type);

	bool compile();
	bool isCompiled() const;

	void define	(const std::string& in_def);
	void undef	(const std::string& in_def);

private:
	GLuint		m_handle;
	ShaderType	m_type;
	std::string m_src;

};

#endif