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

IncPath=-I./ $(SFMLIncludePath) $(CLINCLUDE)
LibPath=$(SFMLLibPath) $(GLEWLibPath) $(LIBJPEGPath)

Libs=$(GLLibs) $(SFMLLibs) $(CLLIBS)

filedir=generator
OBJDIR=build

files=$(addprefix generator/, generator.cpp clengine.cpp shader_util.cpp physicsengine.cpp)
gen_objs=$(addprefix $(OBJDIR)/, generator.o generatorengine.o)
cle_objs=$(addprefix $(OBJDIR)/, shader_util.o clengine.o physicsengine.o)
___objs=$(addprefix $(OBJDIR)/, main.o)
objects=$(gen_objs) $(cle_objs) $(___objs)


CPPFLAGS=$(IncPath)
CFLAGS=$(IncPath)

all:	executable

debug: clean
debug: CXX += -g
debug: CC += -g
debug: executable

executable: $(objects)
	$(CC) $^ -o sfml-app $(LibPath) $(Libs)

$(gen_objs): $(OBJDIR)/%.o: generator/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(cle_objs): $(OBJDIR)/%.o: clengine/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(___objs): $(OBJDIR)/%.o: %.cpp
	$(CC) -c $< -o $@ $(IncPath)

clean:
	rm -Rf *.o sfml-app
	rm -Rf build/*

setup:
	sudo ./run.sh
