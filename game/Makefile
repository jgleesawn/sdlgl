deppath=../deps/

SFMLIncludePath=-I./$(deppath)/SFML-2.1/include
SFMLLibPath=-L./$(deppath)/SFML-2.1/lib

GLEWLibPath=-L./$(deppath)/glew-1.7.0/lib
LIBJPEGPath=-L./$(deppath)/jpeg-8/.libs

SFMLLibs=-lsfml-graphics -lsfml-window -lsfml-system -ljpeg
GLLibs=-lGL -lGLEW -lGLU

IncPath=$(SFMLIncludePath)
LibPath=$(SFMLLibPath) $(GLEWLibPath) $(LIBJPEGPath)

Libs=$(GLLibs) $(SFMLLibs)

all:	clean main.o
	g++ main.o -o sfml-app $(LibPath) $(Libs)
main.o:
	g++ -c main.cpp $(IncPath)

clean:
	rm -Rf *.o sfml-app
