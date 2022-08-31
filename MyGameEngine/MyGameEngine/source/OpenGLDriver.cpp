#include "OpenGLDriver.h"
#include "ResourceManager.h"

	//<생성자>
OpenGLDriver::OpenGLDriver(int _width, int _height, const char* _title, Scene* _scene)
	: width(_width), height(_height), title(_title), sceneToDraw(_scene)
{

}

	//<소멸자>
OpenGLDriver::~OpenGLDriver()
{

}

	//<public>
	//<override>
void OpenGLDriver::Init()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(window);	//GLEW 초기화
	glClearColor(0.2, 0.2f, 0.2f, 0.0f);
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	glEnable(GL_CULL_FACE);		//face culling 활성화
	glFrontFace(GL_CCW);				//시계반대방향이 전면
	glCullFace(GL_BACK);				//GL_BACK는 후면을 폐기, GL_FRONT_AND_BACK은 전면 후면 모두 폐기
	glEnable(GL_DEPTH_TEST);

	BeginScene();							//씬 시작
}

bool OpenGLDriver::Run()
{
	if (!glfwWindowShouldClose(window))
	{
		return true;
	}

	return false;
}

void OpenGLDriver::CloseDriver()
{
	glfwDestroyWindow(window);
	glfwTerminate();	//한번 초기화(glfwInit())된 것은 종료되어야 함

	ResourceManager::DestoryInst();
	delete sceneToDraw;
	delete this;
}

void OpenGLDriver::Loop()
{
	//Main에서 while문 내에 들어가야 할 내용!
	Camera();
	Input();
	LoopScene();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void OpenGLDriver::BeginScene()
{
	sceneToDraw->InitScene();
}

void OpenGLDriver::LoopScene()
{
	sceneToDraw->LoopScene();
}

void OpenGLDriver::Input()
{
	int key_w = glfwGetKey(window, GLFW_KEY_W);
	int key_s = glfwGetKey(window, GLFW_KEY_S);
	int key_a = glfwGetKey(window, GLFW_KEY_A);
	int key_d = glfwGetKey(window, GLFW_KEY_D);
	int key_c = glfwGetKey(window, GLFW_KEY_C);
	int key_space = glfwGetKey(window, GLFW_KEY_SPACE);
	if (key_w == GLFW_PRESS)
	{
		camZ -= 0.02f;
		std::cout << "W 키 입력" << "cam Z = " << camZ << std::endl;
	}
	if (key_s == GLFW_PRESS)
	{
		camZ += 0.02f;
		std::cout << "S 키 입력" << "cam Z = " << camZ << std::endl;
	}
	if (key_a == GLFW_PRESS)
	{
		camX -= 0.02f;
		std::cout << "A 키 입력" << "cam X = " << camX << std::endl;
	}
	if (key_d == GLFW_PRESS)
	{
		camX += 0.02f;
		std::cout << "D 키 입력" << "cam X = " << camX << std::endl;
	}
	if (key_c == GLFW_PRESS)
	{
		camY -= 0.02f;
		std::cout << "C 키 입력" << "cam Y = " << camY << std::endl;
	}
	if (key_space == GLFW_PRESS)
	{
		camY += 0.02f;
		std::cout << "Space 키 입력" << "cam Y= " << camY << std::endl;
	}
}

void OpenGLDriver::Camera()
{
	//Camera

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(75, (width / height), 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-camX, -camY, -camZ);
	gluLookAt(
		5.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
}

//======================Polyhedron======================

void OpenGLDriver::RenderTetrahedron()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat MyVertices[4][3] = {
		{ -1.0, -1.0, 1.0 },     // 0
		{ 1.0, -1.0, 1.0 },      // 1
		{ 0.0, 1.0, 0.0 },        // 2
		{ 0.0, -1.0, -1.0 },      // 3
	};

	GLfloat MyColors[4][3] = {
		{ 0.2, 0.2, 0.2 },
		{ 1.0, 0.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
	};

	GLubyte MyVertexList[18] = {
		0, 1, 2,
		0, 1, 3,
		1, 3, 2,
		2, 0, 3,
	};

	glPolygonMode(GL_FRONT, GL_LINE);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);
	for (GLint i = 0; i < 6; i++)
	{
		glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, &MyVertexList[3 * i]);
	}
	glPolygonMode(GL_FRONT, GL_FILL);
	glFlush();
}

void OpenGLDriver::RenderHexahedron()
{
	//unsigned int MyTextureObject[1];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
	//if (ResourceManager::Instance()->LoadGLTextures("bmp/apple.bmp", &MyTextureObject[0]))
	//{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
	//}
	
	glFlush();
}

void OpenGLDriver::RenderOBJ(
	bool _res,
	std::vector<glm::vec3> _vertices,
	std::vector<glm::vec3> _uvs,
	std::vector<glm::vec3> _normals)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	if (_res)
	{
		GLuint vertexbuffer;
		if (_vertices.size() != 0)
		{
			glGenBuffers(1, &vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
		}

		GLuint uvbuffer;
		if (_uvs.size() != 0)
		{
			glGenBuffers(1, &uvbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec3), &_uvs[0], GL_STATIC_DRAW);
		}

		GLuint normalbuffer;
		if (_normals.size() != 0)
		{
			glGenBuffers(1, &normalbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
		}

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

		glDrawArrays(GL_QUADS, 0, _vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	glFlush();
}