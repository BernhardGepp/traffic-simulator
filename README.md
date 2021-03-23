# TrafficSimulator

## Short introduction to the application:

This application fulfils the basic requirements of a traffic simulator which reproduces driving behaviour in a virtual road network. The user of this tool is invited to build a network consisting of links with one or two lanes. After completion of the construction of the traffic network the simulation can be invoked.
The simulation will be terminated after 1000 simulation iterations.

During the execution of the traffic simulation the user is allowed to interfere into the simulation by blocking lanes of the network. 

## Motivation and meaning behind the development of this application:

This “Traffic Simulator” was gained out of the motivation to get programming experience. The author of this application has a degree in “Intelligent Transport Systems”. Therefor it was obvious for the author to create a tool which is related to the field of traffic planning. This application contains algorithms which state of the art and are also used professional traffic simulations tools are used. 
The external appearance may look outdated and will remind at simulation applications of the nineties but the core of this application perfectly transferrable to contemporary applications.

## Used technology:

•	C++
C++ features:
o	GDI Libraries in C++
o	WinAPI (windows.h)
o	Precompiled Header
o	Boost Container
o	Pool allocator
o	Multithreading (Futures)

## Quick Start:

The main-file represents the core of the project. Make sure that your chosen IDE can deal with those two following issues: 
•	This application is designed as windows application. It uses the functions of the Window Application Interface. Make sure that your IDE supports this.
•	This C++-application uses a header file which contains precompiled header libraries (PrecompiledHeadersEdges.h). It contains several “standard template header files” which are used in the project. Make sure that the IDE deals with that. 

## FAQ:

### Can I contribute to the “traffic flow simulator”?

This project is considered as completed by the author. Which means the project corresponds now to the initial imagination how it should be at the beginning of the programming.
Comments about programming style are welcome as long they are constructive.
As author of the code I want to express: Feel free to use the code or parts of the code for your own projects. Except the part “PoolAllocator” which is mostly inspired by “Brotcrunsher”.In that particular case respect the intensions of the author “Brotcrunsher” which lies behind his work and his publications. 
The rest of the code entirely written by myself, which means you don´t harm any kind of intellectually property of other people. 

### IDE, Compiler, C++ Version:

The project was built with Microsoft Visual Studio Version 15.9.20. Most parts of the project were made with the C++14 Version. 

### How to run the simulation?

The program consists of two stages. User can create in the first stage a network. In the second stage the simulation is invoked in the network which was built in the first stage.

### Exists there a project description?
Yes! This repository includes a project description which describes the structure of the application. This description contains UML class diagrams, sequence diagrams, activity diagrams etc.


