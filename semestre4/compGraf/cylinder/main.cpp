// g++ main.cpp -lglfw -lGL -lGLEW -o a && ./a

//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-10-06                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>

//---------------------------------//
//------------ Defines ------------//
//---------------------------------//
#define MAIN_WINDOW_WIDTH 800
#define MAIN_WINDOW_HEIGHT 800
float RATIO = float(MAIN_WINDOW_WIDTH)/MAIN_WINDOW_HEIGHT;

//---------------------------------//
//------ Terminal Color Code ------//
//---------------------------------//
// https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
// The following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET       "\033[0m"
#define BLACK       "\033[30m"              /* Black */
#define RED         "\033[31m"              /* Red */
#define GREEN       "\033[32m"              /* Green */
#define YELLOW      "\033[33m"              /* Yellow */
#define BLUE        "\033[34m"              /* Blue */
#define MAGENTA     "\033[35m"              /* Magenta */
#define CYAN        "\033[36m"              /* Cyan */
#define WHITE       "\033[37m"              /* White */
#define BOLDBLACK   "\033[1m\033[30m"       /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"       /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"       /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"       /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"       /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White */

#define QTY_FACES 100
//---------------------------------//
//-------- GLOBAL VARIABLES -------//
//---------------------------------//
float tx = 0;
float ty = 0;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
float scale = 0.5f;

//---------------------------------//
//------------ SHADERS ------------//
//---------------------------------//
// GLSL para Vertex Shader
const char* vertex_code =
	"attribute vec3 position;\n"
	"uniform mat4 model;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = model*vec4(position, 1.0);\n"
	"}\n";

// GLSL para Fragment Shader
const char* fragment_code =
	"uniform vec4 color;\n"
	"void main()\n"
	"{\n"
	"    gl_FragColor = color;\n"
	"}\n";
//---------------------------------//
//-------------- GLFW -------------//
//---------------------------------//

// funcao para processar eventos de teclado
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch(key)
	{
		case GLFW_KEY_W:
			ty += 0.01;
			break;
		case GLFW_KEY_A:
			tx -= 0.01;
			break;
		case GLFW_KEY_S:
			ty -= 0.01;
			break;
		case GLFW_KEY_D:
			tx += 0.01;
			break;
		case GLFW_KEY_X:
			angleX += 0.01;
			break;
		case GLFW_KEY_Y:
			angleY += 0.01;
			break;
		case GLFW_KEY_Z:
			angleZ += 0.01;
			break;
		case GLFW_KEY_UP:
			scale += 0.02;
			break;
		case GLFW_KEY_DOWN:
			scale -= 0.02;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
	}
}
void initWindow(GLFWwindow **mainWindow)
{
    // Check if glfw was initialized
    if(!glfwInit())
    {
        std::cout << BOLDRED << "[Window] GLFW initialization failed!" << RESET << std::endl;
        glfwTerminate();
		exit(1);
    }

    //----- GLFW config -----//
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    //----- Create main window -----//
    GLFWmonitor* monitor = nullptr;

    *mainWindow = glfwCreateWindow(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, "Cylinder", monitor, nullptr);
    glfwSetWindowPos(*mainWindow, mode->width/2-(MAIN_WINDOW_WIDTH)/2, 0);

    if(*mainWindow == nullptr)
    {
        std::cout << BOLDRED << "[Window] Failed to create main window!" << RESET << std::endl;
        glfwTerminate();
        exit(1);
    }

    // Set to draw to this window
    glfwMakeContextCurrent(*mainWindow);

	glfwSetKeyCallback(*mainWindow, keyCallback); // teclado
}
//---------------------------------//
//------------- OPENGL ------------//
//---------------------------------//
void compileShadersAndLink(GLuint program, GLuint vertex, GLuint fragment)
{
	// Define source code to each shader
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

	// Compile vertex shader
    glCompileShader(vertex);

	// Check vertex shader erros
    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        std::cout << BOLDRED << "[Compilation] Failed to compile vertex shader!" << RESET << std::endl;
        std::cout << RED << info << RESET << std::endl;
    }

	// Compile fragment shader
    glCompileShader(fragment);

	// Check fragment shader erros
    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        std::cout << BOLDRED << "[Compilation] Failed to compile fragment shader!" << RESET << std::endl;
        std::cout << RED << info << RESET << std::endl;
    }

	// Attach shader to program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

	// Link program and define as default to be used
    glLinkProgram(program);
    glUseProgram(program);
}

//---------------------------------//
//----------- AUXILIARY -----------//
//---------------------------------//
typedef struct{
    float x, y, z;
} Point;

std::vector<Point> getVertices()
{
	std::vector<Point> vertices;


	// Bottom face
	for(int i=0;i<QTY_FACES;i++)
	{
		vertices.push_back({0,0,0.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*i),sin(2*M_PI/QTY_FACES*i),0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*(i+1)),sin(2*M_PI/QTY_FACES*(i+1)),0});
	}

	// Top face
	for(int i=0;i<QTY_FACES;i++)
	{
		vertices.push_back({0,0,1.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*i),sin(2*M_PI/QTY_FACES*i),1.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*(i+1)),sin(2*M_PI/QTY_FACES*(i+1)),1.0});
	}

	for(int i=0;i<QTY_FACES;i++)
	{
		vertices.push_back({cos(2*M_PI/QTY_FACES*(i+1)),sin(2*M_PI/QTY_FACES*(i+1)),1.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*i),sin(2*M_PI/QTY_FACES*i),1.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*(i+1)),sin(2*M_PI/QTY_FACES*(i+1)),0.0});
		vertices.push_back({cos(2*M_PI/QTY_FACES*i),sin(2*M_PI/QTY_FACES*i),0.0});
	}


	return vertices;
}

std::vector<std::vector<float>> multiplyMatrices(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B)
{
	std::vector<std::vector<float>> result = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                result[i][j] += A[i][k] * B[k][j];

	return result;
}

//---------------------------------//
//-------------- MAIN -------------//
//---------------------------------//
int main(int argc, char** argv)
{
	// Initialize the glfw window and glew
	GLFWwindow *mainWindow;
	initWindow(&mainWindow);
	glewInit();
	//glDepthFunc(GL_LEQUAL);

	// Request slots to the GPU for the fragment and vertex shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	compileShadersAndLink(program, vertex, fragment);

	// Generate object vertices
	std::vector<Point> vertices = getVertices();

	// Create buffer and send vertices to the buffer
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Point), vertices.data(), GL_DYNAMIC_DRAW);

	// Send vertices to shader position attribute
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*) 0);

	// Color location
	GLint locColor = glGetUniformLocation(program, "color");

	// Print help
	printf("---------- HELP ----------\n - WASD to translate\n - XYZ to rotate\n - <ARROW-UP><ARROW-DOWN> to scale\n - <ESQ> Close\n--------------------------\n");

	glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		std::vector<std::vector<float>> scal = {{scale, 0.0f, 0.0f, 0.0f},
												{0.0f, scale, 0.0f, 0.0f},
												{0.0f, 0.0f, scale, 0.0f},
												{0.0f, 0.0f, 0.0f, 1.0f}};

		std::vector<std::vector<float>> tran = {{1.0f, 0.0f, 0.0f, tx},
												{0.0f, 1.0f, 0.0f, ty},
												{0.0f, 0.0f, 1.0f, 0.0f},
												{0.0f, 0.0f, 0.0f, 1.0f}};

		std::vector<std::vector<float>> rotX = {{1.0f, 0.0f, 0.0f, 0.0f},
												{0.0f, cos(angleX), -sin(angleX), 0.0f},
												{0.0f, sin(angleX), cos(angleX), 0.0f},
												{0.0f, 0.0f, 0.0f, 1.0f}};
		
		std::vector<std::vector<float>> rotY = {{cos(angleY), 0.0f, sin(angleY), 0.0f},
												{0.0f, 1.0f, 0.0f, 0.0f},
												{-sin(angleY), 0.0f, cos(angleY), 0.0f},
												{0.0f, 0.0f, 0.0f, 1.0f}};

		std::vector<std::vector<float>> rotZ = {{cos(angleZ), -sin(angleZ), 0.0f, 0.0f},
												{sin(angleZ), cos(angleZ), 0.0f, 0.0f},
												{0.0f, 0.0f, 1.0f, 0.0f},
												{0.0f, 0.0f, 0.0f, 1.0f}};

		std::vector<std::vector<float>> matTransform = multiplyMatrices(rotX, scal);
		matTransform = multiplyMatrices(rotZ, matTransform);
		matTransform = multiplyMatrices(rotY, matTransform);
		matTransform = multiplyMatrices(tran, matTransform);

		// Create model transformation matrix
        float modelMat[16];
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				modelMat[i*4+j]=matTransform[i][j];

        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		// Send transform matrix to GPU
        loc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc, 1, GL_TRUE, modelMat);

		for(int i=0;i<QTY_FACES;i++)
		{
			srand(i);
			float R = (float)rand()/RAND_MAX;
            float G = (float)rand()/RAND_MAX;
            float B = (float)rand()/RAND_MAX;

			glUniform4f(locColor, R,G,B,1);// Red
			glDrawArrays(GL_TRIANGLES, i*3, 3); 
			glDrawArrays(GL_TRIANGLES, QTY_FACES*3+i*3, 3); 
			glDrawArrays(GL_TRIANGLE_STRIP, QTY_FACES*6+i*4, 4); 
		}

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

