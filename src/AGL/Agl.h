#pragma once
#include<dtl.h>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<Shader.h>
#include<stb/stb_image.h>
#include<ImGui.h>

struct BufferData;

struct Vertice
{
	glm::vec2 position;
	glm::vec2 uv;
	Vertice();
	Vertice(glm::vec2 pos, glm::vec2 UV = { 0.0f, 0.0f });
	~Vertice() = default;
	Vertice(const Vertice&) = default;
};

struct Color
{
	uchar r, g, b, a;
	Color();
	Color(uchar red, uchar green, uchar blue, uchar alpha);
	~Color() = default;
	Color(const Color&) = default;
	glm::vec4 getNormalized() const;
	Color operator+(Color c) const;
};


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
		void bind(int slot = 0) const;
		static void unbind();
	};
	//Rendering
	class Object
	{
		glm::vec2 m_pos;
		glm::ivec2 m_texRatio;
		float m_xScale, m_yScale;
		float m_rotation;
		agl::Texture* m_tex;
		Color m_color;
	public:
		Object(float width, float height, glm::vec2 pos = { 0.f, 0.f }, Color color = {255, 255, 255, 255}, glm::ivec2 texRatio = {1, 1});
		~Object();
		void setTexture(agl::Texture& texture);
		void setRotation(float rads);
		void setScale(float xScale, float yScale);
		void setPosition(float xPos, float yPos);
		void setPosition(glm::vec2 pos);
		void setColor(uchar red, uchar green, uchar blue, uchar alpha);
		void setColor(Color color);
		Color getColor() const;
		float getRotation() const;
		glm::vec2 getScale() const;
		glm::vec2 getPosition() const;
		friend class GraphicLayer;
	};

	class Camera
	{
		glm::vec2 m_pos;
		glm::vec2 m_size;
		float m_focalLengh;
	public:
		Camera(const Camera&) = default;
		Camera(float x, float y, glm::vec2 size, float focalLength);
		Camera(glm::vec2 position, float w, float h, float focalLength);
		Camera(float x, float y, float w, float h, float focalLength);
		Camera(glm::vec2 position, glm::vec2 size, float focalLength);
		~Camera();
		void setFocalLength(float focalLength);
		void setPosition(float x, float y);
		void setPosition(glm::vec2 position);
		void setSize(float w, float h);
		void setSize(glm::vec2 size);
		float getFocalLength();
		glm::vec2 getPosition();
		glm::vec2 getSize();
	};

	class GraphicLayer
	{
		struct BufferData;
		agl::Shader* m_shader;
		agl::Camera* m_camera;
		const uint32_t m_trisStencile[6] = {0, 1, 2, 2, 3, 1};
		std::vector<BufferData> m_bd;
		struct BufferData
		{ uint32_t VBO, EBO, VAO; agl::Object* objptr; };
	public:
		GraphicLayer(const GraphicLayer&) = delete;
		GraphicLayer(agl::Shader& shader, agl::Camera& camera);
		~GraphicLayer();
		void draw();
		void addObject(Object& obj);
		void removeObject(Object& obj);
	};

}

