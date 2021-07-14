#include "pch.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\PrecompiledHeadersEdges.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\edge.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vertex.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vertexEnd.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vertexFlex.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vertexStart.h"
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vehicle.cpp" 
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\vehicle.h" 
#include "E:\vs_Community\simi_projekt\oberflaeche_versuch\22_Sommer2021\Projekt1\velocityToLength.h" 
 


TEST(TestCaseName, TestName) {
	velocityToLength o;

	EXPECT_EQ(o.VLStepConversion(99), 25);
	EXPECT_TRUE(true);

}


TEST(TestCaseName2, TestName2) {
	
	
	edge e1;
	edge e2;
	edge e3;
	edge e4;
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	e2.m_startVertex = 12;
	e2.m_endVertex = 13;
	e3.m_startVertex = 12;
	e3.m_endVertex = 14;
	e4.m_startVertex = 12;
	e4.m_endVertex = 15;
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	std::shared_ptr<vertex>v3 = std::make_shared<vertexEnd>(0, 200, 2);
	std::shared_ptr<vertex>v4 = std::make_shared<vertexEnd>(200, 400, 2);
	std::shared_ptr<vertex>v5 = std::make_shared<vertexEnd>(400, 200, 2);
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	e2.m_startVertexPtr = v2;
	e2.m_endVertexPtr = v3;
	e2.m_endVertex = 13;
	e3.m_startVertexPtr = v2;
	e3.m_endVertexPtr = v4;
	e3.m_endVertex = 14;
	e4.m_startVertexPtr = v2;
	e4.m_endVertexPtr = v5;
	e4.m_endVertex = 15;
	e1.m_length = 200;
	e2.m_length = 200;
	e3.m_length = 200;
	e4.m_length = 200;
	e1.m_risingOrDescention = true;
	e2.m_risingOrDescention = false;
	e3.m_risingOrDescention = true;
	e4.m_risingOrDescention = true;
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.sFs.vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(120, 200);
	e3.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e4.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.p1Shape = 0;
	e3.p1Shape = 0;
	e4.p1Shape = 0;

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	v3->m_vertexID = 13;
	v4->m_vertexID = 14;
	v5->m_vertexID = 15;
	
	v2->setTransmissionTable(13);
	v2->setTransmissionTable(14);
	v2->setTransmissionTable(15);
	
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[91];
	int counter = 0;
	for (int i = 0; i < 90; i++) {

		
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		if (counter == 0) {
			vehicleArray[i].m_routeID = 1;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,13 };
		}
		if (counter == 1) {
			vehicleArray[i].m_routeID = 2;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,14 };
		}
		if (counter == 2) {
			vehicleArray[i].m_routeID = 3;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,15 };
		}
		counter++;
		if (counter == 3) {
			counter = 0;
		}
	}
	
	counter = 0;
	for (int i = 0; i < 500; i++) {
		
		if (counter < 90) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			//e1.sFs.vehicleSetPtr->flow(1, e1.m_length, e1.m_risingOrDescention);
		}
		
		counter++;
		
		e1.singleSimulationStep(220);
		
		
		e1.deallocateVehicleAtEnd(true);
		
		e2.flow1L(1, 220);
		
		e2.singleSimulationStep(220);
		e2.deallocateVehicleAtEnd(true);
		
		e3.flow1L(1, 220);
		
		e3.singleSimulationStep(220);
		e3.deallocateVehicleAtEnd(true);
		
		e4.flow1L(1, 220);
		
		e4.singleSimulationStep(220);
		e4.deallocateVehicleAtEnd(true);
		
	}
	

	EXPECT_EQ(v3->m_numberOfVehicle, 30);
	EXPECT_TRUE(true);

	EXPECT_EQ(v4->m_numberOfVehicle, 28);
	EXPECT_TRUE(true);
	EXPECT_EQ(v5->m_numberOfVehicle, 28);
	EXPECT_TRUE(true);
	
	delete[] vehicleArray;
	file.close();

}

TEST(TestCaseName1, TestName1) {
	velocityToLength o;
	vertexStart v(10, 100, 1, 1);

	EXPECT_EQ(o.VLStepConversion(69), 17);
	EXPECT_TRUE(true);
}
TEST(TestCaseName3, TestName3) {
	

	edge e1;
	edge e2;
	
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	e2.m_startVertex = 12;
	e2.m_endVertex = 13;
	
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	std::shared_ptr<vertex>v3 = std::make_shared<vertexEnd>(0, 200, 2);
	
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	e2.m_startVertexPtr = v2;
	e2.m_endVertexPtr = v3;
	e2.m_endVertex = 13;
	
	e1.m_length = 200;
	e2.m_length = 200;
	
	e1.m_risingOrDescention = true;
	e2.m_risingOrDescention = false;
	
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.sFs.vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(120, 200);
	
	e2.p1Shape = 0;
	
	

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	v3->m_vertexID = 13;
	
	v2->setTransmissionTable(13);
	
	
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[91];
	
	for (int i = 0; i < 90; i++) {

		
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		
		vehicleArray[i].m_routeID = 1;
		vehicleArray[i].m_routeVertexID_vehicle = { 10,12,13 };
		
	}
	
	
	for (int i = 0; i < 500; i++) {
		
		if (i < 90) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			//e1.sFs.vehicleSetPtr->flow(1, e1.m_length, e1.m_risingOrDescention);
		}
		
		
		

		e1.singleSimulationStep(220);
		
		e1.deallocateVehicleAtEnd(true);
		
		e2.flow1L(1, 220);
		
		e2.singleSimulationStep(220);
		e2.deallocateVehicleAtEnd(true);
		
		
		
		
	}
	
	EXPECT_EQ(v3->m_numberOfVehicle, 90);
	EXPECT_TRUE(true);

	
	
	delete[] vehicleArray;
	

}
TEST(TestCaseName4, TestName4) {
	

	edge e1;
	
	edge e3;
	edge e4;
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	
	e3.m_startVertex = 12;
	e3.m_endVertex = 14;
	e4.m_startVertex = 12;
	e4.m_endVertex = 15;
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	
	std::shared_ptr<vertex>v4 = std::make_shared<vertexEnd>(200, 400, 2);
	std::shared_ptr<vertex>v5 = std::make_shared<vertexEnd>(400, 200, 2);
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	
	e3.m_startVertexPtr = v2;
	e3.m_endVertexPtr = v4;
	e3.m_endVertex = 14;
	e4.m_startVertexPtr = v2;
	e4.m_endVertexPtr = v5;
	e4.m_endVertex = 15;
	e1.m_length = 200;
	
	e3.m_length = 200;
	e4.m_length = 200;
	e1.m_risingOrDescention = true;
	
	e3.m_risingOrDescention = true;
	e4.m_risingOrDescention = true;
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	
	e3.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e4.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	
	e3.p1Shape = 0;
	e4.p1Shape = 0;

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	
	v4->m_vertexID = 14;
	v5->m_vertexID = 15;
	
	
	v2->setTransmissionTable(14);
	v2->setTransmissionTable(15);
	
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[101];
	int counter = 0;
	for (int i = 0; i < 100; i++) {

		
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		if (counter == 0) {
			vehicleArray[i].m_routeID = 1;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,14 };
		}
		if (counter == 1) {
			vehicleArray[i].m_routeID = 2;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,15 };
		}
		
		counter++;
		if (counter == 2) {
			counter = 0;
		}
	}
	
	counter = 0;
	for (int i = 0; i < 500; i++) {
		
		if (counter < 100) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			
		}
		
		counter++;
		

		e1.singleSimulationStep(220);
		
		e1.deallocateVehicleAtEnd(true);
		
		
		e3.flow1L(1, 220);
		
		e3.singleSimulationStep(220);
		e3.deallocateVehicleAtEnd(true);
		
		e4.flow1L(1, 220);
		
		e4.singleSimulationStep(220);
		e4.deallocateVehicleAtEnd(true);
	
	}
	
	
	EXPECT_EQ(v2->m_numberOfVehicle, 100);
	EXPECT_TRUE(true);

	EXPECT_EQ(v4->m_numberOfVehicle, 48);
	EXPECT_TRUE(true);
	EXPECT_EQ(v5->m_numberOfVehicle, 47);
	EXPECT_TRUE(true);

	
	delete[] vehicleArray;
	file.close();

}