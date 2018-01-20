#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include"ShaderFromFile.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH =800;
const unsigned int SCR_HEIGHT =600;


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
	
	ShaderFromFile myshader("vertex.gl","fragment.gl");
	myshader.CompileAndLink();
		
	//set up vertex data
	float vertices[]={
		//positions          //colors          //texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f   1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f   0.0f, 1.0f
	};
	unsigned int indices[]={
		0,1,3,
		1,2,3
	};
	unsigned int VAO, VBO, EBO TEXTURE;
	//set VAO
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	//set VBO
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//set EBO
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	//set texture
	glGenTextures(1,&TEXTURE);
	glBindTexture(GL_TEXTURE_2D,TEXTURE);
	//set texture wrap parameter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//set texture filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//position attribute
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coord texture
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	//set texture
	int width,height,nrChannels;
	unsigned char* imgdata = stbi_load("mypicture.jpg",&width,height,&nrChannels,0);
	if(imgdata)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,imgdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout<<"Failed to load texture"<<endl;
	}
	stbi_image_free(data);
	
	//disable bind(unbind)
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	while(!glfwWindowShouldClose(demoWindow))
	{
		processInput(demoWindow);
		glClearColor(0.0f,0.0f,0.0f,1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindTexture(GL_TEXTURE_2D,TEXTURE);
		
		myshader.useProgram();
		
		
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES,0,3);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		
		glfwSwapBuffers(demoWindow);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	
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
