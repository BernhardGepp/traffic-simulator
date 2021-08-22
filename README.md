# TrafficSimulator

## Brief introduction to the application:

This application meets the basic requirements of a traffic simulator, which replicates driving behavior on a virtual road network. The user of this tool is asked to build a network of one or two lane connections. After the construction of the traffic network is completed, the simulation can be run.
The simulation is terminated after 1000 simulation iterations.

During the execution of the traffic simulation, the user is allowed to intervene in the simulation by blocking lanes of the network. 

## Motivation and purpose behind the development of this application:

This "Traffic Simulator" was created out of the motivation to gain programming experience. The author of this application has a degree in "Intelligent Transport Systems". Therefore, it was obvious for the author to develop a tool that has a relation to the field of traffic planning. This application contains state-of-the-art algorithms that are also used in professional traffic simulation programs. 
The external appearance may seem outdated and reminiscent of simulation applications from the nineties, but the core of this application is quite transferable to contemporary applications.

## Technology used:

- C++
C++ features:
- GDI libraries in C++
- WinAPI (windows.h)
- Precompiled headers
- [Boost container](https://github.com/boostorg)
- Pool allocator
- Multithreading (Futures)
- [Google Test](https://github.com/google/googletest)

## Quick start:

The main file represents the core of the project. Make sure that the IDE you choose can handle the following two items: 
- This application is designed as a Windows application. It uses the Window Application Interface features. Make sure that your IDE supports this.
- This C++ application uses a header file that contains precompiled header libraries (PrecompiledHeadersEdges.h). It contains several "standard template header files" that are used in the project. Make sure that the IDE can handle them. 

## FAQ:

### Can I contribute to the "traffic flow simulator"?

This project is considered complete by the author. That is, the project is now as it was originally envisioned to be when programming began.
Comments on programming style are welcome as long as they are constructive.
As the author of the code, I would like to express: Feel free to use the code or parts of the code for your own projects. With the exception of the "PoolAllocator" part, which is mostly inspired by "Brotcrunsher", respect the intentions of the author "Brotcrunsher" behind his work and publications. 
The rest of the code was written entirely by me, which means you are not infringing on any intellectual property of other people. 

### IDE, Compiler, C++ Version:

The project was created using Microsoft Visual Studio version 15.9.20. Most parts of the project were created with C++14 version. 

### How is the simulation executed?

The program consists of two stages. In the first stage, the user can create a network. In the second stage, the simulation is called in the network that was created in the first stage.

### Is there a project description?
Yes! This repository contains a project description that describes the structure of the application. This description includes UML class diagrams, sequence diagrams, activity diagrams, etc.


