// g++ main.cpp -lglfw -lGL -lGLEW -o a && ./a

//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-11-11                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
glm::vec3 cameraPos= {0,0,3};
glm::vec3 cameraUp = {0,1,0};
glm::vec3 cameraFront = {0,0,-1};
float cameraSpeed = 0.2;
// Mouse handling
bool firstMouse = true;
float yaw, pitch, lastX, lastY;

//---------------------------------//
//------------ SHADERS ------------//
//---------------------------------//
// GLSL para Vertex Shader
const char* vertex_code =
	"attribute vec3 position;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = projection*view*model*vec4(position, 1.0);\n"
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

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch(key)
	{
		case GLFW_KEY_W:
			cameraPos += cameraFront*cameraSpeed;
			break;
		case GLFW_KEY_A:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case GLFW_KEY_S:
			cameraPos -= cameraFront*cameraSpeed;
			break;
		case GLFW_KEY_D:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case GLFW_KEY_E:
			cameraPos += cameraUp*cameraSpeed;
			break;
		case GLFW_KEY_Q:
			cameraPos -= cameraUp*cameraSpeed;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
	}
}

static void mouseCallback(GLFWwindow* window, double xpos, double ypos){
	xpos/=MAIN_WINDOW_WIDTH;
	ypos/=MAIN_WINDOW_HEIGHT;
	if(firstMouse)
	{
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
		yaw = -90;
		pitch = 0;
	}

	float xoffset = xpos-lastX;
	float yoffset = lastY-ypos;

	float sensitivity = 600;
	xoffset*=sensitivity;
	yoffset*=sensitivity;

	yaw+=xoffset;
	pitch+=yoffset;

	//if(pitch>=90)pitch=90;
	//if(pitch<=-90)pitch=-90;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

	lastX = xpos;
	lastY = ypos;
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

    *mainWindow = glfwCreateWindow(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, "Mesh", monitor, nullptr);
    glfwSetWindowPos(*mainWindow, mode->width/2-(MAIN_WINDOW_WIDTH)/2, 0);

    if(*mainWindow == nullptr)
    {
        std::cout << BOLDRED << "[Window] Failed to create main window!" << RESET << std::endl;
        glfwTerminate();
        exit(1);
    }

    // Set to draw to this window
    glfwMakeContextCurrent(*mainWindow);

	glfwSetKeyCallback(*mainWindow, keyCallback); // keyboard
	glfwSetCursorPosCallback(*mainWindow, mouseCallback); // mouse
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

typedef struct{
    int i0, i1, i2;
} Indice;

std::vector<Point> getVertices(std::string fileName)
{
	std::vector<Point> vertices;
	std::vector<Indice> indices;
	std::vector<Point> texCoords;
	std::vector<Point> normals;
	std::vector<Point> result;// All vertices without indices

	std::ifstream file(fileName.c_str());
	if(file.is_open())
	{
		std::string line;
		while(getline(file, line))
		{
			std::string code = line.substr(0, line.find(' '));
			if(code=="#")
				continue;
			else if(code=="v")
			{
				int firstSpace = line.find(' ');
				int secondSpace = line.find(' ', firstSpace+1);
				int thirdSpace = line.find(' ', secondSpace+1);
				float val1 = std::stof(line.substr(firstSpace, secondSpace));
				float val2 = std::stof(line.substr(secondSpace, thirdSpace));
				float val3 = std::stof(line.substr(thirdSpace, line.size()));
				//std::cout << "vertex " << val1 << " " <<val2 << " " << val3 << std::endl;
				vertices.push_back({val1, val2, val3});
			}
			else if(code=="vt")
			{
				int firstSpace = line.find(' ');
				int secondSpace = line.find(' ', firstSpace+1);
				float val1 = std::stof(line.substr(firstSpace, secondSpace));
				float val2 = std::stof(line.substr(secondSpace, line.size()));
				//std::cout << "tex " << val1 << " " <<val2 << std::endl;
				texCoords.push_back({val1, val2, 0});
			}
			else if(code=="vn")
			{
				int firstSpace = line.find(' ');
				int secondSpace = line.find(' ', firstSpace+1);
				int thirdSpace = line.find(' ', secondSpace+1);
				float val1 = std::stof(line.substr(firstSpace, secondSpace));
				float val2 = std::stof(line.substr(secondSpace, thirdSpace));
				float val3 = std::stof(line.substr(thirdSpace, line.size()));
				//std::cout << "normal" << val1 << " " <<val2 << " " << val3 << std::endl;
				normals.push_back({val1, val2, val3});
			}
			else if(code=="f")
			{
				int firstSpace = line.find(' ');
				int secondSpace = line.find(' ', firstSpace+1);
				int thirdSpace = line.find(' ', secondSpace+1);
				int index1 = std::stoi(line.substr(firstSpace, line.find('/',firstSpace)));
				int index2 = std::stoi(line.substr(secondSpace, line.find('/',secondSpace)));
				int index3 = std::stoi(line.substr(thirdSpace, line.find('/',thirdSpace)));

				// Deal with 3/4 vertices per face
				if(line.find(' ', thirdSpace+1)<line.size()-4)
				{
					int fourthSpace = line.find(' ', thirdSpace+1);
					int index4 = std::stoi(line.substr(fourthSpace, line.find('/',fourthSpace)));
					indices.push_back({index1, index2, index3});
					indices.push_back({index2, index3, index4});
				}
				else
				{
					indices.push_back({index1, index2, index3});
				}
			}
			else if(code=="usemtl" || code=="usemat")
			{

			}
		}

	}
	file.close();
	for(auto face : indices)
	{
		result.push_back(vertices[face.i0-1]);
		result.push_back(vertices[face.i1-1]);
		result.push_back(vertices[face.i2-1]);
	}

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

	// Request slots to the GPU for the fragment and vertex shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	compileShadersAndLink(program, vertex, fragment);

	//-------- Load models --------//
	// Load flower
	std::vector<Point> vertices = getVertices("flower.obj");
	std::vector<int> modelOffsetVertices = {0};
	modelOffsetVertices.push_back(vertices.size());

	// Load cats
	std::vector<Point> temp = getVertices("cats.obj");
	vertices.insert(vertices.end(), temp.begin(), temp.end());
	modelOffsetVertices.push_back(vertices.size());

	// Load chair
	temp = getVertices("chair.obj");
	vertices.insert(vertices.end(), temp.begin(), temp.end());
	modelOffsetVertices.push_back(vertices.size());

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
	printf("---------- HELP ----------\n - WASDEQ to change position\n - mouse to rotate the camera\n - <ESQ> Close\n--------------------------\n");

	glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        glClearColor(0.8,0.8,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		// View matrix
		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        loc = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, &viewMat[0][0]);

		// Projection matrix
		glm::mat4 projMat = glm::perspective(
			glm::radians(60.0f),
			(float)MAIN_WINDOW_WIDTH / (float)MAIN_WINDOW_HEIGHT,
			0.1f,
			1000.0f
		);

        loc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, &projMat[0][0]);

		// Model matrix
        loc = glGetUniformLocation(program, "model");

		//---------- Draw flower ----------//
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, glm::vec3(0, 0, 0.0f));
		mat = glm::scale(mat, glm::vec3(0.1, 0.1, 0.1));
        glUniformMatrix4fv(loc, 1, GL_TRUE, &mat[0][0]);
		mat = glm::transpose(mat);

		glUniform4f(locColor, 1.0,0,0,1);
		glDrawArrays(GL_TRIANGLES, modelOffsetVertices[0], modelOffsetVertices[1]-modelOffsetVertices[0]); 
		
		//---------- Draw cat ----------//
		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(180.f), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(2.0f, 0.0f, 0.0f));
		mat = glm::scale(mat, glm::vec3(0.01, 0.01, 0.01));
		mat = glm::transpose(mat);
        glUniformMatrix4fv(loc, 1, GL_TRUE, &mat[0][0]);

		glUniform4f(locColor, 0.0,0.0,1.0,1);
		glDrawArrays(GL_TRIANGLES, modelOffsetVertices[1], modelOffsetVertices[2]-modelOffsetVertices[1]); 

		//---------- Draw chair ----------//
		mat = glm::mat4(1.0f);
		mat = glm::rotate(mat, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::translate(mat, glm::vec3(-6.0f, 0.0f, 0.0f));
		mat = glm::scale(mat, glm::vec3(0.03, 0.03, 0.03));
		mat = glm::transpose(mat);
        glUniformMatrix4fv(loc, 1, GL_TRUE, &mat[0][0]);

		glUniform4f(locColor, 0.0,1.0,0.0,1);
		glDrawArrays(GL_TRIANGLES, modelOffsetVertices[2], modelOffsetVertices[3]-modelOffsetVertices[2]); 
		
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

