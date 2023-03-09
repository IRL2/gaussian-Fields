# gaussian-Fields

This project build has been successfully built with the following:
1.  visual studio 2019 or Xcode 14
2.  openFrameworks of_v0.11.2_vs2017_release

The way that I built it is as follows:
1.  download from https://openframeworks.cc/download/ the latest windows version of openFrameworks
    (i downloaded of_v0.11.2_vs2017_release.zip, either for windows or Mac depending what you are using)
2.  extract the zip
3.  within the directory of_v0.11.2_vs2017_release, navigate to the directory /examples/math
4.  clone the gaussian-Fields repo so that it sides alongside the other math examples
5.  within the gaussian-Fields repo, open the .sln file (if using VS) or the .xcodeproj file (if using Xcode)
6.  build the project
7.  run the project
8.  if you get a VS error when you try to run, try setting gaussianFields as the single startup project
    a. right click "Solution 'gaussianFields'" in the VS solution explorer
    b. -> Properties
    c. select 'Single Startup Project', and indicate 'gaussianFields'
9.  pressing spacebar reinitializes things; pressing 'f' temporarily zeros out the forces
10. have fun!
