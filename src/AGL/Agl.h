#pragma once
#include<dtl.h>
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<Shader.h>
#include<stb/stb_image.h>
#include<ImGui.h>
#include<glm/glm.hpp>
#include<vector>
#include<queue>

#define Object Quad

struct Vertice 
{
	glm::vec2 position;
	glm::vec2 uv;
	Vertice();
	Vertice(glm::vec2 pos, glm::vec2 UV = { 0.0f, 0.0f });
};

struct Color {
	uchar r, g, b, a;
	Color();
	Color(uchar red, uchar green, uchar blue, uchar alpha);
	[[nodiscard]] glm::vec4 getNormalized() const;
	Color operator+(Color c) const;
};


namespace agl
{
	void Init();
	void Terminate();
	//!visual==================================================================================================================================
	class Visual
	{
	public:
		Visual() = default;
		virtual ~Visual() = default;
		Visual(Visual&&) = delete;
		Visual(const Visual&) = delete;
		Visual& operator=(Visual&&) = delete;
		Visual& operator=(const Visual&) = delete;
		virtual void bind(int slot = 0) const = 0;
		[[nodiscard]] virtual std::pair<glm::vec2, glm::vec2> getUV() const = 0;
		static void unbind();
	};

	class Texture : public Visual
	{
	public:
		Texture(std::string filepath, int filter, glm::ivec2 textureRatio = { 1, 1 }, int sWrap = GL_CLAMP_TO_BORDER, int tWrap = GL_CLAMP_TO_BORDER);
		~Texture() override;
		Texture(Texture&& oth) noexcept;
		Texture& operator=(Texture&& oth) noexcept;
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		void bind(int slot = 0) const override;
		static void unbind();
		[[nodiscard]] std::pair<glm::vec2, glm::vec2> getUV() const override;
	private:
		uint32_t m_textureID;
		glm::ivec2 m_texRat;
	};

	class Animation : public Visual
	{
	public:
		Animation(std::string filepath, int filter, uint frames, float frametime, uint width, uint heigth);
		~Animation() override;
		Animation(Animation&& oth) noexcept;
		Animation(const Animation&) = delete;
		Animation& operator=(Animation&& oth) noexcept;
		Animation& operator=(const Animation&) = delete;

		void bind(int slot = 0) const override;
		static void unbind();
		[[nodiscard]] std::pair<glm::vec2, glm::vec2> getUV() const override;
		void update(float deltaT);
	private:
		uint32_t m_textureID;
		uint m_frames;
		float m_frameTime;
		float m_timePassed;
		uint m_w, m_h;
	};

	//!rendering==================================================================================================================================
	class Quad
	{
	public:
		Quad();
		~Quad();

		Quad(Quad && oth) noexcept;
		Quad(const Quad& oth) = delete;
		Quad &operator=(Quad && oth) noexcept;
		Quad &operator=(const Quad & oth) = delete;

		void setVisual(agl::Visual* visual);
		void setPosPtr(float* x, float* y);
		void setScalePtr(float* xScale, float* yScale);
		void setRotationPtr(float* rotation);
		void setColor(uchar red, uchar green, uchar blue, uchar alpha);
		void setColor(Color color);
		void setTexRepeat(float defxScale, float defyScale);
		[[nodiscard]] Color getColor() const;

		friend class GraphicLayer;
	private:
		float* m_x, *m_y;
		float* m_xScale, *m_yScale;
		float* m_rotation;
		float m_defxScale = 0.f, m_defyScale = 0.f;
		agl::Visual* m_vis;
		Color m_color;
		GLuint m_VBO, m_EBO, m_VAO;
		bool m_exists;
	};

	class Camera
	{
	public:
		Camera();
		Camera(float x, float y, glm::vec2 size, float focalLength);
		Camera(glm::vec2 position, float w, float h, float focalLength);
		Camera(float x, float y, float w, float h, float focalLength);
		Camera(glm::vec2 position, glm::vec2 size, float focalLength);

		~Camera() = default;
		Camera(Camera&&) = default;
		Camera(const Camera&) = default;
		Camera &operator=(Camera&&) = default;
		Camera &operator=(const Camera&) = default;

		void setFocalLength(float focalLength);
		void setPosition(float x, float y);
		void setPosition(glm::vec2 position);
		void setSize(float w, float h);
		void setSize(glm::vec2 size);
		[[nodiscard]] float getFocalLength() const;
		[[nodiscard]] glm::vec2 getPosition() const;
		[[nodiscard]] glm::vec2 getSize() const;
	private:
		glm::vec2 m_pos;
		glm::vec2 m_size;
		float m_focalLengh;
	};

	class GraphicLayer
	{
	public:
		GraphicLayer(agl::Shader& shader, agl::Camera& camera);

		~GraphicLayer() = default;
		GraphicLayer(GraphicLayer&&) noexcept = default;
		GraphicLayer(const GraphicLayer&) = delete;
		GraphicLayer &operator=(GraphicLayer&&) = default;
		GraphicLayer &operator=(const GraphicLayer&) = delete;

		void draw();
		uint32_t newQuad();
		void removeObject(uint32_t quad_ID);
		agl::Quad* getQuadPtr(uint32_t quad_ID);
	private:
		agl::Shader* m_shader;
		agl::Camera* m_camera;
		std::vector<agl::Quad> m_quads;
		std::queue<uint32_t> m_freeinxs;
	};

}

