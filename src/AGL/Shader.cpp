#include<pch.h>
#include<Shader.h>


unsigned int agl::Shader::sm_currBind = 0;

unsigned int agl::Shader::CompileShader(unsigned int type, const std::string& src)
{
	unsigned int id = glCreateShader(type);
	const char* srcc = src.c_str();
	glShaderSource(id, 1, &srcc, nullptr);
	glCompileShader(id);
	//error handling
	int shaderCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		int logLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		char* message = new char[logLength];
		glGetShaderInfoLog(id, logLength, &logLength, message);
		std::string errorlog(message);
		std::string errorshadertype;
		switch (type)
		{
			case(GL_VERTEX_SHADER):
				errorshadertype = "Vertex";
				break;
			case(GL_FRAGMENT_SHADER):
				errorshadertype = "Fragment";
				break;
			case(GL_GEOMETRY_SHADER):
				errorshadertype = "Geometry";
				break;
		}
		DTL_ERR("Compilaton of a shader with a type of \"{0}\" failed. Error message:\n{0}\n", errorshadertype, errorlog);
		delete[] message;
		return 0;
	}
	return id;
}

bool agl::Shader::getUniformLoc(const std::string& varName, uint32_t id)
{
	if (!(uniformLocs.contains(varName)))
	{
		int Id = glGetUniformLocation(id, varName.c_str());

		if (Id == -1)
		{
			DTL_ERR("Shader uniform with a name of \"{0}\" wasn't found", varName);
			glUseProgram(sm_currBind);
			return true;
		}
		else uniformLocs[varName] = Id;
	}
	return false;
}

agl::Shader::Shader(const std::string& FilePath)
	: m_ID(0)
{
	std::ifstream shaderFile;
	shaderFile.open(FilePath);
	if (!shaderFile.is_open()) { DTL_ERR("Couldn't open shader file. Path: {0}", FilePath); return; }
	shaderType currType = none;
	std::string currLine;
	std::string vertexsrc;
	std::string fragmentsrc;
	std::string geometrysrc;
	std::string computesrc;
	//reading from a shader file
	while (std::getline(shaderFile, currLine))
	{
		if (currLine.find("#shader") != std::string::npos)
		{
			if (currLine.find(" vertex") != std::string::npos) currType = vertex;
			else if (currLine.find(" fragment") != std::string::npos) currType = fragment;
			else if (currLine.find(" geometry") != std::string::npos) currType = geometry;
			else DTL_ERR("Unsupported shader type in file \"{0}\"", FilePath);
			continue;
		}
		if (currType == none) continue;
		if (currType == vertex)
		{
			vertexsrc += currLine;
			vertexsrc += "\n";
			continue;
		}
		if (currType == fragment)
		{
			fragmentsrc += currLine;
			fragmentsrc += "\n";
			continue;
		}
		if (currType == geometry)
		{
			geometrysrc += currLine;
			geometrysrc += "\n";
			continue;
		}
	}
	if (!vertexsrc.size() || !fragmentsrc.size())
	{
		if (!vertexsrc.size()) DTL_ERR("Vertex shader not provided");
		if (!fragmentsrc.size()) DTL_ERR("Fragment shader not provided");
	}
	//compiling and linking shader program
	unsigned int vertexShaderId = agl::Shader::CompileShader(GL_VERTEX_SHADER, vertexsrc);
	unsigned int fragmentShaderId = agl::Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentsrc);
	unsigned int geometryShaderId = 0;
	if (!vertexsrc.size() || !fragmentsrc.size()) exit(EXIT_FAILURE);
	if(geometrysrc.size()) geometryShaderId = agl::Shader::CompileShader(GL_GEOMETRY_SHADER, geometrysrc);
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShaderId);
	glAttachShader(m_ID, fragmentShaderId);
	if (geometryShaderId) glAttachShader(m_ID, geometryShaderId);
	glLinkProgram(m_ID);
	glValidateProgram(m_ID);
	//error handling
	int programCompiled = 0;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &programCompiled);
	if (programCompiled != GL_TRUE)
	{
		int logLength = 0;
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
		char* message = new char[logLength];
		glGetProgramInfoLog(m_ID, logLength, &logLength, message);
		std::string errorlog(message);
		DTL_ERR("Linking of a shader program failed. Error message:\n{0}\n", errorlog);
		delete[] message;
	}
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	if (geometryShaderId) glDeleteShader(geometryShaderId);
}

agl::Shader::Shader(const std::string& VertexFilePath, const std::string& FragmentFilePath, const std::string& GeometryFilePath)
	: m_ID(0)
{
	unsigned int vertexShaderId = agl::Shader::CompileShader(GL_VERTEX_SHADER, VertexFilePath);
	unsigned int fragmentShaderId = agl::Shader::CompileShader(GL_FRAGMENT_SHADER, FragmentFilePath);
	unsigned int geometryShaderId = 0;
	if (!VertexFilePath.size() || !FragmentFilePath.size()) { DTL_ERR("Vertex or Fragment shader is empty or failed to open correctly. Shader compiling failed"); return; }
	if (GeometryFilePath.size()) geometryShaderId = agl::Shader::CompileShader(GL_GEOMETRY_SHADER, GeometryFilePath);
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShaderId);
	glAttachShader(m_ID, fragmentShaderId);
	if (geometryShaderId) glAttachShader(m_ID, geometryShaderId);
	glLinkProgram(m_ID);
	glValidateProgram(m_ID);
	//error handling
	int programCompiled = 0;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &programCompiled);
	if (programCompiled != GL_TRUE)
	{
		int logLength = 0;
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
		char* message = new char[logLength];
		glGetProgramInfoLog(m_ID, logLength, &logLength, message);
		std::string errorlog(message);
		DTL_ERR("Linking of a shader program failed. Error message:\n{0}\n", errorlog);
		delete[] message;
	}
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	if (geometryShaderId) glDeleteShader(geometryShaderId);
}
//-floats
void agl::Shader::setUniform1f(const std::string& varName, float v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1f(uniformLocs[varName], v0);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2f(const std::string& varName, float v0, float v1)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2f(uniformLocs[varName], v0, v1);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3f(const std::string& varName, float v0, float v1, float v2)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3f(uniformLocs[varName], v0, v1, v2);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4f(const std::string& varName, float v0, float v1, float v2, float v3)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4f(uniformLocs[varName], v0, v1, v2, v3);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2f(const std::string& varName, glm::vec2 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2f(uniformLocs[varName], v0.x, v0.y);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3f(const std::string& varName, glm::vec3 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3f(uniformLocs[varName], v0.x, v0.y, v0.z);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4f(const std::string& varName, glm::vec4 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4f(uniformLocs[varName], v0.x, v0.y, v0.z, v0.w);
	glUseProgram(sm_currBind);
}
//-ints
void agl::Shader::setUniform1i(const std::string& varName, int v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1i(uniformLocs[varName], v0);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2i(const std::string& varName, int v0, int v1)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2i(uniformLocs[varName], v0, v1);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3i(const std::string& varName, int v0, int v1, int v2)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3i(uniformLocs[varName], v0, v1, v2);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4i(const std::string& varName, int v0, int v1, int v2, int v3)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4i(uniformLocs[varName], v0, v1, v2, v3);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2i(const std::string& varName, glm::ivec2 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2i(uniformLocs[varName], v0.x, v0.y);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3i(const std::string& varName, glm::ivec3 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3i(uniformLocs[varName], v0.x, v0.y, v0.z);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4i(const std::string& varName, glm::ivec4 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4i(uniformLocs[varName], v0.x, v0.y, v0.z, v0.w);
	glUseProgram(sm_currBind);
}
//-uints
void agl::Shader::setUniform1u(const std::string& varName, uint32_t v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1ui(uniformLocs[varName], v0);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2u(const std::string& varName, uint32_t v0, uint32_t v1)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2ui(uniformLocs[varName], v0, v1);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3u(const std::string& varName, uint32_t v0, uint32_t v1, uint32_t v2)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3ui(uniformLocs[varName], v0, v1, v2);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4u(const std::string& varName, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4ui(uniformLocs[varName], v0, v1, v2, v3);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform2u(const std::string& varName, glm::uvec2 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform2ui(uniformLocs[varName], v0.x, v0.y);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform3u(const std::string& varName, glm::uvec3 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform3ui(uniformLocs[varName], v0.x, v0.y, v0.z);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform4u(const std::string& varName, glm::uvec4 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform4ui(uniformLocs[varName], v0.x, v0.y, v0.z, v0.w);
	glUseProgram(sm_currBind);
}
//-vecs
void agl::Shader::setUniform1fv(const std::string& varName, float* ptr, size_t size)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1fv(uniformLocs[varName], size, ptr);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform1iv(const std::string& varName, int* ptr, size_t size)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1iv(uniformLocs[varName], size, ptr);
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniform1uv(const std::string& varName, uint32_t * ptr, size_t size)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1uiv(uniformLocs[varName], size, ptr);
	glUseProgram(sm_currBind);
}
void agl::Shader::setUniform1fv(const std::string& varName, const std::vector<float>& arr)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1fv(uniformLocs[varName], arr.size(), &arr[0]);
	glUseProgram(sm_currBind);
}
void agl::Shader::setUniform1iv(const std::string& varName, const std::vector<int>& arr)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1iv(uniformLocs[varName], arr.size(), &arr[0]);
	glUseProgram(sm_currBind);
}
void agl::Shader::setUniform1uv(const std::string& varName, const std::vector<uint32_t>& arr)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniform1uiv(uniformLocs[varName], arr.size(), &arr[0]);
	glUseProgram(sm_currBind);
}
//-matrixes
void agl::Shader::setUniformMatrix3(const std::string& varName, glm::mat3 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniformMatrix3fv(uniformLocs[varName], 1, GL_FALSE, glm::value_ptr(v0));
	glUseProgram(sm_currBind);
}

void agl::Shader::setUniformMatrix4(const std::string& varName, glm::mat4 v0)
{
	glUseProgram(m_ID);
	if (getUniformLoc(varName, m_ID)) return;
	glUniformMatrix4fv(uniformLocs[varName], 1, GL_FALSE, glm::value_ptr(v0));
	glUseProgram(sm_currBind);
}

agl::Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void agl::Shader::bind() const
{
	glUseProgram(m_ID);
	sm_currBind = m_ID;
}

void agl::Shader::unbind()
{
	glUseProgram(0);
	sm_currBind = 0;
}

void agl::Shader::enableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}