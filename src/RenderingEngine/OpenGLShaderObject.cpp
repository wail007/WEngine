#include "OpenGLShaderObject.h"
#include <iostream>

ShaderObject::ShaderObject()
	:m_handle(0), m_src(), m_type(VERTEX_SHADER)
{

}


ShaderObject::ShaderObject(const std::string& in_src, ShaderType in_type)
	:m_handle(0), m_src(in_src), m_type(in_type)
{

}


ShaderObject::~ShaderObject()
{
	glDeleteShader(m_handle);
}


void ShaderObject::setSrc(const std::string& in_src)
{
	m_src = in_src;
}


void ShaderObject::setType(ShaderType in_type)
{
	m_type = in_type;
}


bool ShaderObject::compile()
{
	switch (m_type)
	{
	case VERTEX_SHADER:
		m_handle = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		m_handle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		return false;
	}

	if (m_handle == 0)
	{
		std::cerr << "Error creating shader object" << std::endl;
		return false;
	}

	const char* src = m_src.c_str();
	glShaderSource(m_handle, 1, &src, 0);


	glCompileShader(m_handle);

	int result;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int logSize;
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &logSize);

		if (logSize > 0)
		{
			char* log = new char[logSize+1];
		
			GLsizei written;
			glGetShaderInfoLog(m_handle, logSize, &written, log);

			log[written] = '\0';

			std::cerr << log << std::endl;

			delete[] log;
		}

		return false;
	}

	return true;
}


bool ShaderObject::isCompiled() const
{
	return m_handle != 0;
}

void ShaderObject::define(const std::string& in_def)
{
	m_src = "#define " + in_def + "\n" + m_src;
}


void ShaderObject::undef(const std::string& in_def)
{
	std::string define = "#define " + in_def + "\n";

	int index = m_src.find(define);

	if (index != std::string::npos)
		m_src.erase(index, define.size());

}


int	ShaderObject::getHandle() const
{
	return m_handle;
}

ShaderType ShaderObject::getType()	const
{
	return m_type;
}