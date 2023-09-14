#pragma once
#include "PrecompiledHeadersEdges.h"

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

