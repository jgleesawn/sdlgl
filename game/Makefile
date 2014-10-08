deppath=../deps/

SFMLIncludePath=-I./$(deppath)/SFML-2.1/include
SFMLLibPath=-L./$(deppath)/SFML-2.1/lib

CLINCLUDE=-I./$(deppath)/openCL/
CLLIBS=-lOpenCL

GLEWLibPath=-L./$(deppath)/glew-1.7.0/lib
LIBJPEGPath=-L./$(deppath)/jpeg-8/.libs

SFMLLibs=-lsfml-graphics -lsfml-window -lsfml-system -ljpeg
GLLibs=-lGL -lGLEW -lGLU

IncPath=$(SFMLIncludePath) $(CLINCLUDE)
LibPath=$(SFMLLibPath) $(GLEWLibPath) $(LIBJPEGPath)

Libs=$(GLLibs) $(SFMLLibs) $(CLLIBS)

FILES= main.cpp generator.cpp clengine.cpp shader_util.cpp physicsengine.cpp object.cpp
OBJS= main.o generator.o clengine.o shader_util.o physicsengine.o object.o

all:	clean objs
	g++ $(OBJS) -o sfml-app $(LibPath) $(Libs)

debug: clean objs
	g++ -g $(OBJS) -o sfml-app $(LibPath) $(Libs)

objs:
	g++ -c $(FILES) $(IncPath)

clean:
	rm -Rf *.o sfml-app

setup:
	sudo ./run.sh
