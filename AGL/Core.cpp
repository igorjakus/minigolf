#include"Precomps.h"
#include"core.h"

void agl::Init()
{
	//gfwd init
	if (!glfwInit())
	{ Log.error("Failed to initialize GLFW"); exit(EXIT_FAILURE); }
	//imgui init
	if (!ImGui::CreateContext())
	{ Log.error("Failed to initialize ImGui"); exit(EXIT_FAILURE); }
	IMGUI_CHECKVERSION();
	//stb_image setup
	stbi_set_flip_vertically_on_load(true);
}
void agl::Terminate()
{
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
//?data structures---------------------------------------------------------------------------------------------------------------------------------------
Vertice::Vertice() :position({ 0.f, 0.f }), uv({0.0f, 0.0f}) {}
Vertice::Vertice(glm::vec2 pos, glm::vec2 UV)
	:position(pos), uv(UV) {}

//?textures---------------------------------------------------------------------------------------------------------------------------------------
agl::Texture::Texture(std::string filepath, int filter, int sWrap, int tWrap)
	:m_textureID(0), m_widthImg(0), m_heightImg(0), m_BPP(0), m_bytesData(nullptr)
{ 
	m_bytesData = stbi_load(filepath.c_str(), &m_widthImg, &m_heightImg, &m_BPP, 4);
	if(!m_bytesData) Log.error("Faild to load texture: \"{0}\"", filepath);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_widthImg, m_heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_bytesData);
	
	if(m_bytesData)	stbi_image_free(m_bytesData);
}
agl::Texture::~Texture() { glDeleteTextures(1, &m_textureID); }

void agl::Texture::bind(int slot/*= 0*/) { glActiveTexture(GL_TEXTURE0 + slot); glBindTexture(GL_TEXTURE_2D, m_textureID); }
void agl::Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

//?rendering---------------------------------------------------------------------------------------------------------------------------------------
agl::Object::Object(float width, float height, agl::Texture& texture, glm::vec2 position /*= {0.f, 0.f}*/,glm::ivec2 texRatio/*= {1, 1}*/)
	:m_pos({position}), m_tRat(texRatio), m_xs(width), m_ys(height), m_rot(0.f), m_tex(&texture)
{ m_transform(); }

agl::Object::~Object(){}

//transform funcions
void agl::Object::setTexture(agl::Texture& texture) { m_tex = &texture; }
void agl::Object::setRotation(float rads) { m_rot = rads; m_transform(); }
void agl::Object::setScale(float xScale, float yScale) { m_xs = xScale; m_ys = yScale; m_transform(); }
void agl::Object::setPosition(float xPos, float yPos) { m_pos = { xPos, yPos }; m_transform(); }
void agl::Object::setPosition(glm::vec2 pos) { m_pos = pos; m_transform(); }
void agl::Object::rotate(float rads) { m_rot += rads; m_transform(); }
void agl::Object::scale(float xScale, float yScale) { m_xs += xScale; m_ys += yScale; m_transform(); }
void agl::Object::move(float xPos, float yPos) { m_pos.x += xPos; m_pos.y += yPos; m_transform(); }
void agl::Object::move(glm::vec2 pos) { m_pos += pos; }
void agl::Object::m_transform() { m_model = glm::translate(glm::mat4(1.f), glm::vec3(m_pos, 0.f)) * glm::rotate(glm::mat4(1.f), glm::radians(m_rot), glm::vec3(0.f, 0.f, 1.f)) * glm::scale(glm::mat4(1.f), glm::vec3(m_xs, m_ys, 1.f)); }


agl::Renderer::Renderer(GL::Shader* shader)
	:m_shader(shader){}

agl::Renderer::~Renderer()
{
	for (int i = 0; i < m_bd.size(); ++i)
	{
		glDeleteBuffers(1, &m_bd[i].VBO);
		glDeleteBuffers(1, &m_bd[i].EBO);
		glDeleteVertexArrays(1, &m_bd[i].VAO);
	}
}

void agl::Renderer::draw()
{
	m_shader->bind();
	m_shader->setUniform1i("u_Tex", 0);
	for (int i = 0; i < m_bd.size(); ++i)
	{
		glBindVertexArray(m_bd[i].VAO);
		m_shader->setUniformMatrix4("u_M", m_bd[i].objptr->m_model);
		m_bd[i].objptr->m_tex->bind();
		glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, nullptr );
	}
	m_shader->unbind();
}

void agl::Renderer::addObject(Object& obj)
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
		{{-.5f, -.5f,}	, {0.0f			, 0.0f			}},
		{{ .5f, -.5f,}	, {obj.m_tRat.x	, 0.0f			}},
		{{-.5f,  .5f,}	, {0.0f			, obj.m_tRat.y	}},
		{{ .5f,  .5f,}	, obj.m_tRat					}};

	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertice), objectData);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 6 * sizeof(uint32_t), m_trisStencile);

	glBindVertexArray(0);
}

void agl::Renderer::removeObject(Object& obj)
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

