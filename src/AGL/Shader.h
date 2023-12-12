#pragma once
#include"dtl.h"
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>

namespace GL
{
	class Shader
	{
	private:
		bool m_firstCon = true;
		static unsigned int sm_currBind;
		unsigned int m_ID;
		unsigned int CompileShader(unsigned int type, const std::string& src);
		std::unordered_map<std::string, int> uniformLocs;
		bool getUniformLoc(const std::string& varName, uint32_t id);
	private:
		enum shaderType
		{
			vertex, fragment, geometry, none
		};
	public:
		Shader(const Shader&) = delete;
		Shader(const std::string& FilePath);
		Shader(const std::string& VertexFilePath, const std::string& FragmentFilePath, const std::string& GeometryFilePath = "");
		~Shader();
		void bind() const;
		static void unbind();

		void setUniform1f(const std::string& varName, float v0);
		void setUniform2f(const std::string& varName, float v0, float v1);
		void setUniform3f(const std::string& varName, float v0, float v1, float v2);
		void setUniform4f(const std::string& varName, float v0, float v1, float v2, float v3);
		void setUniform2f(const std::string& varName, glm::vec2 v0);
		void setUniform3f(const std::string& varName, glm::vec3 v0);
		void setUniform4f(const std::string& varName, glm::vec4 v0);

		void setUniform1i(const std::string& varName, int v0);
		void setUniform2i(const std::string& varName, int v0, int v1);
		void setUniform3i(const std::string& varName, int v0, int v1, int v2);
		void setUniform4i(const std::string& varName, int v0, int v1, int v2, int v3);
		void setUniform2i(const std::string& varName, glm::ivec2 v0);
		void setUniform3i(const std::string& varName, glm::ivec3 v0);
		void setUniform4i(const std::string& varName, glm::ivec4 v0);

		void setUniform1u(const std::string& varName, uint32_t v0);
		void setUniform2u(const std::string& varName, uint32_t v0, uint32_t v1);
		void setUniform3u(const std::string& varName, uint32_t v0, uint32_t v1, uint32_t v2);
		void setUniform4u(const std::string& varName, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);
		void setUniform2u(const std::string& varName, glm::uvec2 v0);
		void setUniform3u(const std::string& varName, glm::uvec3 v0);
		void setUniform4u(const std::string& varName, glm::uvec4 v0);
		
		void setUniform1fv(const std::string& varName, float* ptr, uint32_t size);
		void setUniform1iv(const std::string& varName, int* ptr, uint32_t size);
		void setUniform1uv(const std::string& varName, uint32_t* ptr, uint32_t size);
		
		void setUniformMatrix3(const std::string& varName, glm::mat3 v0);
		void setUniformMatrix4(const std::string& varName, glm::mat4 v0);
		
	};
}