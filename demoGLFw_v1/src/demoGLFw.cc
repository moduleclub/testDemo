#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH =800;
const unsigned int SCR_HEIGHT =600;

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location=0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos,1.0f);\n"
	"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(0.2f,0.5f, 0.2f, 1.0);"
	"}\n\0";

int main(){
	//initialize glfw 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create glfw window
	GLFWwindow* demoWindow = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"demoGL",NULL,NULL);
	if(demoWindow == NULL)
	{
		cout<<"Failed to create GLFW window "<<endl;
		glfwTerminate();
		return -1;
	}
	//set current window context demoWindow
	glfwMakeContextCurrent(demoWindow);
	glfwSetFramebufferSizeCallback(demoWindow,framebuffer_size_callback);
	
	//glad load all GL function pointers (initialize Gpu HW)
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout<<"Failed to initialize GLAD"<<endl;
		glfwTerminate();
		return -1;
	}
	// build and compile opengl shading language specification
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"Failed to compile vertexShader :"<<infoLog<<endl;	
	}	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"Failed to compile fragmentShader :"<<infoLog<<endl;	
	}	
	//link Shader
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	glGetShaderiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"Failed to Link Shader :"<<infoLog<<endl;	
	}
	//finish use Shader and delete it
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	//set up vertex data
	float vertices[]={
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	unsigned int VAO,VBO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//disable bind(unbind)
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	while(!glfwWindowShouldClose(demoWindow))
	{
		processInput(demoWindow);
		glClearColor(0.0f,0.0f,0.0f,1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		
		glfwSwapBuffers(demoWindow);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	
	glfwTerminate();
	return 0;
	
		
}


void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}




