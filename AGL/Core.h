#pragma once
#include"dtl.h"
#include"glad/glad.h"
#include"glfw/glfw3.h"
#include"Shader.h"
#include"stb/stb_image.h"

#define AGL_DEFINE_DEFTEX agl::Texture solidWhiteTex("src/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT)
#define AGL_DEFTEX solidWhiteTex

struct Vertice;
struct BufferData;

namespace agl
{
	void Init();
	void Terminate();
	//textures
	class Texture
	{
		uint32_t m_textureID;
		int m_widthImg, m_heightImg, m_BPP;
		uint8_t* m_bytesData;
	public:
		Texture(std::string filepath,int filter,int sWrap,int tWrap);
		~Texture();
		void bind(int slot = 0);
		void unbind();
	};
	//Rendering
	class Object
	{
		static agl::Texture s_defTex;
		glm::vec2 m_pos;
		glm::ivec2 m_tRat;
		glm::mat4 m_model;
		float m_xs, m_ys;
		float m_rot;
		agl::Texture* m_tex;
		void m_transform();
	public:
		Object(float width, float height, agl::Texture& texture, glm::vec2 pos = { 0.f, 0.f }, glm::ivec2 texRatio = {1, 1});
		~Object();
		void setTexture(agl::Texture& texture);
		void setRotation(float rads);
		void setScale(float xScale, float yScale);
		void setPosition(float xPos, float yPos);
		void setPosition(glm::vec2 pos);
		void rotate(float rads);
		void scale(float xScale, float yScale);
		void move(float xPos, float yPos);
		void move(glm::vec2 pos);
		friend class Renderer;
	};

	class Renderer
	{
		GL::Shader* m_shader;
		const uint32_t m_trisStencile[6] = {0, 1, 2, 2, 3, 1};
		std::vector<BufferData> m_bd;

	public:
		Renderer(const Renderer&) = delete;
		Renderer(GL::Shader* shader);
		~Renderer();
		void draw();
		void addObject(Object& obj);
		void removeObject(Object& obj);
	};

}

//data structures
struct Vertice
{
	glm::vec2 position;
	glm::vec2 uv;
	Vertice();
	Vertice(glm::vec2 pos, glm::vec2 UV = { 0.0f, 0.0f });
};

struct BufferData
{
	uint32_t VBO, EBO, VAO;
	agl::Object* objptr;
};