#include "PrecompiledHeadersEdges.h"
#include "velocityToLength.h"

velocityToLength::velocityToLength() {};

velocityToLength::~velocityToLength() noexcept {};

int velocityToLength::VLStepConversion(const int& m_velocity) {
	if (m_velocity > 129)
		return 36;
	if ((m_velocity<130) && (m_velocity > 119))
		return 33;
	if ((m_velocity<120) && (m_velocity > 109))
		return 31;
	if ((m_velocity<110) && (m_velocity > 99))
		return 28;
	if ((m_velocity<100) && (m_velocity > 89))
		return 25;
	if ((m_velocity<90) && (m_velocity > 79))
		return 22;
	if ((m_velocity<80) && (m_velocity > 69))
		return 19;
	if ((m_velocity<70) && (m_velocity > 59))
		return 17;
	if ((m_velocity<60) && (m_velocity > 49))
		return 14;
	if ((m_velocity<50) && (m_velocity > 39))
		return 11;
	if ((m_velocity<40) && (m_velocity > 29))
		return 8;
	if ((m_velocity<30) && (m_velocity > 19))
		return 6;
	if ((m_velocity<20) && (m_velocity >= 1))
		return 3;
	if (m_velocity <= 0)
		return 0;
}