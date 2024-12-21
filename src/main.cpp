#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	glClearColor(0.7,0.33,0,0.5);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	glLinkProgram(shader_program);

	glDeleteShader(vs);
	glDeleteShader(fs);

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
		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
	std::cout<<"по сьебам пацаны"<<std::endl;
    return 0;
}