#!/bin/sh

export LD_LIBRARY_PATH=./deps/glew-1.7.0/lib/:./deps/glew-1.10.0/lib/:./deps/SFML-2.1/lib:./deps/jpeg-8/.libs && ./game/sdl-app
export LD_LIBRARY_PATH=./deps/glew-1.7.0/lib/:./deps/glew-1.10.0/lib/:./deps/SFML-2.1/lib:./deps/jpeg-8/.libs && ./game/sfml-app
