#pragma once
#include "PrecompiledHeadersEdges.h"
//#include <fstream>
//static int hilfeVar = 0;

class randomSpeed_neu {
public:
	
	int a=100;
	randomSpeed_neu();
	randomSpeed_neu::randomSpeed_neu(const randomSpeed_neu& other) = delete;
	randomSpeed_neu& operator= (const randomSpeed_neu& other) = delete;
	randomSpeed_neu::randomSpeed_neu(const randomSpeed_neu&& other) = delete;
	randomSpeed_neu&& operator= (const randomSpeed_neu&& other) = delete;
	~randomSpeed_neu() noexcept;
	
	void randomNumberRequest();
	
	
private:
	std::queue<int>q1;
	static std::queue<int>q2;
	std::future<void> f1;
	static bool serviceBool;
	
	void randomSpeed_neu::random();
	static void randomSpeed_neu::randomNumberGenerator();

};
/*
class printFunc {
public:
	std::ofstream file;
	std::string name= "C:/Users/bernh/Desktop/donne/randontestXXX" + std::to_string(hilfeVar) + ".txt";
	printFunc() {
		hilfeVar++;
	
		file.open(name);
	}
	~printFunc() {
		file.close();
	}
	void printFuncA(int param) {
		file << "\n" << param;
	}
	void printFuncB(int param) {
		file << "\t" << param;
	}
};

*/
