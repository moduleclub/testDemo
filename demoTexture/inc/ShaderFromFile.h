#ifndef SHADER_H_
#define SHADER_H_
#include"glad/glad.h"
#include<iostream>
#include<fstream>
#include<cstdlib>


class ShaderFromFile
{
public:
	ShaderFromFile(const char* vertexPath_, const char* fragmentPath_);
	~ShaderFromFile();
	void setVertexSourcePath(const char* vertexPath_);
	void setFragmentSourcePath(const char* fragmentPath_);
	unsigned int getShaderProgram()const;
	int CompileAndLink();
	void useProgram()const;

private:
	const char* vertexPath=NULL;
	const char* fragmentPath=NULL;
	unsigned int shaderProgram;

};







#endif
