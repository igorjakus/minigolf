#pragma once
#include<dtl.h>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<Shader.h>
#include<stb/stb_image.h>
#include<ImGui.h>
#include<glm/glm.hpp>
#include<vector>

#define Object Quad

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
	//visual
	class Visual
	{
	public:
		Visual() = default;
		virtual ~Visual() = default;
		Visual(const Visual&) = delete;
		Visual(Visual&&) = delete;
		Visual& operator=(const Visual&) = delete;
		Visual& operator=(Visual&&) = delete;
		virtual void bind(int slot = 0) const = 0;
		virtual std::pair<glm::vec2, glm::vec2> getUV() const = 0;
		static void unbind();
	};

	class Texture : public Visual
	{
	public:
		Texture(std::string filepath, int filter, glm::ivec2 textureRatio = { 1, 1 }, int sWrap = GL_CLAMP_TO_BORDER, int tWrap = GL_CLAMP_TO_BORDER);
		~Texture() override;
		Texture(const Texture&) = delete;
		Texture &operator=(const Texture &) = delete;
		void bind(int slot = 0) const override;
		static void unbind();
		std::pair<glm::vec2, glm::vec2> getUV() const override;
	private:
		uint32_t m_textureID;
		glm::ivec2 m_texRat;
	};

	class Animation : public Visual
	{
	public:
		Animation(std::string filepath, int filter, uint frames, float frametime, uint width, uint heigth);
		~Animation() override;
		Animation(const Animation&) = delete;
		Animation &operator=(const Animation &) = delete;
		void bind(int slot = 0) const override;
		static void unbind();
		std::pair<glm::vec2, glm::vec2> getUV() const override;
		void update(float deltaT);
	private:
		uint32_t m_textureID;
		uint m_frames;
		float m_frameTime;
		float m_timePassed;
		uint m_w, m_h;
	};

	//Rendering
	class Quad
	{
	public:
		Quad();
		~Quad();
		Quad(Quad && other) noexcept;
		Quad(const Quad&) = delete;
		Quad &operator=(Quad &&) = default;
		Quad &operator=(const Quad &) = delete;
		void setVisual(agl::Visual* visual);
		void setPosPtr(float* x, float* y);
		void setScalePtr(float* xScale, float* yScale);
		void setRotationPtr(float* rotation);
		void setColor(uchar red, uchar green, uchar blue, uchar alpha);
		void setColor(Color color);
		Color getColor() const;
		friend class GraphicLayer;
	private:
		float* m_x, *m_y;
		float* m_xScale, *m_yScale;
		float* m_rotation;
		agl::Visual* m_vis;
		Color m_color;
		GLuint m_VBO, m_EBO, m_VAO;
		bool lol = true;
	};

	class Camera
	{
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
	private:
		glm::vec2 m_pos;
		glm::vec2 m_size;
		float m_focalLengh;

	};

	class GraphicLayer
	{
	public:
		GraphicLayer(const GraphicLayer&) = delete;
		GraphicLayer(agl::Shader& shader, agl::Camera& camera);
		~GraphicLayer();
		void draw();
		agl::Quad* newQuad();
		//it dont be working tho
		void removeObject(agl::Quad* &obj);
	private:
		static uint32_t s_;
		agl::Shader* m_shader;
		agl::Camera* m_camera;
		std::vector<agl::Quad> m_quads;
	};

}

