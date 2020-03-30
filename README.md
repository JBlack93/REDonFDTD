# REDonFDTD

A Tool to propagate EM fields through a 4D space-time grid using
numerical methods with a GUI including real-time visualisation

## Table of contents
* [Getting Started](#getting-started)
 * [Requirements](#requirements)
 * [Building Main Library](#building-main-library)
 * [Building the GUI](#building-the-gui)
* [Features](#features)
 * [Mesh Configuration](#mesh-setup)
 * [Source Configuration](#source-setup)
* [Documentation](#documentation)

## Getting Started
### Requirements

There are very few requirements for this library although very modern
C++ features are utilised, as such you need:

* C++17 Capable Compiler (`gcc 7`, or `clang 5`)
* [Gnuplot](http://www.gnuplot.info/)
* [CMake](https://cmake.org)3.13+
* [qmake-qt5](https://www.qt.io/)

For [documentation](#documentation) generation, you will need
[doxygen](http://www.doxygen.nl/) installed, although there is also a
copy available [here](https://jamesblack.ddns.net/REDonFDTD)

### Building Main Library
To build, one can simply use the
following commands:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX='/desired/install/path'  /path/to/source
make -j $(nproc)   # Unless you're on MacOS, then drop the core # specification -j $(nproc).
make install
```

At this stage one can even run the regression tests which have been
set up with `make test`.

### Building the GUI
The GUI can then be built with your system's `qmake-qt5` (which will vary):

```
mkdir GUIbuild
cd GUIbuild
qmake-qt5 /path/to/REDonFDTDGUI/REDonFDTDGUI.pro
make -j $(nproc) # Again, MacOS, drop the core specification.
```

From here you have the GUI set up, and can run by running the executable: `REDonFDTDGUI`.

## Features

Currently this project is in development. That means there are plenty
of both Physics issues as well as feature requests which have yet to
be built into the project. The most notable of the upcoming additions
is Hardware acceleration in the form of CUDA or OpenCL support. For
now, the GUI should be set up to prevent you from choosing options
which are meant for future releases.

![](images/mainwindow.png)

There is a Graphics View widget in the main window, which is where the
real-time plotting happens. In the main window, there are many (soon
to be supported) options which include changing which plane is
plotted, which component is plotted, and what plotting routine is
used. There is also an option to disable the gnuplot interpolation,
which is on by default, so as to reduce the load produced by the
program as it runs.

Finally, by clicking the stop button during a simulation, one can kill
a simulation (for example, if you have started a simulation which is
too much for your hardware to handle, or simply realised it would take
too long.

![](images/simStopped.png)

By clicking on `Advanced`, a new window will appear which allow you to
specify many parameters to set up [the mesh](#mesh-setup) and [the
sources](source-setup) however you want.

### Mesh Setup
![](images/meshconfig.png)

Inside the mesh tab window there are many options: this includes the
number of steps in the simulation, the dimensions of the mesh (x,y,z),
and the timestep- which itself sets the grid spacing. You can even
apply a constant external field. In the future there will be support
to load a mesh in and begin a simulation where it left off, as well as
alternative boundary conditions.

### Source Setup
![](images/sourceconfig.png)

This source configuration window is the UI to the magic of the
REDonFDTD library. There is an abstract source class, from which all
sources are derived. This means that we can use a factory method in
producing these sources in the mesh, and therefore choose which source
to input into the mesh and run the code simply and easily. Currently
you have the option of a particle (defaults as a proton, for now) and
a basic ricker source.

Inside this tab of the option window, there is the option to change
the starting position, velocity and acceleration of the source. You
can also modify how large of a range around the source you wish to
calculate analytically (large number: slower computation, small
number: more numerical artifacts). In the future there will be support
for other particle tracking algorithms, such as Runge-Kutta. If the
ricker source is selected inside the drop-down box, an extra option
appears, which is the points-per-wave of the ricker source itself.


## Documentation

Documentation for the physics and concepts can found in the docs
folder in the form of my Master's Thesis. Documentation for the code
itself is provided in the form of Doxygen, and is currently only
available for the main library, not for the GUI. This can be built by
navigating to the docs folder and running:

```
cd docs
cd doxygen
doxygen Doxyfile.in
xdg-open html/index.html
```

A version of this (although likely not the latest) is also [hosted
here](https://jamesblack.ddns.net/REDonFDTD)