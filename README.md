# gaussian-Fields

This project has been successfully built with the following:
1.  Visual studio 2019 or Xcode 14
2.  openFrameworks of_v0.11.2_vs2017_release

The way that I build this project is as follows:
1.  Download from https://openframeworks.cc/download/ the latest windows version of openFrameworks
    (i downloaded of_v0.11.2_vs2017_release.zip, either for windows or Mac depending what you are using)
2.  Extract the zip
3.  Within the directory of_v0.11.2_vs2017_release, navigate to the directory /examples/math
4.  Clone the gaussian-Fields repo so that it sides alongside the other math examples
5.  Within the gaussian-Fields repo, open the .sln file (if using VS) or the .xcodeproj file (if using Xcode)
6.  Build the project
7.  Run the project
8.  If you get a VS error when you try to run, try setting gaussianFields as the single startup project
    * right click "Solution 'gaussianFields'" in the VS solution explorer
    * -> Properties
    * select 'Single Startup Project', and indicate 'gaussianFields'

Running:
1.  Pressing::
    * 'r' reinitializes the attractors & the particles
    * 'z' zeros out the forces (for as long as it is pressed)
    * Spacebar pauses/plays the simulation
    * 'f' runs the velocity verlet integrator in the forward or the backward direction
2.  If you run into performance issues, reduce within ofApp.cpp the number of attractors 'nattractors' & number of particles 'nparticles'
3.  Have fun!
