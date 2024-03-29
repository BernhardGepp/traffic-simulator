#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vertexObjectCreator.h"
#include "vertexEnd.h"
#include "vertexFlex.h"
#include "vertexStart.h"

//************************************************************************************
//Implementation of the factory method for creating vertex objects.

std::shared_ptr <vertex> createVertex::create(const int& xvalue, const int& yvalue, const int& shapeOfThatVertex) {
	int shapeOfThatVertex_intern = shapeOfThatVertex;
	
	switch (shapeOfThatVertex_intern) {
	case 1:
		createdVertex=std::make_unique<vertexStart>(xvalue, yvalue, shapeOfThatVertex);
		break;
	case 2:
		createdVertex= std::make_unique<vertexEnd>(xvalue, yvalue, shapeOfThatVertex);
		break;
	case 11:
		createdVertex= std::make_unique<vertexFlex>(xvalue, yvalue, shapeOfThatVertex);
		break;
	}
	createdVertex->m_vertexID = counter;
	counter++;
	return createdVertex;
}

void createVertex::decrementCounter() {
	counter--;
}