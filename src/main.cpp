#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render/ShaderProgram.h"
#include <iostream>
#include<math.h>

int g_winSizeX = 840;
int g_winSizeY = 620;

GLfloat point[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat color[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

const char* vertex_shader = 
"#version 460\n"
"layout(location=0) in vec3 vertex_position;"
"layout(location=1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader = 
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"   frag_color = vec4(color, 1.0);"
"}";

void glfwKeyBack(GLFWwindow* pWin, int key, int scancode, int action, int mode)
{
	if(key==GLFW_KEY_X && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWin, GL_TRUE);
	}

	static float time = 0.0f; 
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) 
	{
		time += 0.05f;
		float x = (sin(time) + 1.0f) / 2.0f; 
		glClearColor(x, 0.4f, 0.8f, 1.0f);
	}
}

void glfwScreenSizeBack(GLFWwindow* pWin, int width, int height)
{
	g_winSizeX = width;
	g_winSizeY = height;
	glViewport(0, 0, g_winSizeX, g_winSizeY);
}

int main(void)
{
    if (!glfwInit()) 
	{
		std::cout<<"glfwInit Error"<<std::endl;
		return -1;
	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(g_winSizeX, g_winSizeY, "HellNahh", nullptr, nullptr);
    if (!pWindow)
    {
		std::cout<<"Error open window"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);

	glfwSetKeyCallback(pWindow, glfwKeyBack);
	glfwSetWindowSizeCallback(pWindow, glfwScreenSizeBack);

	if(!gladLoadGL())
	{
		std::cout<<"Cant open glad!" << std::endl;
		return -1;
	}
	std::cout<<"Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout<<"OpenGL: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.6, 0.4, 0.8, 0);

	std::string vertexShader(vertex_shader);
	std::string fragmentShader(fragment_shader);
	Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);
	if(!shaderProgram.isCompiled()) 
	{
		std::cerr<<"Error creating shader program :("<<std::endl;
		return -1;
	}
	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
	std::cout<<"по сьебам пацаны"<<std::endl;
    return 0;
}