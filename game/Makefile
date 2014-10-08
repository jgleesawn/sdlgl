deppath=../deps/

CC=g++
CXX=g++

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

filedir=generator
OBJDIR=build

objects=$(addprefix $(OBJDIR)/, generator.o clengine.o shader_util.o physicsengine.o object.o)


CPPFLAGS=$(IncPath)
CFLAGS=$(IncPath)

all:	executable

debug: clean
debug: CXX += -g
debug: CC += -g
debug: executable

executable: $(objects) main.o
	$(CC) $^ -o sfml-app $(LibPath) $(Libs)

$(OBJDIR)/%.o: $(filedir)/%.cpp
	$(CC) -c $< -o $@ $(IncPath)

clean:
	rm -Rf *.o sfml-app
	rm -Rf */*.o

setup:
	sudo ./run.sh
