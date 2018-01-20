#include<iostream>

template<typename T> 
class sixteenTree{
public:
	sixteenTree();
	~sixteenTree();
	create();
	addNode();
	virtual deleteNode();
	SearchNode();
private:
	sixteenTree* NodePtr[16];
	T data;
};
