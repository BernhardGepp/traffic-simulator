#pragma once
#include "vertex.h"
#include "PoolAllocator.h"
#include "vehicle.h"
#include "selectionFlowSimulation.h"
#include "PrecompiledHeadersEdges.h"
#include "observer_subjekt.h"
#include "observer.h"
static int hilfezahlera;

class edge {
private:
	int m_simulationIterator = 0;
	int m_maxVelocity = 140;
	int m_maxVelocity_Density = 140;
	int m_numberOfVehicleinRange = 0;
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
	
public:
	std::string textaa = "C:/Users/bernh/Desktop/edge" + std::to_string(hilfezahlera) + ".txt";
	std::ofstream file5;
	observer* m_observerPTR = nullptr;
	concreteObserverSubjekt* m_cOSptr = nullptr;
	selectionFlowSimulation sFs;
	std::unique_ptr<PrintPattern> m_ppPtr;	
	std::shared_ptr<vertex> m_startVertexPtr;
	std::shared_ptr<vertex> m_endVertexPtr;
	int m_numberOfLanes = 1;
	bool m_verticalOrHorizontal = true;
	std::vector<std::pair<std::pair<int, float>, std::vector<int>>> m_routeTable_IDrValueIDvertex;
	size_t m_routeTableIterator = 0;
	bool m_routeServiceBool = false;
	int m_startVertex = 0;
	int m_endVertex = 0;
	float m_weight = 0.0f;
	float m_density = 0.0f;
	float m_averageSpeed = 0.0f;
	float m_averageTravelTime = 0.0f;
	int m_length = 0;
	bool m_risingOrDescention = true;
	std::vector<vehicle*> vehicleEraseVector;

	edge();
	explicit edge(const int& , const int& , const int& , std::unique_ptr<PrintPattern>&,concreteObserverSubjekt* );
	edge(const edge& other)=delete;
	edge(edge&& );
	edge& operator=(const edge& other) = delete;
	edge& operator=( edge&& other) = default;
	~edge() noexcept;


	int getStartVertex();
	int getEndVertex();
	void sectionDestruct();
	void initialisation();
	void setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& );
	void computeWeightOfEdge();
	void computeEdgesCharactaristics();
	void simiRun(const int& );
	void flow1L(const int& , const int& );
	void singleSimulationStep(const int& );
	void sort();
	vehicle* routeAssignment(vehicle* );
	vehicle* insertion(vehicle* );
	void allocateVehicleAtPositionX();
	void deallocateVehicleAtEnd(bool);
};


