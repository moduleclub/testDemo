#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<string>

using namespace std;
struct A{
	int x;
	int y;
};
struct B{
	A a;
	char* b;
};
class mydata{
public:
	mydata(){}
	void set(int* x,float* y)
	{
		for(int i=0;i<4;i++)
		{
			a[i]=*(x+i);
			b[i]=*(y+i);
		}
	}
	void show()
	{
		cout<<"a ="<<a[0]<<","<<a[1]<<","<<a[2]<<endl;
		cout<<"b ="<<b[0]<<","<<b[1]<<","<<b[2]<<endl;
	}
private:
	int a[4];
	float b[4];
};
int main()
{

	vector<string> s;
	vector<mydata> d;
	B bd;
	A& ma=bd.a;
	ma.x=10;
	cout<<"ma.x="<<bd.a.x<<endl;
	char buf[10];
	const int value=100;
	const int myvalue=100;
	int x[4]={1,2,3,6};
	float y[4]={4.1,4.67,67.45,80.56};
	
	
	clock_t timestart=clock();	
	for(int i=0;i<value;i++){
			mydata data;
			data.set(x,y);
			d.push_back(data);		
	}
	cout<<"alloc vector mydata mem time: "<<(clock()-timestart) <<"milli-seconds"<<endl;
	cout<<"vector mydata size:"<<d.size()<<endl;
	cout<<"vector mydata capacity:"<<d.capacity()<<endl;
	cout<<"vector mydata self size: "<<sizeof(d)<<endl;
	cout<<"mydata self size: "<<sizeof(d[9])<<endl;	
	
	timestart=clock();	
	for(int i=0;i<value;i++){
		try{
			srand((unsigned int)time(NULL));
			snprintf(buf,10,"%d",rand());
			s.push_back(string(buf));
		}
		catch(exception& p){
			cout<<"i="<<" "<< p.what()<<endl;
			abort();
		}
	}
	cout<<"alloc vector string mem time: "<<(clock()-timestart)<<"milli-seconds"<<endl;
	cout<<"vector string size:"<<s.size()<<endl;
	cout<<"vector string capacity"<<s.capacity()<<endl;
	cout<<"vector string self size: "<<sizeof(s)<<endl;
	//-----------------------------------------------------------
	vector<int> pra;
	cout<<"-------starttime--vector int size:"<<pra.capacity()<<endl;
	timestart = clock();
	int start_capacity=0;
	for(int i=0;i<myvalue;i++){
		try{
			srand((unsigned int)time(NULL));
			pra.push_back(rand());			
		}
		catch(exception& e){
			cout<<"error : "<<e.what()<<endl;
			abort();
		}
		if(start_capacity != pra.capacity()){
				start_capacity=pra.capacity();
				cout<<"change vector int capacity:"<< start_capacity <<endl;
			}
	}
	cout<<"alloc vector int mem time: " <<(clock()-timestart)<<"milli-seconds"<<endl;
	cout<<"vector int size: "<<pra.size()<<endl;
	cout<<"vector int capacity: "<<pra.capacity()<<endl;//
	cout<<"vector int self size: "<<sizeof(pra)<<endl;//size-->24
	
	return 0;	
}


/*
alloc vector string mem time: 677milli-seconds
vector string size:100
vector string capacity128
vector string self size: 24
-------starttime--vector int size:0
change vector int capacity:1
change vector int capacity:2
change vector int capacity:4
change vector int capacity:8
change vector int capacity:16
change vector int capacity:32
change vector int capacity:64
change vector int capacity:128
change vector int capacity:256
change vector int capacity:512
change vector int capacity:1024
change vector int capacity:2048
change vector int capacity:4096
change vector int capacity:8192
change vector int capacity:16384
change vector int capacity:32768
change vector int capacity:65536
change vector int capacity:131072
change vector int capacity:262144
change vector int capacity:524288
change vector int capacity:1048576
change vector int capacity:2097152
change vector int capacity:4194304
change vector int capacity:8388608
change vector int capacity:16777216
change vector int capacity:33554432
change vector int capacity:67108864
change vector int capacity:134217728

*/
