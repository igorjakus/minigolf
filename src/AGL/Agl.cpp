#include<pch.h>
#include<Agl.h>

void agl::Init()
{
	//gfwd init
	if (!glfwInit())
	{ dtl::Log.error("Failed to initialize GLFW"); exit(EXIT_FAILURE); }
	//imgui init
	bool imguiInit = IMGUI_INIT;
	if (!imguiInit) {/*todo Logging*/ };
}
void agl::Terminate()
{
	IMGUI_TERMINATE;
	glfwTerminate();
}
//?data structures---------------------------------------------------------------------------------------------------------------------------------------
Vertice::Vertice() :position({ 0.f, 0.f }), uv({0.0f, 0.0f}) {}
Vertice::Vertice(glm::vec2 pos, glm::vec2 UV)
	:position(pos), uv(UV) {}

//?textures---------------------------------------------------------------------------------------------------------------------------------------
agl::Texture::Texture(std::string filepath, int filter, int sWrap, int tWrap)
	:m_textureID(0), m_widthImg(0), m_heightImg(0), m_BPP(0), m_bytesData(nullptr)
{ 
	stbi_set_flip_vertically_on_load(1);
	m_bytesData = stbi_load(filepath.c_str(), &m_widthImg, &m_heightImg, &m_BPP, 4);
	if(m_bytesData == nullptr) dtl::Log.error("Faild to load texture: \"{0}\"", filepath);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_widthImg, m_heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_bytesData);
	
	if(m_bytesData != nullptr)	stbi_image_free(m_bytesData);
	stbi_set_flip_vertically_on_load(0);
}
agl::Texture::~Texture() { glDeleteTextures(1, &m_textureID); }

void agl::Texture::bind(int slot/*= 0*/) const { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

//?rendering---------------------------------------------------------------------------------------------------------------------------------------
agl::Object::Object(float width, float height, agl::Texture& texture, glm::vec2 position /*= {0.f, 0.f}*/,glm::ivec2 texRatio/*= {1, 1}*/)
	:m_pos({position}), m_texRatio(texRatio), m_xScale(width), m_yScale(height), m_rotation(0.f), m_tex(&texture) {}

agl::Object::~Object(){}

//transform funcions
void agl::Object::setTexture(agl::Texture& texture) { m_tex = &texture; }
void agl::Object::setRotation(float radians) { m_rotation = radians; }
void agl::Object::setScale(float xScale, float yScale) { m_xScale = xScale; m_yScale = yScale; }
void agl::Object::setPosition(float xPos, float yPos) { m_pos = { xPos, yPos }; }
void agl::Object::setPosition(glm::vec2 pos) { m_pos = pos; }
float agl::Object::getRotation() { return m_rotation; }
glm::vec2 agl::Object::getScale() { return { m_xScale, m_yScale }; }
glm::vec2 agl::Object::getPosition() { return m_pos; }

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
	m_shader->setUniform1i("u_Tex", 0);

	glm::vec2 pos = m_camera->getPosition();
	glm::vec2 size = m_camera->getSize();
	float fl = m_camera->getFocalLength();
	glm::mat4 proj = glm::ortho(pos.x - (size.x/2)*fl, pos.x + (size.x/2)*fl, pos.y - (size.y/2)*fl, pos.y + (size.y/2)*fl, -1.0f, 1.0f);
	m_shader->setUniformMatrix4("u_P", proj);
	for (int i = 0; i < m_bd.size(); ++i)
	{
		glBindVertexArray(m_bd[i].VAO);
		m_shader->setUniformMatrix4("u_T", glm::translate(glm::mat4(1.f), glm::vec3(m_bd[i].objptr->m_pos, 0.f)));
		m_shader->setUniformMatrix4("u_R", glm::rotate(glm::mat4(1.f), glm::radians(m_bd[i].objptr->m_rotation), glm::vec3(0.f, 0.f, 1.f)));
		m_shader->setUniformMatrix4("u_S", glm::scale(glm::mat4(1.f), glm::vec3(m_bd[i].objptr->m_xScale, m_bd[i].objptr->m_yScale, 1.f)));
		m_bd[i].objptr->m_tex->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
	}
	m_shader->unbind();
}

void agl::GraphicLayer::addObject(Object& obj)
{
	m_bd.push_back({0, 0, 0, nullptr});
	//vertex buffer generation and setup
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
	//element buffer generation and setup
	glGenBuffers(1, &(*(m_bd.end() - 1)).EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(m_bd.end() - 1)).EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), nullptr, GL_STATIC_DRAW);

	(*(m_bd.end() - 1)).objptr = &obj;

	Vertice objectData[4] = {
		{{-.5f, -.5f,}	, {0.0f, 0.0f}},
		{{ .5f, -.5f,}	, {obj.m_texRatio.x, 0.0f}},
		{{-.5f,  .5f,}	, {0.0f, obj.m_texRatio.y}},
		{{ .5f,  .5f,}	, obj.m_texRatio}};

	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertice), objectData);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 6 * sizeof(uint32_t), m_trisStencile);

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
