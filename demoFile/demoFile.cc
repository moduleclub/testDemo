#include<cstdio>
#include<cstring>
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
	FILE* fileUC=NULL;
	filebuf* myfilebuf;
	size_t fileSize;
	char* filebuf=NULL;
	size_t result;
	clock_t timeStart =clock();
	fileUC = fopen("cmm.avi","r");
	if(fileUC==NULL)
	{
		cout<<"c program ----- failed to use fopen function to open a file "<<endl;
		return -1;
	}
	fseek(fileUC,0,SEEK_END);
	fileSize = ftell(fileUC);
	rewind(fileUC);	
	filebuf = (char*)malloc(fileSize);
	if(filebuf==NULL)
	{
		cout<<"c program -----malloc memory error"<<endl;
		return -1;
	}
	result = fread(filebuf,1,fileSize,fileUC);
	if(result != fileSize)
	{
		cout<<"c program ---Memory error"<<endl;
		return -1;
	}	
	cout<<"c program -----file size :"<<(fileSize)<<endl;
	cout<<"c program -----read file time : "<<(clock()-timeStart)<<endl;//377356
	fclose(fileUC);
	free(filebuf);
	if(filebuf==NULL)
	{
		cout<<"test filebuf free....."<<endl;
	}
//-------------------------------------------------------------------------	
	timeStart = clock();
	ifstream fileS;
	fileS.open("hmm.avi");
	myfilebuf = fileS.rdbuf();
	fileSize = myfilebuf->pubseekoff(0,fileS.end,fileS.in);
	myfilebuf->pubseekpos(0,fileS.in);
	
	filebuf =new char[fileSize];
	myfilebuf->sgetn(filebuf,fileSize);
	
	cout<<"c++ program -----file size :"<<(fileSize)<<endl;
	cout<<"c++ program -----read file time : "<<(clock()-timeStart)<<endl;//569633
	fileS.close();
	delete[] filebuf;
	if(filebuf==NULL)
	{
		cout<<"test filebuf free....."<<endl;
	}
	
	return 0;
}
