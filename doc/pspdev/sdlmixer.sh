cd ..

cd SDL_mixer

./autogen.sh

LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" \	  
	     ./configure --host psp --with-sdl-prefix=$(psp-config --psp-prefix) \
	     --disable-music-mp3 --prefix=$(psp-config --psp-prefix) \
	     --disable-music-libmikmod --enable-music-mod

make clean

make

make install 
