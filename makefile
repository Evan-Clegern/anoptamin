FlagsGeneral := -std=c++17 -Wall -Wno-unused-variable
FlagsGCC := -fno-omit-frame-pointer -O2 -rdynamic
FlagsLinkDirs := -L./lib/ -Wl,-rpath=./lib/
FlagsLinkLibs := -L./lib/ -Wl,-rpath=./lib/ -shared -fPIC
FlagsIncludeGL := -I. -I/usr/include/GL -I/usr/include/GLES3

#/usr/include/GLES3
#gl31.h  gl32.h  gl3ext.h  gl3.h  gl3platform.h
#/usr/include/GL
#freeglut_ext.h  glcorearb.h  glu.h     glx.h     glxproto.h
#freeglut.h      glext.h      glut.h    glxint.h  glxtokens.h
#freeglut_std.h  gl.h         glxext.h  glxmd.h


# Packages Required:
# libglew2.2 libglew-dev libsdl2-2.0-0 libsdl2-dev libopengl0 libopengl-dev libgle3 libgle3-dev libgles2

UseSDL2 := -lSDL2
UseOpenGL := -lopengl
UseBase := -lanoptamin_base -lSDL2
UseSDLOps := -lanoptamin_sdlops

.PHONY: all
all: clean test


clean:
	rm -f test

lib/libanoptamin_base.so:
	g++ $(FlagsGeneral) $(FlagsGCC) $(FlagsLinkLibs) source/base.cpp -o lib/libanoptamin_base.so $(UseSDL2)
	
lib/libanoptamin_sdlops.so: lib/libanoptamin_base.so
	g++ $(FlagsGeneral) $(FlagsGCC) $(FlagsLinkLibs) source/sdl.cpp -o lib/libanoptamin_sdlops.so $(UseBase)
	
test: lib/libanoptamin_sdlops.so
	g++ $(FlagsGeneral) $(FlagsGCC) $(FlagsLinkDirs) test.cpp -o test $(UseBase) $(UseSDLOps)

01_Hooked_Closing.out: lib/libanoptamin_sdlops.so
	g++ $(FlagsGeneral) $(FlagsGCC) $(FlagsLinkDirs) 01_Hooked_Closing.cpp -o 01_Hooked_Closing.out $(UseBase) $(UseSDLOps)
