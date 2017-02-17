MatchPoint - Read Me
----------------------------
----------------------------


Needed Third Party Libraries
----------------------------

Please load and compile the following third party libraries/tool:

1. CMake (version 2.8 or higher)
2. Litmus (in this distribution; see \Utilities\Litmus; if you want tests) 
3. itk (4.6.0 or higher) 
5. doxygen (if you want to generate a source code documentation)

Installation instruction
------------------------

Remark: To make sure everything runs smoothly, please make sure that all libraries and the RTToolbox
are either compiled with \MD or \MT flags.

If third party library packages cannot be found automatically, cmake will ask for them. 
Please give the location of the root folder, where the libraries where built for itk and Litmus.


[A. ITK]

A.1. Configure ITK with CMake (seperated binary folder recommended)
A.2. Build ITK

[B. If you build tests - Litmus]

B.1. Configure Litmus with CMake (seperated binary folder recommended)
B.1.1 Activate parameter "LIT_ENABLE_ITK_SUPPORT"

B.2. Build Litmus

[C. Configure/Build MatchPoint]

C.1 Configure with CMake

C.2 Select external registration libraries you want to wrap. Remark: If you want to build the included elastix wrapper, you need the elastix source code compiled on your system.
   
C.3 Generate CMake configuration

C.4 Build MatchPoint and have fun!


[D. Documentation]

D.1 Generate the documentation using doxygen and the configuration found in "MatchPoint_binary_dir/Documentation/doxygen.config".