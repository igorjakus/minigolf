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


//!data structures==================================================================================================================================
Vertice::Vertice() :position({ 0.f, 0.f }), uv({ 0.f, 0.f }) {}
Vertice::Vertice(glm::vec2 pos, glm::vec2 UV)
	:position(pos), uv(UV) {}
Color::Color() : r(255), g(255),b(255),a(255) {}
Color::Color(uchar red, uchar green, uchar blue, uchar alpha) 
	: r(red), g(green), b(blue), a(alpha) {}

glm::vec4 Color::getNormalized() const
{ return { r / 255.f, g / 255.f, b / 255.f, a / 255.f }; }

Color Color::operator+(Color c) const
{ return { static_cast<uchar>(r + c.r), static_cast<uchar>(g + c.g), static_cast<uchar>(b + c.b), static_cast<uchar>(a + c.a) }; }




//!visual==================================================================================================================================
void agl::Visual::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

agl::Texture::Texture(std::string filepath, int filter, glm::ivec2 textureRatio/*= {1, 1}*/, int sWrap/* = GL_CLAMP_TO_BORDER*/, int tWrap/* = GL_CLAMP_TO_BORDER*/)
	:m_textureID(0), m_texRat(textureRatio)
{
	int w, h, bpp;
	stbi_set_flip_vertically_on_load(1);
	uint8_t* data = stbi_load(filepath.c_str(), &w, &h, &bpp, 4);
	if (data == nullptr) { DTL_ERR("Faild to load texture: \"{0}\"", filepath); return; }
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
agl::Texture::~Texture() { glDeleteTextures(1, &m_textureID); }
std::pair<glm::vec2, glm::vec2> agl::Texture::getUV() const { return { {0.f, 0.f}, m_texRat}; }
void agl::Texture::bind(int slot/*= 0*/) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

agl::Animation::Animation(std::string filepath, int filter, uint frames, float frametime, uint width, uint heigth)
	:m_textureID(0), m_frames(frames), m_frameTime(frametime), m_timePassed(0.f), m_w(width), m_h(heigth)
{
	int w, h, bpp;
	stbi_set_flip_vertically_on_load(1);
	uint8_t* data = stbi_load(filepath.c_str(), &w, &h, &bpp, 4);
	if (data == nullptr) { DTL_ERR("Faild to load texture: \"{0}\"", filepath); return; }
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
agl::Animation::~Animation() { glDeleteTextures(1, &m_textureID); }
std::pair<glm::vec2, glm::vec2> agl::Animation::getUV() const {
	const int currframe = m_timePassed / m_frameTime;
	return {
		{1.f / m_w * (currframe % m_w)			, 1.f / m_h * (m_h - 1 - (currframe / m_w))},
		{1.f / m_w * ((currframe % m_w) + 1)	, 1.f / m_h * (m_h - (currframe / m_w))}
	};
}
void agl::Animation::update(float deltaT)
{ m_timePassed += deltaT; if (m_timePassed >= m_frames * m_frameTime) m_timePassed -= m_frames * m_frameTime; }
void agl::Animation::bind(int slot/* = 0*/) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Animation::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }



//!rendering==================================================================================================================================
agl::Object::Object(float width, float height, glm::vec2 pos/*= { 0.f, 0.f }*/, Color color/* = {255, 255, 255, 255}*/, glm::ivec2 texRatio/*= {1, 1}*/)
	:m_pos({pos}), m_texRatio(texRatio), m_xScale(width), m_yScale(height), m_rotation(0.f), m_vis(nullptr), m_color(color) {}
agl::Object::~Object(){}

//transform funcions
void agl::Object::setVisual(agl::Visual& visual) { m_vis = &visual; }
void agl::Object::setRotation(float radians) { m_rotation = radians; }
void agl::Object::setScale(float xScale, float yScale) { m_xScale = xScale; m_yScale = yScale; }
void agl::Object::setPosition(float xPos, float yPos) { m_pos = { xPos, yPos }; }
void agl::Object::setPosition(glm::vec2 pos) { m_pos = pos; }
void agl::Object::setColor(uchar red, uchar green, uchar blue, uchar alpha) { m_color = { red, green, blue, alpha }; }
void agl::Object::setColor(Color color) { m_color = color; }
Color agl::Object::getColor() const { return m_color; }
float agl::Object::getRotation() const { return m_rotation; }
glm::vec2 agl::Object::getScale() const { return { m_xScale, m_yScale }; }
glm::vec2 agl::Object::getPosition() const { return m_pos; }

agl::GraphicLayer::GraphicLayer(agl::Shader& shader, agl::Camera& camera)
	:m_shader(&shader), m_camera(&camera) {}

agl::GraphicLayer::~GraphicLayer()
{
	for (int i = 0; i < m_bd.size(); ++i)
	{
		glDeleteBuffers(1, &m_bd[i].VBO);
		glDeleteBuffers(1, &m_bd[i].EBO);
		glDeleteVertexArrays(1, &m_bd[i].VAO);
	}
}

void agl::GraphicLayer::draw()
{
	m_shader->bind();

	const glm::vec2 pos = m_camera->getPosition();
	const glm::vec2 size = m_camera->getSize();
	const float focl = m_camera->getFocalLength();
	const glm::mat4 proj = glm::ortho(pos.x - (size.x / 2) * focl, pos.x + (size.x / 2) * focl, pos.y - (size.y / 2) * focl, pos.y + (size.y / 2) * focl, -1.f, 1.f);
	m_shader->setUniformMatrix4("u_P", proj);
	for (int i = 0; i < m_bd.size(); ++i)
	{
		glBindVertexArray(m_bd[i].VAO);
		glm::dvec2 blV = m_bd[i].objptr->m_vis->getUV().first;
		glm::dvec2 trV = m_bd[i].objptr->m_vis->getUV().second;
		Vertice objectData[4] = {
		{{-.5f, -.5f,}	, static_cast<glm::vec2>(blV)},
		{{ .5f, -.5f,}	, {static_cast<float>(trV.x), static_cast<float>(blV.y)}},
		{{-.5f,  .5f,}	, {static_cast<float>(blV.x), static_cast<float>(trV.y)}},
		{{ .5f,  .5f,}	, static_cast<glm::vec2>(trV)} };

		glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertice), objectData);
		m_shader->setUniformMatrix4("u_T", glm::translate(glm::mat4(1.f), glm::vec3(m_bd[i].objptr->m_pos, 0.f)));
		m_shader->setUniformMatrix4("u_R", glm::rotate(glm::mat4(1.f), glm::radians(m_bd[i].objptr->m_rotation), glm::vec3(0.f, 0.f, 1.f)));
		m_shader->setUniformMatrix4("u_S", glm::scale(glm::mat4(1.f), glm::vec3(m_bd[i].objptr->m_xScale, m_bd[i].objptr->m_yScale, 1.f)));
		m_shader->setUniform4f("u_Col", m_bd[i].objptr->m_color.getNormalized());
		if (m_bd[i].objptr->m_vis != nullptr) {
			m_shader->setUniform1i("u_Tex", 0);
			m_shader->setUniform1i("u_Texuse", 1);
			m_bd[i].objptr->m_vis->bind(0); }
		else { m_shader->setUniform1i("u_Texuse", 0); }
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
	}
	agl::Shader::unbind();
}

void agl::GraphicLayer::addObject(Object& obj)
{
	m_bd.push_back({ 0, 0, 0, nullptr });
	// vertex buffer generation and setup
	glCreateVertexArrays(1, &(*(m_bd.end() - 1)).VAO);
	glBindVertexArray((*(m_bd.end() - 1)).VAO);
	glGenBuffers(1, &(*(m_bd.end() - 1)).VBO);
	glBindBuffer(GL_ARRAY_BUFFER, (*(m_bd.end() - 1)).VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertice), nullptr, GL_STATIC_DRAW);
	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
	// uv attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	// element buffer generation and setup
	glGenBuffers(1, &(*(m_bd.end() - 1)).EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(m_bd.end() - 1)).EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), nullptr, GL_STATIC_DRAW);

	(*(m_bd.end() - 1)).objptr = &obj;

	Vertice objectData[4] = {
		{{-.5f, -.5f,}	, {0.f, 0.f}},
		{{ .5f, -.5f,}	, {1.f, 0.f}},
		{{-.5f,  .5f,}	, {0.f, 1.f}},
		{{ .5f,  .5f,}	, {1.f, 1.f}} };

	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertice), &objectData[0]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 6 * sizeof(uint32_t), &m_trisStencile[0]);

	glBindVertexArray(0);
}

void agl::GraphicLayer::removeObject(Object& obj)
{
	for (int i = 0; i < m_bd.size(); ++i) 
	{ 
		if (m_bd[i].objptr == &obj)
		{
			glDeleteBuffers(1, &m_bd[i].VBO);
			glDeleteBuffers(1, &m_bd[i].EBO);
			glDeleteVertexArrays(1, &m_bd[i].VAO);
			m_bd.erase(m_bd.begin() + i); 
			break;
		} 
	}
}

agl::Camera::Camera(float x, float y, glm::vec2 size, float focalLength)
	:m_pos(x, y), m_size(size), m_focalLengh(focalLength) {}
agl::Camera::Camera(glm::vec2 position, float w, float h, float focalLength)
	:m_pos(position), m_size(w, h), m_focalLengh(focalLength) {}
agl::Camera::Camera(float x, float y, float w, float h, float focalLength)
	:m_pos(x, y), m_size(w, h), m_focalLengh(focalLength) {}
agl::Camera::Camera(glm::vec2 position, glm::vec2 size, float focalLength)
	:m_pos(position), m_size(size), m_focalLengh(focalLength) {}
agl::Camera::~Camera() {}

void agl::Camera::setFocalLength(float focalLength) { m_focalLengh = focalLength; }
void agl::Camera::setPosition(float x, float y) { m_pos = { x, y }; }
void agl::Camera::setPosition(glm::vec2 position) { m_pos = position; }
void agl::Camera::setSize(float w, float h) { m_size = { w, h }; }
void agl::Camera::setSize(glm::vec2 size) { m_size = size; }
float agl::Camera::getFocalLength() { return m_focalLengh; }
glm::vec2 agl::Camera::getPosition() { return m_pos; }
glm::vec2 agl::Camera::getSize() { return m_size; }
