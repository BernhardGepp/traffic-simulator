#pragma once
//#include "sectionVisitor.h"
//#include "selectionFlowSimulation.h"

#include "vertex.h"
#include "PoolAllocator.h"
#include "vehicle.h"
//#include "sectionVisitor.h"
#include "selectionFlowSimulation.h"
#include "PrecompiledHeadersEdges.h"
#include "observer_subjekt.h"
#include "observer.h"

class edge {
private:
	int m_simulationIterator = 0;
	
	std::vector<vehicle*> vehicleEraseVector;
	int p1Shape = 99;
	int p2Shape = 99;
	HDC m_hdc;
	void(*m_f8PaintPoint)(HDC hdc, const std::vector<std::tuple<int, int,int>> &PointsToBePrinted) = nullptr;
	void(*m_f5PaintLane)(HDC hdc, const int &iPosXLk, const  int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanesa, const std::vector<std::tuple<int, int,int>> &PointsToBePrinted) = nullptr;
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV)=nullptr;
	int (*m_callback_getRandomNumber)()=nullptr;
	//int(randomSpeed_neu::*getRandomNumber)();
	//int m_sectionID = 0;
	int m_maxVelocity = 140;
	int m_maxVelocity_Density = 140;
	bool m_risingOrDescention = true;
	//ServiceVar
	//PrintPatternLine1LaneHoriNeg pp1;
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
	int m_numberOfVehicleinRange = 0;
public:
	observer* m_observerPTR = nullptr;
	concreteObserverSubjekt* m_cOSptr = nullptr;
	selectionFlowSimulation sFs;
	PrintPattern* m_ppPtr = nullptr;
	
	std::shared_ptr<vertex> m_startVertexPtr;
	std::shared_ptr<vertex> m_endVertexPtr;
	//std::unique_ptr<sectionVehicleSet> vehicleSetPtr= std::make_unique<sectionVehicleSet>(m_callback_getRandomNumber);
	int m_numberOfLanes = 1;
	
	bool m_verticalOrHorizontal = true;
	
	//std::vector<std::tuple<int, int,int>> pointContainer;
	int p1x = 0;
	int p1y = 0;
	int p2x = 0;
	int p2y = 0;
	std::vector<std::pair<std::pair<int, float>, std::vector<int>>> m_routeTable_IDrValueIDvertex;
	size_t m_routeTableIterator = 0;
	bool m_routeServiceBool = false;
	//std::vector<int>m_vectorOFmultilePathPerRoute;
	int m_startVertex = 0;
	int m_endVertex = 0;
	float m_weight = 0.0f;
	float m_density = 0.0f;
	float m_averageSpeed = 0.0f;
	float m_averageTravelTime = 0.0f;
	int m_length = 0;
	edge::edge() {

	}
	explicit edge::edge(const int& startVertex, const int& endVertex, const HDC& hdc,
		int(*callback_getRandomNumber)(),
		void(*f8PaintPoint)(HDC hdc, const std::vector<std::tuple<int, int,int>>& PointsToBePrinted),
		void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanesa, const std::vector<std::tuple<int, int,int>> &PointsToBePrinted),
		void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV),
		concreteObserverSubjekt* cOSptr
		)
		: m_startVertex(startVertex), m_endVertex(endVertex), m_hdc(hdc), m_callback_getRandomNumber(callback_getRandomNumber), m_f8PaintPoint(f8PaintPoint), m_f5PaintLane(f5PaintLane), m_f6PrintLaneInNumbers(f6PrintLaneInNumbers),m_cOSptr(cOSptr) {

		/*if ((m_startVertex != m_startVertexPtr->m_vertexID) || (m_endVertex != m_endVertexPtr->m_vertexID)) {
			this->~edge();
		}*/
		//tialisation();
		
		vehicleEraseVector.reserve(30);
		m_routeServiceBool = false;
		sFs.m_hdc = m_hdc;
		m_ppPtr->m_cbl.m_hdc = m_hdc;
		sFs.m_callback_getRandomNumber = callback_getRandomNumber;
		sFs.m_f6PrintLaneInNumbers = f6PrintLaneInNumbers;
		m_observerPTR = m_ppPtr->createObserver();
		m_cOSptr->registrieren(m_observerPTR);
		//sFs.PPPtrA = PPPtr;
			//m_vectorOFmultilePathPerRoute.clear();
		
		
	}
	explicit edge::edge(const int& startVertex, const int& endVertex, const HDC& hdc,PrintPattern* pp_ptr,
		int(*callback_getRandomNumber)(),
		void(*f8PaintPoint)(HDC hdc, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted),
		void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanesa, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted),
		void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV),
		concreteObserverSubjekt* cOSptr)
		: m_startVertex(startVertex), m_endVertex(endVertex), m_hdc(hdc),m_ppPtr(pp_ptr), m_callback_getRandomNumber(callback_getRandomNumber), m_f8PaintPoint(f8PaintPoint), m_f5PaintLane(f5PaintLane), m_f6PrintLaneInNumbers(f6PrintLaneInNumbers),m_cOSptr(cOSptr) {
		
		vehicleEraseVector.reserve(30);
		m_routeServiceBool = false;
		sFs.m_hdc = m_hdc;
		m_ppPtr->m_cbl.m_hdc = m_hdc;
		m_observerPTR = m_ppPtr->createObserver();
		sFs.m_callback_getRandomNumber = callback_getRandomNumber;
		sFs.m_f6PrintLaneInNumbers = f6PrintLaneInNumbers;
		m_cOSptr->registrieren(m_observerPTR);
	}
	edge::~edge() {
		delete m_ppPtr;
		//vehicleSetPtr.~unique_ptr();
		//vehicleSetPtr->~sectionVehicleSet();
	}
	edge::edge(const edge& other) = delete;
	edge::edge(edge&& other) noexcept {
		delete m_ppPtr;
		m_ppPtr = std::move(other.m_ppPtr);
		other.m_ppPtr = nullptr;
		m_simulationIterator = std::move(other.m_averageSpeed);
		vehicleEraseVector = std::move(other.vehicleEraseVector);
		p1Shape = std::move(other.p1Shape);
		p2Shape = std::move(other.p2Shape);
		m_hdc = std::move(other.m_hdc);
		m_maxVelocity = std::move(other.m_maxVelocity);
		m_maxVelocity_Density = std::move(other.m_maxVelocity_Density);
		m_risingOrDescention = std::move(other.m_risingOrDescention);
		m_numberOfVehicleinRange = std::move(other.m_numberOfVehicleinRange);
		m_observerPTR = std::move(other.m_observerPTR);
		other.m_observerPTR = nullptr;
		m_cOSptr = std::move(other.m_cOSptr);
		other.m_cOSptr = nullptr;
		sFs = std::move(other.sFs);
		m_startVertexPtr = std::move(other.m_startVertexPtr);
		m_endVertexPtr = std::move(other.m_endVertexPtr);
		m_numberOfLanes = std::move(other.m_numberOfLanes);
		m_verticalOrHorizontal = std::move(other.m_verticalOrHorizontal);
		p1x = std::move(other.p1x);
		p1y = std::move(other.p1y);
		p2x = std::move(other.p2x);
		p2y = std::move(other.p2y);
		m_routeTable_IDrValueIDvertex = std::move(other.m_routeTable_IDrValueIDvertex);
		m_routeTableIterator = std::move(other.m_routeTableIterator);
		m_routeServiceBool = std::move(other.m_routeServiceBool);
		m_startVertex = std::move(other.m_startVertex);
		m_endVertex = std::move(other.m_endVertex);
		m_weight = std::move(other.m_weight);
		m_density = std::move(other.m_density);
		m_averageSpeed = std::move(other.m_averageSpeed);
		m_averageTravelTime = std::move(other.m_averageTravelTime);
		m_length = std::move(other.m_length);
	}
	edge& operator=(const edge& other) = delete;
	edge& operator=(edge&& other) {
		delete m_ppPtr;
		m_ppPtr = std::move(other.m_ppPtr);
		other.m_ppPtr = nullptr;
		m_simulationIterator=std::move(other.m_averageSpeed);
		vehicleEraseVector=std::move(other.vehicleEraseVector);
		p1Shape = std::move(other.p1Shape);
		p2Shape = std::move(other.p2Shape);
		m_hdc = std::move(other.m_hdc);
		m_maxVelocity = std::move(other.m_maxVelocity);
		m_maxVelocity_Density = std::move(other.m_maxVelocity_Density);		
		m_risingOrDescention = std::move(other.m_risingOrDescention);
		m_numberOfVehicleinRange = std::move(other.m_numberOfVehicleinRange);
		m_observerPTR = std::move(other.m_observerPTR);
		other.m_observerPTR = nullptr;
		m_cOSptr = std::move(other.m_cOSptr);
		other.m_cOSptr = nullptr;
		sFs=std::move(other.sFs);		
		m_startVertexPtr=std::move(other.m_startVertexPtr);
		m_endVertexPtr = std::move(other.m_endVertexPtr);		
		m_numberOfLanes = std::move(other.m_numberOfLanes);
		m_verticalOrHorizontal = std::move(other.m_verticalOrHorizontal);
		p1x = std::move(other.p1x);
		p1y = std::move(other.p1y);
		p2x = std::move(other.p2x);
		p2y = std::move(other.p2y);
		m_routeTable_IDrValueIDvertex = std::move(other.m_routeTable_IDrValueIDvertex);		
		m_routeTableIterator = std::move(other.m_routeTableIterator);
		m_routeServiceBool = std::move(other.m_routeServiceBool);		
		m_startVertex = std::move(other.m_startVertex);
		m_endVertex = std::move(other.m_endVertex);
		m_weight = std::move(other.m_weight);
		m_density = std::move(other.m_density);
		m_averageSpeed = std::move(other.m_averageSpeed);
		m_averageTravelTime = std::move(other.m_averageTravelTime);
		m_length = std::move(other.m_length);
		return *this;
	}

	int edge::getStartVertex() {
		return m_startVertex;
	}
	int edge::getEndVertex() {
		return m_endVertex;
	}
	int edge::getSizeOfVehicleSet() {
		return sFs.vehicleSetPtr->m_vehicleSet.size();
	}
	void edge::sectionDestruct() {

		vehicle* vehiclePtr = nullptr;
		while (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {

			vehiclePtr = *sFs.vehicleSetPtr->m_vehicleSet.begin();
			sFs.vehicleSetPtr->m_vehicleSet.erase(sFs.vehicleSetPtr->m_vehicleSet.begin());
			m_VPAptr->deallocate(vehiclePtr);
			vehiclePtr = nullptr;
		}
		
	}
	void edge::initialisation() {
		
		p1x = m_startVertexPtr->m_XcoordinateVertex;
		p1y = m_startVertexPtr->m_YcoordinateVertex;
		p1Shape = m_startVertexPtr->m_shapeOfThatVertex;
		p2x = m_endVertexPtr->m_XcoordinateVertex;
		p2y = m_endVertexPtr->m_YcoordinateVertex;
		p2Shape = m_endVertexPtr->m_shapeOfThatVertex;
		
		if (p1x == p2x) {
			m_numberOfLanes = m_startVertexPtr->m_numberOfLanesVertical;
		}
		if (p1y == p2y) {
			m_numberOfLanes = m_startVertexPtr->m_numberOfLanesHorizontal;
		}
		if (p1x == p2x) {
			m_verticalOrHorizontal = true;
			if (p1y < p2y) {
				m_risingOrDescention = true;
				m_length = p2y - p1y;
				
			}
			if (p1y > p2y) {
				m_risingOrDescention = false;
				m_length = p1y - p2y;
				
			}
		}
		if (p1y == p2y) {
			m_verticalOrHorizontal = false;
			if (p1x < p2x) {
				m_risingOrDescention = true;
				m_length = p2x - p1x;
				
			}
			if (p1x > p2x) {
				m_risingOrDescention = false;
				m_length = p1x - p2x;
				
			}
		}
		sFs.setEndingPoints(m_startVertexPtr->m_XcoordinateVertex, m_startVertexPtr->m_YcoordinateVertex, m_endVertexPtr->m_XcoordinateVertex, m_endVertexPtr->m_YcoordinateVertex, m_maxVelocity, m_maxVelocity_Density);
		
		m_ppPtr->accept(sFs);
		
	}
	void edge::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef) {
		m_VPAptr = &poolAllocatorRef;
	}

	void edge::computeWeightOfEdge() {
		m_weight = 1 / ((static_cast<float>(sFs.vehicleSetPtr->sumOfVehicleSpeedInEdge())) / (static_cast<float>(m_length)));
	}
	void edge::computeEdgesCharactaristics() {
		m_density = 0.0f;
		m_averageSpeed = 0.0f;
		if (m_length > 0) {
			if (sFs.vehicleSetPtr->trafficCharacteristics().second > 0) {//vehicleSetPtr->trafficCharacteristics().second  =>> Anzahl der Fahrzeuge in Edge
				m_density = (static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().second)) / ((static_cast<float>(m_length)*0.001));
				m_averageSpeed = (static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().first)) / (static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().second));
			}
		}
		if (m_averageSpeed > 0) {
			m_averageTravelTime = m_averageSpeed / (static_cast<float>(m_length)*0.001);
		}
		else {
			m_averageTravelTime = static_cast<float>(m_maxVelocity) / (static_cast<float>(m_length)*0.001);
		}
		//m_weight = 1/(((static_cast<float>(vehicleSetPtr->trafficCharacteristics().first))/ (static_cast<float>(vehicleSetPtr->trafficCharacteristics().second))) / (static_cast<float>(m_length)));
		///Hier nachdenken ob das Richtig ist!!
		
	}


	void edge::simiRun(const int& simulationIterator) {
		m_simulationIterator = simulationIterator;
		
		for (auto &i : sFs.vehicleSetPtr->m_vehicleSet) {
			
			i->m_riseOrDecline = m_risingOrDescention;
			
		}
		if (m_numberOfLanes == 1) {
			flow1L(1,220);
			singleSimulationStep(220);
		}
		if (m_numberOfLanes == 2) {
			flow1L(1,440);
			singleSimulationStep(440);
		}
		if (m_observerPTR->m_position.first > 0) {//Wenn Observer aktiviert wurde!
			allocateVehicleAtPositionX();
		}
		if (simulationIterator % 10 == 0) {
			computeEdgesCharactaristics();
		}
		sFs.vehicleSetPtr->printContentOfSection(m_startVertexPtr->m_XcoordinateVertex, m_startVertexPtr->m_YcoordinateVertex, m_endVertexPtr->m_XcoordinateVertex, m_endVertexPtr->m_YcoordinateVertex);
		/*if ((m_endVertexPtr->m_vertexID == 4)&&(m_endVertexPtr->sizeOfTT().first>30)) {
			m_f6PrintLaneInNumbers(m_hdc, 4, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 1, true);
		}
		if ((m_endVertexPtr->m_vertexID == 4) && (m_endVertexPtr->sizeOfTT().second > 30)) {
			m_f6PrintLaneInNumbers(m_hdc, 4, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 2, true);
		}
		if ((m_endVertexPtr->m_vertexID == 1) && (m_endVertexPtr->sizeOfTT().first > 30)) {
			m_f6PrintLaneInNumbers(m_hdc, 1, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 1, true);
		}
		if ((m_endVertexPtr->m_vertexID == 1) && (m_endVertexPtr->sizeOfTT().second > 30)) {
			m_f6PrintLaneInNumbers(m_hdc, 1, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 2, true);
		}
		if ((m_endVertexPtr->m_vertexID == 3) && (m_endVertexPtr->sizeOfTT().first > 30)) {
			m_f6PrintLaneInNumbers(m_hdc, 3, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 1, true);
		}
		if ((m_endVertexPtr->m_vertexID == 3) && (m_endVertexPtr->sizeOfTT().second > 30)) {
			m_f6PrintLaneInNumbers(m_hdc,3, m_endVertexPtr->sizeOfTT().first, m_endVertexPtr->sizeOfTT().second, 2, true);
		}*/
	}


	void edge::flow1L(const int& a,const int& b) {

		bool checkIfPositionIsEmpty = false;
		//************************************************************
		//Prüfung ob erste Position im Set belegt ist!
		for (auto &i : sFs.vehicleSetPtr->m_vehicleSet) {
			i->m_riseOrDecline = m_risingOrDescention;
			if ((i->m_position == 0) && (m_risingOrDescention == true)) {
				//std::cout << "Allocation failed!\n";
				checkIfPositionIsEmpty = true;

			}
			if ((i->m_position == m_length) && (m_risingOrDescention == false)) {
				//std::cout << "Allocation failed!\n";
				checkIfPositionIsEmpty = true;

			}
		}
		if (checkIfPositionIsEmpty == false) {
			if (p1Shape == 1) {
				if (a < 150) {
					
					vehicle* VPAEptr = nullptr;
					
					VPAEptr = m_startVertexPtr->getVehiclePtrOutOfVertex(0, 0);
					if (VPAEptr != nullptr) {
						
						VPAEptr = routeAssignment(VPAEptr);
						

						
						sFs.vehicleSetPtr->insertSET(insertion(VPAEptr));// Einfügen der FahrzeugObjekten ins Set! Neu!
					}
					
				}
				/*else {
					if (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {
						if (a < 250) {
							if (m_numberOfVehicleinRange >= 2) {
								singleSimulationStep(b);
							}
							else {
								//dealocate All
								deallocateVehicleAtEnd(false);
							}
						}
						else {

						}
					}
				}*/
			}
			if ((p1Shape == 0) || (p1Shape == 11) || (p1Shape == 12) || (p1Shape == 21) || (p1Shape == 22)) {
				
				
				sFs.vehicleSetPtr->insertSET(insertion(m_startVertexPtr->getVehiclePtrOutOfVertex(m_endVertex, 0)));
				sort();
				
			}
		}
	}

	
	void edge::singleSimulationStep(const int& param) {
		size_t vehicleSetSize = 0;
		vehicleSetSize = sFs.vehicleSetPtr->getVehicleSetSize();
		size_t counter = 0;
		do {
			counter++;
			
			if (sFs.vehicleSetPtr->m_vehicleSet.size() > 0) {
				
				if ((m_length / sFs.vehicleSetPtr->m_vehicleSet.size()) >= param) {
					m_maxVelocity_Density = 80;
				}
				else {
					m_maxVelocity_Density = 140;
				}
				m_numberOfVehicleinRange = sFs.vehicleSetPtr->flow( m_numberOfLanes, m_length,m_risingOrDescention);
				
			}
		} while (counter < vehicleSetSize);
		deallocateVehicleAtEnd(true);
		//vehicleSetPtr->setServiceBoolFalse();
		//vehicleSetSize = vehicleSetPtr->getVehicleSetSize();
	}
	
	void edge::sort() {
		
		//flowSimulation1NegStraight dublicateSet;
		std::vector <vehicle*> vehicleVector;
		for (auto i : sFs.vehicleSetPtr->m_vehicleSet) {
			vehicleVector.push_back(i);
		}
		sFs.vehicleSetPtr->m_vehicleSet.clear();
		for (auto &i : vehicleVector) {
			sFs.vehicleSetPtr->m_vehicleSet.insert(i);
		}
	}

	
	vehicle* edge::routeAssignment(vehicle* VPAEptr) {
		VPAEptr->m_routeVertexID_vehicle.clear();

		if (!m_routeTable_IDrValueIDvertex.empty()) {


			//std::vector<int> multipleEndVertex;
			if ((m_routeTableIterator >= 0) && (m_routeTableIterator < m_routeTable_IDrValueIDvertex.size())) {

			}
			else {
				m_routeTableIterator = 0;//Iterator rücksetzen!
			}
			if (m_routeServiceBool == false) {
				m_routeServiceBool = true;
			}

			if (m_routeTableIterator < m_routeTable_IDrValueIDvertex.size()) {
				VPAEptr->m_routeVertexID_vehicle.clear();
				VPAEptr->m_routeID = m_routeTable_IDrValueIDvertex[m_routeTableIterator].first.first;
				//VPAEptr->m_routeVertexID_vehicle = m_routeTable_IDrValueIDvertex[m_routeTableIterator].second;

				for (size_t i = 0; i < m_routeTable_IDrValueIDvertex[m_routeTableIterator].second.size(); i++) {
					VPAEptr->m_routeVertexID_vehicle.push_back(m_routeTable_IDrValueIDvertex[m_routeTableIterator].second[i]);
				}


				m_routeTableIterator++;
				if (m_routeTableIterator >= m_routeTable_IDrValueIDvertex.size()) {
					m_routeTableIterator = 0;
				}

			}
			else {
				VPAEptr->m_routeID = -1;
				VPAEptr->m_routeVertexID_vehicle.clear();
				m_routeTableIterator = 0;
			}
		}
		return VPAEptr;
	}
	vehicle* edge::insertion(vehicle* VPAEptr) {
		if (VPAEptr != nullptr) {
			VPAEptr->setPtr(VPAEptr);
			VPAEptr->m_moblieORStationary = true;
			VPAEptr->m_riseOrDecline = m_risingOrDescention;
			VPAEptr->m_inRange = true;
			VPAEptr->m_lane = 1;
			VPAEptr->serviceBool = false;
			//VPAEptr->processedByIteration = false;
			if (m_risingOrDescention == true) {
				VPAEptr->m_position = 0;
			}
			if (m_risingOrDescention == false) {
				VPAEptr->m_position = m_length;
			}
			return VPAEptr;
			//m_vehicleList.push_back(VPAEptr);

		}
		return nullptr;
	}

	
	void edge::allocateVehicleAtPositionX(){//const int& xCoordinate, const int& yCoordinate) {
		bool checkIfPositionIsEmpty = false;
		
		
		//m_f6PrintLaneInNumbers(m_hdc, m_observerPTR->m_position.first, m_observerPTR->m_position.second, 22, m_cOSptr->m_observerPTRvector.size(),true);
		if (m_observerPTR->m_position.second>0) {
			for (auto &i : sFs.vehicleSetPtr->m_vehicleSet) {
				if (i->m_position == m_observerPTR->m_position.first) {
					//std::cout << "Allocation failed!\n";
					checkIfPositionIsEmpty = true;
					i->m_moblieORStationary = true;
					m_observerPTR->m_position.first = 0;
					m_observerPTR->m_position.second = 0;
					//file << "\n****Löschen!!!!!\n";
					break;
				}
				else {
					checkIfPositionIsEmpty = false;
					
				}
			
			}
			if (checkIfPositionIsEmpty == false) {
				vehicle* VPAEptr = nullptr;
				if (m_observerPTR->m_position.second==1) {
					VPAEptr = m_VPAptr->allocate( 1, m_observerPTR->m_position.first);
					VPAEptr->m_lane = 1;
				}
				if (m_observerPTR->m_position.second==2) {
					VPAEptr = m_VPAptr->allocate( 2, m_observerPTR->m_position.first);
					VPAEptr->m_lane = 2;
				}
				VPAEptr->setPtr(VPAEptr);  //Setzung der ID in Vehicle
				VPAEptr->m_pref_speed = 0;
				VPAEptr->m_moblieORStationary = false;
				VPAEptr->m_position = m_observerPTR->m_position.first;
				VPAEptr->m_inRange = true;
				VPAEptr->m_riseOrDecline = m_risingOrDescention;
				//VPAEptr->processedByIteration = false;
				
				if (VPAEptr != nullptr) {
					sFs.vehicleSetPtr->insertSET(VPAEptr);
				}
				
				sort();
				m_observerPTR->m_position.first = 0;
				m_observerPTR->m_position.second = 0;
				
			}
		}
		//return serviceBool;
	}


	void edge::deallocateVehicleAtEnd(bool totalRelease) {
		
		size_t a = 0;
		
		vehicleEraseVector.clear();
		if (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {
			for (auto &ii : sFs.vehicleSetPtr->m_vehicleSet) {
				ii->serviceBool = false;
				ii->m_riseOrDecline = m_risingOrDescention;
				if (totalRelease == true) {
					if (ii->m_inRange == false) {
						vehicleEraseVector.push_back(ii);
					}
				}
				else {
					vehicleEraseVector.push_back(ii);
				}
			}
			if (!vehicleEraseVector.empty()) {
				for (auto i : vehicleEraseVector) {					
					sFs.vehicleSetPtr->m_vehicleSet.erase(i);//Hier wird aus vehicleSet gelöscht! Oben geht es nicht, weil noch Prüfung über VehicleSet statt findet!
					m_endVertexPtr->vehiclePTRmanipulationInV(i);
					
				}
				
			}
		}
		else {

		}
	}	
};


