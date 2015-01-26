#ifndef W_OPENGL_SHADER_PROGRAM_H
#define W_OPENGL_SHADER_PROGRAM_H

#include "LibOpenGL.h"
#include <string>
#include "OpenGLShaderObject.h"
#include "VertexLayout.h"
#include "../Math/WMath.h"


class ShaderProgram
{
public:
	static const std::string AttribNames[VertexLayout::COUNT];

	ShaderProgram();
	~ShaderProgram();

	bool linkProgram(const ShaderObject& in_vert, const ShaderObject& in_frag);

	void enable()	const;
	void disable()	const;
	
	/////////////////////////////Set Uniform variables//////////////////////////////////
	void setFloat	(const std::string& in_name, float					in_val)	const;
	void setBoolean	(const std::string& in_name, bool					in_val)	const;

	void setVector3	(const std::string& in_name, const WMath::Vector3f& in_vec)	const;
	void setVector4	(const std::string& in_name, const WMath::Vector4f& in_vec)	const;

	void setMatrix3	(const std::string& in_name, const WMath::Matrix3f& in_mat)	const;
	void setMatrix4	(const std::string& in_name, const WMath::Matrix4f& in_mat)	const;

	void setSampler	(const std::string& in_name, int in_texUnit)				const;
	///////////////////////////////////////////////////////////////////////////////////

private:
	GLuint	m_handle;
};


#endif