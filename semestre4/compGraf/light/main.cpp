//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-11-27                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
//------------- STRUCTS -----------//
//---------------------------------//
typedef struct{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
} Vertex;

// Model variables
struct ModelInfo
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	unsigned int indicesSize;
};

struct ObjectInfo
{
	unsigned int modelId;
	unsigned int texId;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

//---------------------------------//
//-------- GLOBAL VARIABLES -------//
//---------------------------------//
double currTime = 0;

// Camera variables
glm::vec3 cameraPos= {-14.718590, 12.241324, -41.411156};
glm::vec3 cameraUp = {0,1,0};
glm::vec3 cameraFront = {0.509715, -0.143492, 0.848293};
glm::vec3 cameraMovement = {0,0,0};
int movingForward;
int movingUp;
int movingLeft;
float cameraSpeed = 200;

// Kart variables
float kartAngle = 0;
float wheelAngle = 0;
float maxWheelAngle = 30;
bool wheelIncrease = true;

// Mouse handling
bool firstMouse = true;
float yaw = 782;
float pitch = -5;
float lastX, lastY;

std::vector<ModelInfo> modelInfos;
std::vector<ObjectInfo> objects;
std::vector<GLuint> textures;

//---------------------------------//
//------------ SHADERS ------------//
//---------------------------------//
// GLSL para Vertex Shader
const char* vertex_code =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 inNormal;\n"
	"layout (location = 2) in vec2 inTexCoords;\n"
	"\n"
	"out vec2 texCoords;\n"
	"out vec3 normal;\n"
	"out vec3 fragPos;\n"
	"\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	texCoords = inTexCoords;\n"
	"	normal = inNormal;\n"
	"	fragPos = position;\n"
	"\n"
	"	gl_Position = projection*view*model*vec4(position, 1.0);\n"
	"}\n";

// GLSL para Fragment Shader
const char* fragment_code =
	"#version 330 core\n"
	"in vec2 texCoords;\n"
	"in vec3 normal;\n"
	"in vec3 fragPos;\n"
	"uniform sampler2D texture0;\n"
	"\n"
    "// parametros da iluminacao ambiente e difusa\n"
    "vec3 lightPos = vec3(0,10,0); // define coordenadas de posicao da luz\n"
    "float ka = 0.3f; // coeficiente de reflexao ambiente\n"
    "float kd = 1.0f; // coeficiente de reflexao difusa\n"
    "// parametros da iluminacao especular\n"
    "uniform vec3 viewPos; // define coordenadas com a posicao da camera/observador\n"
    "float ks = 1; // coeficiente de reflexao especular\n"
    "float ns = 1; // expoente de reflexao especular\n"
	"\n"
    "// parametro com a cor da(s) fonte(s) de iluminacao\n"
    "vec3 lightColor = vec3(1.0, 1.0, 0.7);\n"
	"\n"
	"void main()\n"
	"{\n"
    "\n"
    "	// Calculando reflexao ambiente\n"
    "	vec3 ambient = ka * lightColor;\n"
    "\n"
    "	// Calculando reflexao difusa\n"
    "	vec3 norm = normalize(normal); // normaliza vetores perpendiculares\n"
    "	vec3 lightDir = normalize(lightPos - fragPos); // direcao da luz\n"
    "	float diff = max(dot(norm, lightDir), 0.0); // verifica limite angular (entre 0 e 90)\n"
    "	vec3 diffuse = kd * diff * lightColor; // iluminacao difusa\n"
	"\n"
    "	// calculando reflexao especular\n"
    "	vec3 viewDir = normalize(viewPos - fragPos); // direcao do observador/camera\n"
    "	vec3 reflectDir = reflect(-lightDir, norm); // direcao da reflexao\n"
    "	float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
    "	vec3 specular = ks * spec * lightColor;\n"
    "\n"
	"	 vec4 tex = texture(texture0, texCoords);"
	"	 gl_FragColor = vec4((ambient+diffuse+specular),1)*tex;"
	"}\n";

//---------------------------------//
//-------------- GLFW -------------//
//---------------------------------//

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch(key)
	{
		case GLFW_KEY_W:
			if(action == GLFW_RELEASE)
				movingForward = 0;
			else
				movingForward = 1;
			break;
		case GLFW_KEY_A:
			if(action == GLFW_RELEASE)
				movingLeft = 0;
			else
				movingLeft = -1;
			break;
		case GLFW_KEY_S:
			if(action == GLFW_RELEASE)
				movingForward = 0;
			else
				movingForward = -1;
			break;
		case GLFW_KEY_D:
			if(action == GLFW_RELEASE)
				movingLeft = 0;
			else
				movingLeft = 1;
			break;
		case GLFW_KEY_E:
			if(action == GLFW_RELEASE)
				movingUp = 0;
			else
				movingUp = 1;
			break;
		case GLFW_KEY_Q:
			if(action == GLFW_RELEASE)
				movingUp = 0;
			else
				movingUp = -1;
			break;
		case GLFW_KEY_SPACE:
			std::cout << "Camera info: " << std::endl;;
			std::cout << "\t- Position: " << glm::to_string(cameraPos) << std::endl;
			std::cout << "\t- Front: " << glm::to_string(cameraFront) << std::endl;
			std::cout << "\t- Up: " << glm::to_string(cameraUp) << std::endl;
			std::cout << "\t- Yaw: " << yaw << std::endl;
			std::cout << "\t- Pitch: " << pitch << std::endl;
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
	}

	float xoffset = xpos-lastX;
	float yoffset = lastY-ypos;

	float sensitivity = 600;
	xoffset*=sensitivity;
	yoffset*=sensitivity;

	yaw+=xoffset;
	pitch+=yoffset;

	if(pitch>=90)pitch=90;
	if(pitch<=-90)pitch=-90;

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
//-------------- MESH -------------//
//---------------------------------//

std::vector<std::string> splitLine(const std::string s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
    std::string item;

    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;	
}

void loadModel(std::string fileName)
{
	std::ifstream file(("assets/models/"+fileName).c_str());
	if(file.is_open())
	{
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<Vertex> finalVertices;

		std::string line;
		while(getline(file, line))
		{
			std::vector<std::string> splitted = splitLine(line, ' ');
			std::string code = splitted[0];
			if(code=="#")
				continue;
			else if(code=="v")
			{
				glm::vec3 v;
				v.x = std::stof(splitted[1]);
				v.y = std::stof(splitted[2]);
				v.z = std::stof(splitted[3]);
				vertices.push_back(v);
			}
			else if(code=="vt")
			{
				glm::vec2 v;
				v.x = std::stod(splitted[1]);
				v.y = 1-std::stod(splitted[2]);
				texCoords.push_back(v);
			}
			else if(code=="vn")
			{
				glm::vec3 v;
				v.x = std::stof(splitted[1]);
				v.y = std::stof(splitted[2]);
				v.z = std::stof(splitted[3]);
				normals.push_back(v);
			}
			else if(code=="f")
			{
				// Face with 3 vertices
				if((int)splitted.size()==4)
				{
					for(int i=1;i<4;i++)
					{
						std::vector<std::string> values = splitLine(splitted[i],'/');
						int vert = std::stoi(values[0])-1;
						int tex = std::stoi(values[1])-1;
						int normal = std::stoi(values[2])-1;

						Vertex v;
						v.position = vertices[vert];
						v.texCoords = texCoords[tex];
						v.normal = normals[normal];
						finalVertices.push_back(v);
						indices.push_back(indices.size());
					}
				}
			}
			else if(code=="usemtl" || code=="usemat")
			{

			}
		}
		std::cout << "[Mesh] " << fileName << " loaded successfully: " 
				+ std::to_string((int)finalVertices.size()) + " vertices, "
				+ std::to_string((int)indices.size()) + " indices.\n";

		file.close();

		ModelInfo modelInfo;
		modelInfo.indicesSize = indices.size();
		// Generate buffers
		glGenVertexArrays(1, &modelInfo.VAO);// Vertex array object
		glGenBuffers(1, &modelInfo.VBO);// Vertex buffer object
		glGenBuffers(1, &modelInfo.EBO);// Element buffer object
	  
		// Operations on VAO
		glBindVertexArray(modelInfo.VAO);

		// Add vertices to VBO
		glBindBuffer(GL_ARRAY_BUFFER, modelInfo.VBO);
		glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(Vertex), &finalVertices[0], GL_STATIC_DRAW);  

		// Add indices to EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelInfo.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// Vertex positions
		glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// Vertex normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		// Vertex texture coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		// Unbind VAO
		//glBindVertexArray(0);

		modelInfos.push_back(modelInfo);
	}
	else
	{
		std::cout << "[Mesh] " << " Failed to open file!" << std::endl;
	}
}

//---------------------------------//
//------------ TEXTURE ------------//
//---------------------------------//
void loadTexture(std::string fileName)
{
	int width, height, channels;
	// Bind texture
	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId); 
	textures.push_back(texId);

	// Load image
	unsigned char *data = stbi_load(("assets/textures/"+fileName).c_str(), &width, &height, &channels, 0); 
	if(data)
	{
		std::cout << "[Texture] " << fileName << " loaded successfully: " 
				+ std::to_string(width) + "px X "
				+ std::to_string(height) + "px X "
				+ std::to_string(channels) + ".\n";

		// Set the texture wrapping/filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Generate texture
		if(channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if(channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
		{
			std::cout << "[Texture] Strange number of channels!\n";
			exit(1);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[Texture] Failed to load " + fileName << std::endl;
	}

	stbi_image_free(data);
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

	//-------- Load models and create objects --------//
	loadModel("2cats.obj");
	loadTexture("garage.png");
	objects.push_back({0, 0, {20,0,0}, {0,0,0}, {.1,.1,.1}});
	loadModel("kart-extern.obj");
	loadTexture("kart-extern0.png");
	objects.push_back({1, 1, {0,3,0}, {0,0,180}, {.1,.1,.1}});
	loadModel("kart-intern.obj");
	loadTexture("kart-intern0.png");
	objects.push_back({2, 2, {0,3,0}, {0,0,180}, {.1,.1,.1}});
	loadModel("kart-wheel.obj");
	loadTexture("kart-wheel0.png");
	loadTexture("kart-wheel1.png");
	loadTexture("kart-wheel2.png");
	loadTexture("kart-wheel3.png");
	objects.push_back({3, 3, {3.3,3.9,4}, {0,0,0}, {.1,.1,.1}});
	objects.push_back({3, 4, {-3.3,3.9,4}, {0,0,0}, {.1,.1,.1}});
	objects.push_back({3, 5, {3.3,3.9,-5}, {0,0,0}, {.1,.1,.1}});
	objects.push_back({3, 6, {-3.3,3.9,-5}, {0,0,0}, {.1,.1,.1}});

	// Print help
	printf("---------- HELP ----------\n - WASDEQ to change position\n - mouse to rotate the camera\n - <ESQ> Close\n--------------------------\n");

	glEnable(GL_DEPTH_TEST);// Enable depth test
    while(!glfwWindowShouldClose(mainWindow))
    {
		double lastTime = currTime;
		if(lastTime==0)
			lastTime = glfwGetTime();
		currTime = glfwGetTime();
		float dt = currTime-lastTime;

		//---------- Update camera position ----------//
		cameraPos += cameraFront*cameraSpeed * float(movingForward*dt);
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed * float(movingLeft*dt);
		cameraPos += cameraUp*cameraSpeed * float(movingUp*dt);

		//---------- Update kart position ----------//
		kartAngle += 30*dt;
		if(kartAngle >= 360) kartAngle-=360;
		// Extern/Intern
		objects[1].rotation.y = kartAngle;
		objects[2].rotation.y = kartAngle;

		// Wheels
		objects[3].position.x = cos(glm::radians(-kartAngle)+0.88)*5.18;
		objects[4].position.x = cos(glm::radians(-kartAngle)-0.98)*5.99;
		objects[5].position.x = cos(glm::radians(-kartAngle)+0.98+M_PI)*5.99;
		objects[6].position.x = cos(glm::radians(-kartAngle)-0.88+M_PI)*5.18;

		objects[3].position.z = sin(glm::radians(-kartAngle)+0.88)*5.18;
		objects[4].position.z = sin(glm::radians(-kartAngle)-0.98)*5.99;
		objects[5].position.z = sin(glm::radians(-kartAngle)+0.98+M_PI)*5.99;
		objects[6].position.z = sin(glm::radians(-kartAngle)-0.88+M_PI)*5.18;

		wheelAngle += wheelIncrease?60*dt:-60*dt;
		if(wheelAngle>=maxWheelAngle)
		{
			wheelAngle = maxWheelAngle;
			wheelIncrease = false;
		}
		if(wheelAngle<=-maxWheelAngle)
		{
			wheelAngle = -maxWheelAngle;
			wheelIncrease = true;
		}

		objects[3].rotation.y = kartAngle+wheelAngle+180;
		objects[4].rotation.y = kartAngle+180;
		objects[5].rotation.y = kartAngle;
		objects[6].rotation.y = kartAngle+wheelAngle;


		//---------- Draw objects ----------//
        glfwPollEvents();

        glClearColor(0.8,0.8,0.8,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		// View matrix
		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
       	GLint loc = glGetUniformLocation(program, "view");
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

		// View pos
        loc = glGetUniformLocation(program, "viewPos");
        glUniform3f(loc, cameraPos.x, cameraPos.y, cameraPos.z);

		// Model matrix
        loc = glGetUniformLocation(program, "model");

		//---------- Draw objects ----------//
		for(auto object : objects)
		{
			// Send model matrix
			glm::mat4 mat = glm::mat4(1.0f);
			mat = glm::translate(mat, object.position);
			mat = glm::rotate(mat, glm::radians(object.rotation.x), glm::vec3(0, 0, 1));
			mat = glm::rotate(mat, glm::radians(object.rotation.y), glm::vec3(0, 1, 0));
			mat = glm::rotate(mat, glm::radians(object.rotation.z), glm::vec3(1, 0, 0));
			mat = glm::scale(mat, object.scale);
			mat = glm::transpose(mat);
        	glUniformMatrix4fv(loc, 1, GL_TRUE, glm::value_ptr(mat));
			
			// Bind texture
			glActiveTexture(GL_TEXTURE0);// Activate first texture unit
			glBindTexture(GL_TEXTURE_2D, textures[object.texId]);

			// Draw mesh
			glBindVertexArray(modelInfos[object.modelId].VAO);
			glDrawElements(GL_TRIANGLES, modelInfos[object.modelId].indicesSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

