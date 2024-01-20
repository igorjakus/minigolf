#include<pch.h>
#include<Agl.h>

void agl::Init()
{
	//gfwd init
	if (glfwInit() == GLFW_FALSE)
	{ DTL_ERR("Failed to initialize GLFW"); exit(EXIT_FAILURE); }
	//imgui init
	const bool imguiInit = IMGUI_INIT;
	if (!imguiInit) { DTL_ERR("Failed to initialize ImGui"); };
}
void agl::Terminate()
{
	IMGUI_TERMINATE;
	glfwTerminate();
}
//!DATA STRUCTURES========================================================================================================================================================================================================
Vertice::Vertice() :position({ 0.f, 0.f }), uv({ 0.f, 0.f }) {}
Vertice::Vertice(glm::vec2 pos, glm::vec2 UV)
	:position(pos), uv(UV) {}
Color::Color() : r(255), g(255),b(255),a(255) {}
Color::Color(uchar red, uchar green, uchar blue, uchar alpha) 
	: r(red), g(green), b(blue), a(alpha) {}

glm::vec4 Color::getNormalized() const
{ return { static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, static_cast<float>(a) / 255.f }; }

Color Color::operator+(Color c) const
{ return { static_cast<uchar>(r + c.r), static_cast<uchar>(g + c.g), static_cast<uchar>(b + c.b), static_cast<uchar>(a + c.a) }; }

void agl::Visual::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

//!TEXTURE===================================================================================================================================================================================================================
agl::Texture::Texture(std::string filepath, int filter, glm::ivec2 textureRatio/*= {1, 1}*/, int sWrap/* = GL_CLAMP_TO_BORDER*/, int tWrap/* = GL_CLAMP_TO_BORDER*/)
	:m_textureID(0), m_texRat(textureRatio)
{
	int width = 0; int height = 0; int bpp = 0;
	stbi_set_flip_vertically_on_load(1);
	uint8_t* data = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);
	if (data == nullptr) { DTL_ERR("Faild to load texture: \"{0}\"", filepath); return; }
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
agl::Texture::~Texture() { if (m_textureID != 0) { glDeleteTextures(1, &m_textureID); }}

std::pair<glm::vec2, glm::vec2> agl::Texture::getUV() const { return { {0.f, 0.f}, m_texRat }; }
void agl::Texture::bind(int slot/*= 0*/) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

agl::Texture::Texture(Texture&& oth) noexcept
	:m_textureID(oth.m_textureID), m_texRat(oth.m_texRat) 
{ oth.m_textureID = 0; }
agl::Texture& agl::Texture::operator=(Texture&& oth) noexcept
{
	m_textureID = oth.m_textureID;
	m_texRat = oth.m_texRat;
	oth.m_textureID = 0;
	return *this;
}

//!ANIMATION===================================================================================================================================================================================================================
agl::Animation::Animation(std::string filepath, int filter, uint frames, float frametime, uint width, uint heigth)
	:m_textureID(0), m_frames(frames), m_frameTime(frametime), m_timePassed(0.f), m_w(width), m_h(heigth)
{
	int wid = 0; int hei = 0; int bpp = 0;
	stbi_set_flip_vertically_on_load(1);
	uint8_t* data = stbi_load(filepath.c_str(), &wid, &hei, &bpp, 4);
	if (data == nullptr) { DTL_ERR("Faild to load texture: \"{0}\"", filepath); return; }
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, wid, hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
agl::Animation::~Animation() { if (m_textureID != 0) { glDeleteTextures(1, &m_textureID); }}
std::pair<glm::vec2, glm::vec2> agl::Animation::getUV() const {
	const int currframe = static_cast<int>(m_timePassed / m_frameTime);
	return {
		{1.f / static_cast<float>(m_w * (currframe % m_w))			, 1.f / static_cast<float>(m_h * (m_h - 1 - (static_cast<uint32_t>(currframe) / m_w)))},
		{1.f / static_cast<float>(m_w * ((currframe % m_w) + 1))	, 1.f / static_cast<float>(m_h * (m_h - (static_cast<uint32_t>(currframe) / m_w)))}
	};
}

void agl::Animation::update(float deltaT)
{ m_timePassed += deltaT; if (m_timePassed >= static_cast<float>(m_frames) * m_frameTime) { m_timePassed -= static_cast<float>(m_frames) * m_frameTime; } }
void agl::Animation::bind(int slot/* = 0*/) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Animation::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

agl::Animation::Animation(Animation&& oth) noexcept
	:m_textureID(oth.m_textureID), m_frames(oth.m_frames), m_frameTime(oth.m_frameTime), m_timePassed(oth.m_timePassed), m_w(oth.m_w), m_h(oth.m_h)
{ oth.m_textureID = 0; }
agl::Animation& agl::Animation::operator=(Animation&& oth) noexcept
{
	m_textureID = oth.m_textureID; m_textureID = oth.m_textureID; m_frames = oth.m_frames; 
	m_frameTime = oth.m_frameTime; m_timePassed = oth.m_timePassed; m_w = oth.m_w; m_h = oth.m_h;
	oth.m_textureID = 0;
	return *this;
}

//!QUAD===================================================================================================================================================================================================================
agl::Quad::Quad() 
	:m_x(nullptr), m_y(nullptr), m_xScale(nullptr), m_yScale(nullptr), m_rotation(nullptr), m_vis(nullptr), 
	m_defxScale(0.f), m_defyScale(0.f), m_color({ 255, 255, 255, 255 }), m_VBO(0), m_EBO(0), m_VAO(0), m_exists(true) {}

//transform funcions 
void agl::Quad::setVisual(agl::Visual* visual) { m_vis = visual; }
void agl::Quad::setPosPtr(float* x, float* y) { m_x = x; m_y = y; }
void agl::Quad::setScalePtr(float* xScale, float* yScale) { m_xScale = xScale; m_yScale = yScale; }
void agl::Quad::setRotationPtr(float* rotation) { m_rotation = rotation; }
void agl::Quad::setColor(uchar red, uchar green, uchar blue, uchar alpha) { m_color = { red, green, blue, alpha }; }
void agl::Quad::setColor(Color color) { m_color = color; }
void agl::Quad::setTexRepeat(float defxScale, float defyScale) { m_defxScale = defxScale; m_defyScale = defyScale; }
Color agl::Quad::getColor() const { return m_color; }

agl::Quad::~Quad() 
{
	if (m_VBO != 0) glDeleteBuffers(1, &m_VBO); //NOLINT
	if (m_EBO != 0) glDeleteBuffers(1, &m_EBO); //NOLINT
	if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO); //NOLINT
}

agl::Quad::Quad(Quad && oth) noexcept
	:m_x(oth.m_x), m_y(oth.m_y), m_xScale(oth.m_xScale), m_yScale(oth.m_yScale), m_rotation(oth.m_rotation), m_defxScale(oth.m_defxScale),
	m_defyScale(oth.m_defyScale), m_vis(oth.m_vis), m_color(oth.m_color), m_VBO(oth.m_VBO), m_EBO(oth.m_EBO), m_VAO(oth.m_VAO), m_exists(oth.m_exists)
{
	oth.m_VBO = 0;
	oth.m_EBO = 0;
	oth.m_VAO = 0;
}

agl::Quad& agl::Quad::operator=(Quad && oth) noexcept
{
	m_x = oth.m_x; m_y = oth.m_y; m_xScale = oth.m_xScale; m_yScale = oth.m_yScale; m_rotation = oth.m_rotation; m_defxScale = oth.m_defxScale; 
	m_defyScale = oth.m_defyScale; m_vis = oth.m_vis; m_color = oth.m_color; m_VBO = oth.m_VBO; m_EBO = oth.m_EBO; m_VAO = oth.m_VAO; m_exists = oth.m_exists;
	oth.m_VBO = 0;
	oth.m_EBO = 0;
	oth.m_VAO = 0;
	return *this;
}

//!CAMERA===================================================================================================================================================================================================================
agl::Camera::Camera() :m_pos(0, 0), m_size(1, 1), m_focalLengh(1) {}
agl::Camera::Camera(float x, float y, glm::vec2 size, float focalLength)
	:m_pos(x, y), m_size(size), m_focalLengh(focalLength) {}
agl::Camera::Camera(glm::vec2 position, float w, float h, float focalLength)
	:m_pos(position), m_size(w, h), m_focalLengh(focalLength) {}
agl::Camera::Camera(float x, float y, float w, float h, float focalLength)
	:m_pos(x, y), m_size(w, h), m_focalLengh(focalLength) {}
agl::Camera::Camera(glm::vec2 position, glm::vec2 size, float focalLength)
	:m_pos(position), m_size(size), m_focalLengh(focalLength) {}

void agl::Camera::setFocalLength(float focalLength) { m_focalLengh = focalLength; }
void agl::Camera::setPosition(float x, float y) { m_pos = { x, y }; }
void agl::Camera::setPosition(glm::vec2 position) { m_pos = position; }
void agl::Camera::setSize(float w, float h) { m_size = { w, h }; }
void agl::Camera::setSize(glm::vec2 size) { m_size = size; }
float agl::Camera::getFocalLength() const { return m_focalLengh; }
glm::vec2 agl::Camera::getPosition() const { return m_pos; }
glm::vec2 agl::Camera::getSize() const { return m_size; }

//!GRAPHICS LAYER============================================================================================================================================================================================================

agl::GraphicLayer::GraphicLayer(agl::Shader& shader, agl::Camera& camera)
	:m_shader(&shader), m_camera(&camera) {}

void agl::GraphicLayer::draw()
{
	m_shader->bind();

	const glm::vec2 pos = m_camera->getPosition();
	const glm::vec2 size = m_camera->getSize();
	const float focl = m_camera->getFocalLength();
	const glm::mat4 proj = glm::ortho(pos.x - (size.x / 2) * focl, pos.x + (size.x / 2) * focl, pos.y - (size.y / 2) * focl, pos.y + (size.y / 2) * focl, -1.f, 1.f);
	m_shader->setUniformMatrix4("u_P", proj);
	for (auto &quad : m_quads)
	{
		if (!quad.m_exists) { continue; }
		glBindVertexArray(quad.m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, quad.m_VBO);
		glm::dvec2 botomLeftVert;
		glm::dvec2 topRightVert;
		if(quad.m_vis != nullptr)
		{ botomLeftVert = quad.m_vis->getUV().first; topRightVert = quad.m_vis->getUV().second; }
		else
		{ botomLeftVert = { 0.0, 0.0 }; topRightVert = { 1.0, 1.0 }; }
		if (quad.m_defxScale != 0.f || quad.m_defyScale != 0.f) 
		{
			topRightVert.x *= *quad.m_xScale / quad.m_defxScale;
			topRightVert.y *= *quad.m_yScale / quad.m_defyScale;
		}

		const std::array<Vertice, 4> objectData = {{
		{{-.5f, -.5f,}, {static_cast<glm::vec2>(botomLeftVert)}}, {{ .5f, -.5f,}, {static_cast<float>(topRightVert.x), static_cast<float>(botomLeftVert.y)}},
		{{-.5f,  .5f,}, {static_cast<float>(botomLeftVert.x), static_cast<float>(topRightVert.y)}}, {{ .5f,  .5f,}, {static_cast<glm::vec2>(topRightVert)}} }};

		glBufferSubData(GL_ARRAY_BUFFER, 0, objectData.size() * sizeof(Vertice), objectData.data());
		m_shader->setUniformMatrix4("u_T", glm::translate(glm::mat4(1.f), glm::vec3(*quad.m_x, *quad.m_y, 0.f)));
		m_shader->setUniformMatrix4("u_R", glm::rotate(glm::mat4(1.f), glm::radians(*quad.m_rotation), glm::vec3(0.f, 0.f, 1.f)));
		m_shader->setUniformMatrix4("u_S", glm::scale(glm::mat4(1.f), glm::vec3(*quad.m_xScale, *quad.m_yScale, 1.f)));
		m_shader->setUniform4f("u_Col", quad.m_color.getNormalized());
		if (quad.m_vis != nullptr) {
			m_shader->setUniform1i("u_Tex", 0);
			m_shader->setUniform1i("u_Texuse", 1);
			quad.m_vis->bind(0); 
		}
		else { m_shader->setUniform1i("u_Texuse", 0); }
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
	}

	agl::Shader::unbind();
}

uint32_t agl::GraphicLayer::newQuad()
{
	const std::array<uint32_t, 6> m_trisStencile = { 0, 1, 2, 2, 3, 1 };
	const std::array<Vertice, 4> objectData = {{ {{-.5f, -.5f}, {.0f, .0f}}, {{.5f, -.5f}, {1.f, .0f}}, {{-.5f, .5f}, {.0f, 1.f}}, {{.5f, .5f}, {1.f, 1.f}} }};
	//createing a new quad
	agl::Quad* quad = nullptr;
	uint inx = 0;
	if (!m_freeinxs.empty()) { 
		inx = m_freeinxs.front();
		new (&m_quads[inx]) agl::Quad();
		quad = &m_quads[inx];
		m_freeinxs.pop();
	}
	else { m_quads.emplace_back(); quad = &(*(m_quads.end() - 1)); inx = m_quads.size() - 1; }
	//vertex buffer generation and setup
	glCreateVertexArrays(1, &quad->m_VAO);
	glBindVertexArray(quad->m_VAO);
	glGenBuffers(1, &quad->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, quad->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, objectData.size() * sizeof(Vertice), nullptr, GL_STATIC_DRAW);
	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float))); //NOLINT
	// uv attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); //NOLINT
	//element buffer generation and setup
	glGenBuffers(1, &quad->m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_trisStencile.size() * sizeof(uint32_t), nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, objectData.size() * sizeof(Vertice), objectData.data());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_trisStencile.size() * sizeof(uint32_t), m_trisStencile.data());

	glBindVertexArray(0);

	return inx; 
}


void agl::GraphicLayer::removeObject(uint32_t quad_ID)
{
	if (quad_ID >= m_quads.size()) return; //NOLINT
	m_quads[quad_ID].m_exists = false;
	m_freeinxs.push(quad_ID);
}

agl::Quad* agl::GraphicLayer::getQuadPtr(uint32_t quad_ID) { return &m_quads[quad_ID]; }
