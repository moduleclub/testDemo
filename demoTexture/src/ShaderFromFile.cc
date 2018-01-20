

#include"ShaderFromFile.h"
ShaderFromFile::ShaderFromFile(const char* vertexPath_,const char* fragmentPath_)
{
	vertexPath=vertexPath_;
	fragmentPath=fragmentPath_;
}
ShaderFromFile::~ShaderFromFile()
{
}
void ShaderFromFile::setVertexSourcePath(const char* vertexPath_)
{
	vertexPath=vertexPath_;	
}
void ShaderFromFile::setFragmentSourcePath(const char* fragmentPath_)
{
	fragmentPath=fragmentPath_;
}
unsigned int ShaderFromFile::getShaderProgram()const
{
	return shaderProgram;
}
int ShaderFromFile::CompileAndLink()
{
	using namespace std;
	FILE* vertexShaderSourceFile=NULL;	
	FILE* fragmentShaderSourceFile=NULL;
	if(vertexPath==NULL)
	{
		cout<<"#ERROR: vertexPath is NULL,please to set it "<<endl;
		return -1;
	}
	if(fragmentPath==NULL)
	{
		cout<<"#ERROR: fragmentPath is NULL,please to set it "<<endl;
		return -1;
	}
	vertexShaderSourceFile =fopen(vertexPath,"r");
	fragmentShaderSourceFile =fopen(fragmentPath,"r");
	if((vertexShaderSourceFile==NULL))
	{
		cout<<"#ERROR: Failed to Load file (vertexShaderSourceFile) error!";
		return -1;
	}
	if((fragmentShaderSourceFile==NULL))
	{
		cout<<"#ERROR: Failed to Load file (fragmentShaderSourceFile) error!";
		return -1;
	}
	fseek(vertexShaderSourceFile,0,SEEK_END);
	size_t vertexSourceSize = ftell(vertexShaderSourceFile);
	rewind(vertexShaderSourceFile);
	fseek(fragmentShaderSourceFile,0,SEEK_END);
	size_t fragmentSourceSize = ftell(fragmentShaderSourceFile);
	rewind(fragmentShaderSourceFile);
	if(!vertexSourceSize)
	{
		cout<<"#ERROR: vertexSource error"<<endl;
	}
	if(!fragmentSourceSize)
	{
		cout<<"#ERROR: fragmentSource error"<<endl;
	}
	char* vertexSourceBuffer = (char*) malloc(vertexSourceSize);
	if(vertexSourceBuffer==NULL)
	{
		cout<<"#ERROR: malloc vertexSourceBuffer memory error!"<<endl;
		return -1;
	}
	size_t result=fread(vertexSourceBuffer,1,vertexSourceSize,vertexShaderSourceFile);
	if(result != vertexSourceSize)
	{
		cout<<"#ERROR: read vertex Source file error"<<endl;
		return -1;
	}
	fclose(vertexShaderSourceFile);
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexSourceBuffer,NULL);
	glCompileShader(vertexShader);	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"#ERROR: Failed to compile vertexShader :"<<infoLog<<endl;
		return -1;
	}
	free(vertexSourceBuffer);
	
	
	char* fragmentSourceBuffer = (char*) malloc(fragmentSourceSize);
	if(fragmentSourceBuffer==NULL)
	{
		cout<<"#ERROR: malloc fragmentSourceBuffer memory error!"<<endl;
		return -1;
	}
	result=fread(fragmentSourceBuffer,1,fragmentSourceSize,fragmentShaderSourceFile);
	if(result != vertexSourceSize)
	{
		cout<<"#ERROR: read fragment Source file error"<<endl;
		return -1;
	}
	fclose(fragmentShaderSourceFile);	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentSourceBuffer,NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"Failed to compile fragmentShader :"<<infoLog<<endl;	
		return -1;
	}
	free(fragmentSourceBuffer);	
	//link Shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	glGetShaderiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"Failed to Link Shader :"<<infoLog<<endl;	
		return -1;
	}
	//finish use Shader and delete it
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return 0;
}

void ShaderFromFile::useProgram()const
{
	glUseProgram(shaderProgram);
}
