#pragma once
class velocityToLength {
private:
public:
	velocityToLength();
	velocityToLength::velocityToLength(const velocityToLength &other) = delete;
	velocityToLength::velocityToLength(const velocityToLength &&other) = delete;	
	velocityToLength& operator=(const velocityToLength& other) = delete;
	velocityToLength&& operator=(const velocityToLength&& other) = delete;
	~velocityToLength() noexcept;

	int VLStepConversion(const int& m_velocity);
};

