deppath=../deps/

CC=g++ -std=c++11
CXX=g++ -std=c++11

#SDL2Libs=$(shell sdl2-config --libs)
SDL2Libs=-lSDL2
SDL2Libs+= -lSDL2_image

LibPath=-L/usr/lib/ -L/usr/local/lib/
IncPath=-L/usr/local/include/

Libs=$(SDL2Libs)

filedir=generator
OBJDIR=build

files=$(addprefix generator/, generator.cpp clengine.cpp shader_util.cpp physicsengine.cpp)
obj_objs=$(addprefix $(OBJDIR)/, sprite.o)
wld_objs=$(addprefix $(OBJDIR)/, world.o worldengine.o)
gen_objs=$(addprefix $(OBJDIR)/, generator.o generatorengine.o)
cle_objs=$(addprefix $(OBJDIR)/, shader_util.o clengine.o physicsengine.o)
___objs=$(addprefix $(OBJDIR)/, main.o)
objects=$(___objs) $(obj_objs)


all:	executable

debug: clean
debug: CXX += -g
debug: CC += -g
debug: executable

executable: $(objects)
	$(CC) $^ -o sdl-app $(LibPath) $(Libs)

$(obj_objs): $(OBJDIR)/%.o: object/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(wld_objs): $(OBJDIR)/%.o: world/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(gen_objs): $(OBJDIR)/%.o: generator/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(cle_objs): $(OBJDIR)/%.o: clengine/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(___objs): $(OBJDIR)/%.o: %.cpp
	$(CC) -c $< -o $@ $(IncPath)

clean:
	rm -Rf *.o sdl-app
	rm -Rf build/*

setup:
	sudo ./run.sh
