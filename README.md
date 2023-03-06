# gaussian-Fields

This project build has been successfully built with the following:
1. visual studio 2019
2. openFrameworks release of_v0.11.2_vs2017_release

The way that I built it is as follows:
1. download openFrameworks of_v0.11.2_vs2017_release.zip & extract
2. within the directory of_v0.11.2_vs2017_release, navigate to the directory /examples/math
3. within the directory math/ clone the gaussian-Fields repo 
4. within the gaussian-Fields repo, open the .sln file using Visual Studio 2019
5. build the project
6. run the project
7. if you get an error when you try to run, try setting gaussianFields as the single startup project
   a. right click "Solution 'gaussianFields'" in the VS solution explorer
   b. -> Properties
   c. select 'Single Startup Project', and indicate 'gaussianFields'
8. spacebar reinitializes things; pressing 'f' temporarily zeros out the forces
