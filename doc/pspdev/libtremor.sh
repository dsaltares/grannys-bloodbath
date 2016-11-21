cd ..

cd libTremor

LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./autogen.sh \
     --host psp --prefix=$(psp-config --psp-prefix)
     
make clean

make

make install
