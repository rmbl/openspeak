================
openSpeak Readme
================

About:
======

*openSpeak* is a VoIP tool similar to Mumble or TeamSpeak consisting of a
simple Client-/Serverarchitecture. It uses Speex as the codec to encode speech.

This is a rewrite of the original *openSpeak* codebase done to clean up the codebase,

Status:
=======

This codebase is nowhere near the state of the older one. There is no real usability
and the client and server executables are basically just tests of the underlying 
libraries.

Dependencies:
=============

To build *openSpeak* you currently only need **Boost >= 1.39** apart from a C++ 
compiler and autoconf/automake/... or cmake.

Installation:
=============

Autoconf/Automake:
------------------

Use ``./autogen.sh`` to create and run the configure script. Any options you would 
normally supply to the configure script can be supplied to the autogen.sh script.
A simple ``make`` compiles *openSpeak* after that and ``make install`` puts 
everything into your prefix.

CMake:
------

See cmake --help for available generators. If you just want to generate standard makefiles use ``cmake .``, otherwise use ``cmake -G <generator> .``.
Load the created files with your IDE or use ``make`` to compile *openSpeak*.
Using Makefiles, ``make install`` installs everything.

Copyright:
==========

*openSpeak* is released under the terms of the GPL and is Copyright (c) 2006-2009 
The openSpeak Team.
