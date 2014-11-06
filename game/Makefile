deppath=../deps/

CC=g++ -std=c++11 -g
CXX=g++ -std=c++11 -g

#SDL2Libs=$(shell sdl2-config --libs)
SDL2Libs=-lSDL2 -lGL -lGLU -lGLEW
#SDL2Libs+= -lSDL2_image

CLLibs=-lOpenCL -lGLU

CLInclude=-I../deps/openCL/

LibPath=-L/usr/lib/ -L/usr/local/lib/
IncPath=$(CLInclude) -I. -I/usr/local/include/

Libs=$(SDL2Libs)
#Libs+=$(CLLibs) -lcurl

filedir=generator
OBJDIR=build

files=$(addprefix generator/, generator.cpp clengine.cpp shader_util.cpp physicsengine.cpp)
___test=$(addprefix $(OBJDIR)/, test.o )
___objs=$(addprefix $(OBJDIR)/, main.o game.o)
utl_objs=$(addprefix $(OBJDIR)/, sdlutil.o)
spw_objs=$(addprefix $(OBJDIR)/, sparseworld.o)
obj_objs=$(addprefix $(OBJDIR)/, object.o renderable.o viewport.o)
glm_objs=$(addprefix $(OBJDIR)/, shader_util.o objloader.o objmodel.o glengine.o glmanager.o glprogrambase.o basicrenderer.o)
itf_objs=$(addprefix $(OBJDIR)/, ) #interface.o)

objects=$(___objs) $(utl_objs) $(spw_objs) $(obj_objs) $(glm_objs) $(itf_objs)
#objects+= $(cle_objs) $(obj_objs) $(wld_objs) $(txm_objs)
testObjects=$(___test) $(utl_objs) $(spw_objs) $(obj_objs) $(glm_objs) $(itf_objs)
#testObjects+= $(cle_objs) $(obj_objs) $(wld_objs) $(txm_objs) 

all:	executable

debug: clean
debug: CXX += -g
debug: CC += -g
debug: executable

executable: $(objects)
	$(CC) $^ -o sdl-app $(LibPath) $(Libs)

test: $(testObjects)
	$(CC) $^ -o test-app $(LibPath) $(Libs)


$(itf_objs): $(OBJDIR)/%.o: interface/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(txm_objs): $(OBJDIR)/%.o: texturemanager/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(spw_objs): $(OBJDIR)/%.o: sparseworld/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(glm_objs): $(OBJDIR)/%.o: glmanager/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(obj_objs): $(OBJDIR)/%.o: object/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(utl_objs): $(OBJDIR)/%.o: util/%.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(___objs): $(OBJDIR)/%.o: %.cpp
	$(CC) -c $< -o $@ $(IncPath)
$(___test): $(OBJDIR)/%.o: %.cpp
	$(CC) -c $< -o $@ $(IncPath)


clean:
	rm -Rf *.o sdl-app test-app
	rm -Rf build/*

setup:
	sudo ./run.sh
