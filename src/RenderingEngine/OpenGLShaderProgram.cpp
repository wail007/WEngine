#include "OpenGLShaderProgram.h"


const std::string ShaderProgram::AttribNames[VertexLayout::AttribIndex::COUNT] =
{
	"in_Position",
	"in_Normal",
	"in_Color0",
	"in_Color1",
	"in_TexCoord0",
	"in_TexCoord1",
	"in_TexCoord2",
	"in_TexCoord3",
	"in_Tangent"
};


ShaderProgram::ShaderProgram()
	:m_handle(0)
{

}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_handle);
}



bool ShaderProgram::linkProgram(const ShaderObject& in_vert, const ShaderObject& in_frag)
{
	if (m_handle == 0)
	{
		m_handle = glCreateProgram();
		if (m_handle == 0)
		{
			std::cerr << "Error creating Shader Program" << std::endl;
			return false;
		}
	}

	glAttachShader(m_handle, in_vert.getHandle());
	glAttachShader(m_handle, in_frag.getHandle());


	for (int i = 0; i < VertexLayout::AttribIndex::COUNT; i++)
		glBindAttribLocation(m_handle, i, AttribNames[i].c_str());


	glLinkProgram(m_handle);

	int result;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		int logSize;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &logSize);

		char* log = new char[logSize + 1];

		int written;
		glGetProgramInfoLog(m_handle, logSize, &written, log);

		log[written] = '\0';

		std::cerr << log << std::endl;

		delete[] log;

		return false;
	}

	glDetachShader(m_handle, in_vert.getHandle());
	glDetachShader(m_handle, in_frag.getHandle());

	return true;
}

void ShaderProgram::enable()	const
{
	glUseProgram(m_handle);
}

void ShaderProgram::disable()	const
{
	glUseProgram(0);
}


void ShaderProgram::setFloat(const std::string& in_name, float in_val)	const
{
	glUniform1f(glGetUniformLocation(m_handle, in_name.c_str()), in_val);
}

void ShaderProgram::setBoolean(const std::string& in_name, bool	 in_val) const
{
	glUniform1i(glGetUniformLocation(m_handle, in_name.c_str()), in_val);
}

void ShaderProgram::setVector3(const std::string& in_name, const WMath::Vector3f& in_vec) const
{
	glUniform3fv(glGetUniformLocation(m_handle, in_name.c_str()), 1, in_vec);
}

void ShaderProgram::setVector4(const std::string& in_name, const WMath::Vector4f& in_vec) const
{
	glUniform4fv(glGetUniformLocation(m_handle, in_name.c_str()), 1, in_vec);
}

void ShaderProgram::setMatrix3(const std::string& in_name, const WMath::Matrix3f& in_mat) const
{
	glUniformMatrix3fv( glGetUniformLocation(m_handle, in_name.c_str()), 1, GL_FALSE, in_mat);
}

void ShaderProgram::setMatrix4(const std::string& in_name, const WMath::Matrix4f& in_mat) const
{    
	glUniformMatrix4fv( glGetUniformLocation(m_handle, in_name.c_str()), 1, GL_FALSE, in_mat);
}

void ShaderProgram::setSampler(const std::string& in_name, int in_texUnit) const
{
	glUniform1i(glGetUniformLocation(m_handle, in_name.c_str()), in_texUnit);
}
