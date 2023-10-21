#pragma once
#include "selectionFlowSimulation.h"
#include "observer_subjekt.h"

class edge {
private:
	int m_simulationIterator = 0;
	int m_maxVelocity = 140;
	int m_maxVelocity_Density = 140;
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
	
public:
	observer* m_observerPTR = nullptr;
	concreteObserverSubject* m_cOSptr = nullptr;
	selectionFlowSimulation sFs;
	std::unique_ptr<PrintPattern> m_ppPtr;	
	std::shared_ptr<vertex> m_startVertexPtr;
	std::shared_ptr<vertex> m_endVertexPtr;
	int m_numberOfLanes = 1;
	bool m_verticalOrHorizontal = true;
	int m_startVertex = 0;
	int m_endVertex = 0;
	float m_weight = 0.0f;
	float m_density = 0.0f;
	float m_averageSpeed = 0.0f;
	float m_averageTravelTime = 0.0f;
	int m_length = 0;
	bool m_risingOrDescention = true;
	

	edge();
	explicit edge(const std::shared_ptr<vertex>&, const std::shared_ptr<vertex>&,  int , std::unique_ptr<PrintPattern>,concreteObserverSubject* );
	edge(const edge& other)=delete;
	edge(edge&& );
	edge& operator=(const edge& other) = delete;
	edge& operator=( edge&& other) = default;
	~edge() noexcept;

	int getStartVertex();
	int getEndVertex();
	void sectionDestruct();
	void setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& );
	void computeWeightOfEdge();
	void computeEdgesCharactaristics();
	void simiRun(const int& );
	void writeSimulationResultsIntoDataContainer();
	void allocateVehicleAtPositionX();
};


