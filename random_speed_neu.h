#pragma once
#include "PrecompiledHeadersEdges.h"

class randomSpeed_neu {
public:
	int a=100;
	randomSpeed_neu::randomSpeed_neu() {
		q1.push(70);
		q1.push(80);
		q1.push(90);
		random();
	}
	randomSpeed_neu::~randomSpeed_neu() {
		
	}
	
	void randomNumberRequest();
	
private:
	std::queue<int>q1;
	static std::queue<int>q2;
	std::future<void> f1;
	static bool serviceBool;

	
	randomSpeed_neu::randomSpeed_neu(randomSpeed_neu& other) = delete;
	randomSpeed_neu& operator= (const randomSpeed_neu& other) = delete;
	randomSpeed_neu::randomSpeed_neu(randomSpeed_neu&& other) = delete;
	randomSpeed_neu&& operator= (const randomSpeed_neu&& other) = delete;	
	//static void randomNumberGenerator();

	void randomSpeed_neu::random();
	static void randomSpeed_neu::randomNumberGenerator();


	
	



};


