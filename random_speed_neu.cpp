//#pragma once
#include "PrecompiledHeadersEdges.h"
#include "random_speed_neu.h"

randomSpeed_neu::randomSpeed_neu() {
	q1.push(70);
	q1.push(80);
	q1.push(90);
	random();
}

randomSpeed_neu::~randomSpeed_neu() noexcept {}

void randomSpeed_neu::randomNumberRequest() {
	if (q1.empty()) {
		if (serviceBool == false) {
			if (!q2.empty()) {
				q1 = std::move(q2);
				std::queue<int> q3;
				if (q3.empty()) {
					q2 = std::move(q3);
				}
			}
			randomSpeed_neu::random();
		}
		a = 100;
	}
	else {
		a = q1.front();
		q1.pop();
	}
}

static std::mutex randomClacMutex;

std::queue<int> randomSpeed_neu::q2;

bool randomSpeed_neu::serviceBool = false;

void randomSpeed_neu::randomNumberGenerator() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> intDist(30, 130);
	std::lock_guard<std::mutex> lock(randomClacMutex);
	int bii = 0;
	int cii = 0;
	serviceBool = true;
	while (q2.size() < 80) {
		serviceBool = true;
		bii = intDist(mt);
		if (bii != cii) {
			if (bii == 0) {
				bii = 80;
			}
			q2.push(bii);
		}
		cii = bii;
	}
	serviceBool = false;
}

void randomSpeed_neu::random() {
	f1 = std::async(std::launch::async, randomNumberGenerator);

}