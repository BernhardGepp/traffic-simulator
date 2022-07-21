#include "PrecompiledHeadersEdges.h"
#include "graphTrafficGenerationOnFastRoutes.h"
#include  <fstream> 



//Constructor and destructor of the class:
graphTrafficGenerationOnFastRoutes::graphTrafficGenerationOnFastRoutes(const std::set<int>& setOfVertexes, std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
	std::vector<std::shared_ptr<edge>>& vectorOfEdges, callBackLinks* CBLptr) : graph(setOfVertexes, vectorOfVertex, vectorOfEdges, CBLptr) {
	file5.open("C:/Users/bernh/Desktop/inFastRoutes.txt");
}

graphTrafficGenerationOnFastRoutes::~graphTrafficGenerationOnFastRoutes() {
	file5.close();
}

void graphTrafficGenerationOnFastRoutes::calculationOfRouteIndex() {
	int serviceInt = 0;
	std::vector<std::tuple<int, int, float>>vectorOfMultibleRoute;
	bool serviceBool1 = false;
	bool serviceBool2 = false;
	file5 << "\nHallo\n";
	for (auto& i : m_vectorOfEdgesPtr) {
		i->computeWeightOfEdge();
		i->computeEdgesCharactaristics();
	}
	serviceInt = 0;
	for (std::vector<std::unique_ptr<route>>::reverse_iterator i = m_vectorOfRoutesPtr.rbegin(); i != m_vectorOfRoutesPtr.rend(); ++i) {
		(*i)->m_currentTravelTime = 0.0f;
		(*i)->routeimpactIndexCalculation();
		file5 << "\ninside Dubble loop " << serviceInt << " m_currentTravelTime: " << (*i)->m_currentTravelTime;
		if ((*i)->m_index > 0 ) {
			serviceBool1 = false;
			file5 << "\nm_index > 0: "<< serviceInt<<" m_currentTravelTime: "<< (*i)->m_currentTravelTime;
			if (!vectorOfMultibleRoute.empty()) {
				for (auto& ii : vectorOfMultibleRoute) {
					if ((std::get<0>(ii) == (*i)->m_vertexOfRouteID[0]) && (std::get<1>(ii) == (*i)->m_vertexOfRouteID.back())) {
						serviceBool1 = true;
						if (std::get<2>(ii) > (*i)->m_currentTravelTime)
							std::get<2>(ii) = (*i)->m_currentTravelTime;
					}
				}
			}
			if (!serviceBool1) {
				file5 << "\nvectorOfMultibleRoute.push_back";
				vectorOfMultibleRoute.push_back(std::make_tuple((*i)->m_vertexOfRouteID[0], (*i)->m_vertexOfRouteID.back(), (*i)->m_currentTravelTime));
			}
			file5 << "\t" << (*i)->m_currentTravelTime<<"\tsize: "<< vectorOfMultibleRoute.size();
		}
		serviceInt++;
	}
	serviceInt = 0;
	for (std::vector<std::unique_ptr<route>>::reverse_iterator i = m_vectorOfRoutesPtr.rbegin(); i != m_vectorOfRoutesPtr.rend(); ++i) {
		serviceInt = serviceInt + 10;
		file5 << "\n" << (*i)->m_vertexOfRouteID[0] << "\t" << (*i)->m_vertexOfRouteID.back()<<"\tserviceInt: " << serviceInt;
		for (auto& ii : vectorOfMultibleRoute) {
			serviceInt++;
			file5 << "\n" << (*i)->m_vertexOfRouteID[0] << "\t" << (*i)->m_vertexOfRouteID.back()<<"\t"<< std::get<0>(ii) << "\t" << std::get<1>(ii) << "\tserviceInt: " << serviceInt << "\tTravelTimeListe: " << std::get<2>(ii) << "\tTravelTimeRoute: "<< (*i)->m_currentTravelTime;
			if ((std::get<0>(ii) == (*i)->m_vertexOfRouteID[0]) && (std::get<1>(ii) == (*i)->m_vertexOfRouteID.back())) {
				
				if (std::get<2>(ii) > (*i)->m_currentTravelTime) {
					std::get<2>(ii) = (*i)->m_currentTravelTime;
				}
			}

		}
	}
	serviceInt = 0;
	for (auto& i : m_vectorOfEdgesPtr) {
		i->m_routeTable_IDrValueIDvertex.clear();

		serviceInt = 0;
		
		for (auto& ii : m_vectorOfRoutesPtr) {
			file5 << "\n\nuntere Zeile: " << ii->m_vertexOfRouteID[0] << "\t" << ii->m_vertexOfRouteID.back() << "\tvektor of Routes.size: " << m_vectorOfRoutesPtr.size();
			serviceBool1 = false;
			serviceBool2 = false;
			for (auto& iii : vectorOfMultibleRoute) {
				file5 << "\nfor vectorOfMultibleRoute: " << std::get<0>(iii) << "\t" << std::get<1>(iii) << "\tsize: " << vectorOfMultibleRoute.size();
				if ((std::get<0>(iii) == ii->m_vertexOfRouteID[0]) && (std::get<1>(iii) == ii->m_vertexOfRouteID.back())) {
					serviceBool1 = true;
				}
				
				if ((std::get<0>(iii) == ii->m_vertexOfRouteID[0]) && (std::get<1>(iii) == ii->m_vertexOfRouteID.back()) && (std::get<2>(iii) == ii->m_currentTravelTime)) {
					serviceBool2 = true;
					file5 << "\ninnere Zeile: " << ii->m_vertexOfRouteID[0] << "\t" << ii->m_vertexOfRouteID.back();
				}
			}
			file5 << "\nserviceBool1: " << serviceBool1 << "\tserviceBool2: " << serviceBool2;
			if ((i->m_startVertex == ii->m_vertexOfRouteID[0]) && (i->m_endVertex == ii->m_vertexOfRouteID[1])&&
				(((serviceBool1==false)&&(serviceBool2==false))||
				((serviceBool1 == true) && (serviceBool2 == true)))
				
				) {
				file5 << "\nletzte Zeile";
				if (ii->m_currentTravelTime < (ii->m_initalTravelTime * 5.0f)) {
					std::pair<int, float> p = std::make_pair(serviceInt, ii->m_currentTravelTime);
					std::pair<std::pair<int, float>, std::vector<int>> p1 = std::make_pair(p, ii->m_vertexOfRouteID);

					i->m_routeTable_IDrValueIDvertex.push_back(p1);
				}
			}
			serviceInt++;
		}
	}
}