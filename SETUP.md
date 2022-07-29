# Setup

*** 

Step-by-step set up for my project

### Mac OS

***

1. Setup VS Code
    - Download & install the software
    - Install all necessary extension to run C++ : in particular C++ with IntelliSense
2. Setup Homebrew & external packages
    - Install Homewbrew
    - Download SDL2 library
    - Link library with project in *cpp_properties.json* 
3. Setup CMake
    - Download and install cmake (can be done through Homebrew)
    *Note* : When adding a new external library, do not forget to link it in the CMake file to compile it properly

You should be done for installing all the requirements

Now, go within the project directory and enter build it :


> $ mkdir build
> 
> $ cd build
> 
> $ cmake ..
> 
> $ cmake --build .

The project will be built and compiled.

*Note* : A few warnings will be generated. They stem from the use of *auto* type in some file.  ***Correct this in the future***


### Windows

***

TBD


