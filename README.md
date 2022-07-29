# Cpp3DHungerGames

Here is a first working version of a lab immersion project in Jaksic Laboratory at EPFL done during 02/22 to 07/22. It aims at reproducing and simulating an in vitro evolutionary biology expirement to identify genetic factors of cognition in *Drosophila Melanogaster*. Its purpose is to identify possible parameters values to run the in vitro experiment and explore models to explain drosophila's behaviour.

### 1. Summary

#### Abstract

This project consists of a simulated 3D cilyndrical arena divided in multiple sections to form different rooms. Each room is connected to the next one by multiple one-way entrances in the wall separating them. It simulates agents within the arena. The agents are currently characterized with having random trajectories and can be attracted to a food object if in the same room. The food object is a simple point of attraction located at the center of a room, shifting from room to room. The "null" model implemented so far is a force based model with random attractor points drawn from a uniform distribution.

#### Project executables

The project generates two executable files :

- *Sim3D*, the main part of the project. Can run multiple simulation and record data for analysis. Generates two directories : *SimConfig* & *SimData* that keep track of simulation configuration and simulation data respectively. 
- *DrawArena3D* 2D graphical representation of the simulation, does not save any data. Used to check correct behaviour of simulation and visualize it. (Limited scope as it is a 2D representation for a 3D simulation)

### 2. Requierements

For all the project : 
- C++11 with standard libraries
- CMake : version >= 3.10
For graphics :
- SDL library

### 3. Setup

#### 3.1 Installing & Configuring CMake

##### Mac OS

I am using Visual Studio Code a scoding environment, so some steps and configurations might change. Install the package using *[Homebrew](https://brew.sh/)*. *CMakeLists.txt* should be already configured and working for the porject.

##### Windows 

**TBD**

##### Linux?

**TBD**

#### 3.2 Installing SDL2

##### Mac OS

Once again, go on *[Homebrew](https://brew.sh/)* and install the package from there. Most troubles should be coming from linking the library to your environment. In the case of VS Code, do not forget to add the path to the *.json* properties file for the project. 

##### Windows

**TBD**

##### Linux? 

**TBD**

#### 3.3 Building the executables

##### Mac OS

Be sure to run this following command line while being in the project directory.
After downloading the project and installing all the requirements, run these commands in the terminal

> $ mkdir build
> 
> $ cd build
>
> $ cmake ..
>
> $ cmake --build .

The result should be two executable file ready to be launched in the terminal. 

*Note* : *Sim3D* can take arguments to configure the simulation, it is not the case for *DrawArena3D*.

##### Windows

**TBD**

##### Linux? 

**TBD**

### 4. Classes, Object & Interactions

#### 4.1 Classes

List of classes and small description of there use/utility :

- **Vector3D** : Base utility class, defines 3D vectors and basic operations for the project.
- **Cuboid** : Defines a 3D cuboid shape built with 8 points. Base element to construct walls & entrances. Include many utility functions as well.
- **Wall** : Simulation object that divides the arena in multiple rooms.
- **Entrance** : Simulation object that is part of a wall and enables agents to cross walls.
- **Arena3D**  : Forms cylindrical arena built from walls, in which simulation takes place.
- **Fly3D** : Agent of the simulation, moves within the arena, going from room to room.
- **Food** : Attractor object for the agents, shift from room to room.
- **Simulation3D** : Regroup every element of the simulate and runs it.

- **Utility_SDL** : Utility functions for graphic elements



##### Other

- **main.cpp** : Defines Sim3D executable
- **DrawArena3D.cpp** : Defines DrawArena3D executable
- **Test.cpp** : Defines executable that checks normal behaviour for Vector3D & Cuboid mainly

#### 4.2 Interactions





#### Bibliography & Other resources

[Simulating Flying Insects](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0155698#sec025) main implementation idea

[SDL](https://www.libsdl.org/) library

?[RVO2-3D](https://github.com/snape/RVO2-3D) 

?[Reciprocal Velocity Obstacles for Real-Time Multi-Agent Navigation](https://gamma.cs.unc.edu/RVO/icra2008.pdf)