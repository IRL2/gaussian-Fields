# gaussian-Fields

This project has been successfully built with the following:
1.  Visual Studio 2019 on Windows
2.  Xcode 14 on Mac
3.  openFrameworks of_v0.11.2_vs2017_release

Repo destination:
1.  Download from https://openframeworks.cc/download/ the latest windows version of openFrameworks
    * for example, I downloaded of_v0.11.2_vs2017_release.zip, either for windows or Mac depending what you are using
2.  Extract the zip
3.  Within the directory of_v0.11.2_vs2017_release, navigate to the directory /examples/math
4.  Clone the gaussian-Fields repo so that it sits alongside the other math examples
5.  Within the gaussian-Fields repo, open the .sln file (if using VS) or the .xcodeproj file (if using Xcode)
6.  Build the project
7.  Run the project

Notes
1.  If you get a VS error when you try to run, try setting gaussianFields as the single startup project
    * right click "Solution 'gaussianFields'" in the VS solution explorer
    * -> Properties
    * select 'Single Startup Project', and indicate 'gaussianFields'
2.  For Xcode, I seem to get optimal performance with the build target set to $(RECOMMENDED_MACOSX_DEPLOYMENT_TARGET)
    * in the project navigator, click on gaussian-Fields
    * under the 'General' tab, go to 'Minimum Deployments'
    * in the 'macOS' dropdown menu, ensure the selection of $(RECOMMENDED_MACOSX_DEPLOYMENT_TARGET)
    * building commit 06d3176 in release mode on my macbook air m2 2022 (macOS 13.2.1), 22,000 particles + 4 attractors ran at 60 FPS 

Running:
1.  Pressing::
    * 'r' reinitializes the attractors & the particles
    * 'z' zeros out the forces (for as long as it is pressed)
    * Spacebar pauses/plays the simulation
    * 'f' allows you to switch whether the velocity verlet integrator runs in the forward or the backward direction
2.  If you run into performance issues, reduce within ofApp.cpp the number of attractors 'nattractors' & number of particles 'nparticles'
3.  Have fun!
