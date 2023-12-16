#pragma once
#include<dtl.h>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<Shader.h>
#include<stb/stb_image.h>
#include<ImGui.h>

#define AGL_DEFINE_DEFTEX agl::Texture solidWhiteTex("assets/textures/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT)
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
		glm::vec2 m_pos;
		glm::ivec2 m_texRatio;
		float m_xScale, m_yScale;
		float m_rotation;
		agl::Texture* m_tex;
	public:
		Object(float width, float height, agl::Texture& texture, glm::vec2 pos = { 0.f, 0.f }, glm::ivec2 texRatio = {1, 1});
		~Object();
		void setTexture(agl::Texture& texture);
		void setRotation(float rads);
		void setScale(float xScale, float yScale);
		void setPosition(float xPos, float yPos);
		void setPosition(glm::vec2 pos);
		float getRotation();
		glm::vec2 getScale();
		glm::vec2 getPosition();

		friend class GraphicLayer;
	};

	class GraphicLayer
	{
		agl::Shader* m_shader;
		const uint32_t m_trisStencile[6] = {0, 1, 2, 2, 3, 1};
		std::vector<BufferData> m_bd;

	public:
		GraphicLayer(const GraphicLayer&) = delete;
		GraphicLayer(agl::Shader* shader);
		~GraphicLayer();
		void draw();
		void addObject(Object& obj);
		void removeObject(Object& obj);
	};

	class Camera
	{
		glm::vec2 m_pos;
		float m_focalLengh;
	public:
		Camera(const Camera&) = delete;
		Camera(float x, float y, float focalLength);
		Camera(glm::vec2 position, float focalLength);
		~Camera();
		void setFocalLength(float focalLength);
		void setPosition(float x, float y);
		void setPosition(glm::vec2 position);
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