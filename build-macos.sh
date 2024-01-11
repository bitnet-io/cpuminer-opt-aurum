#!/bin/bash

#if [ "$OS" = "Windows_NT" ]; then
#    ./mingw64.sh
#    exit 0
#fi

# Linux build

make distclean || echo clean
rm -f config.status
./autogen.sh || echo done

#CFLAGS="-O3 -march=native -Wall" ./configure --with-curl --with-crypto=$HOME/usr
#CPPFLAGS="-I/usr/local/opt/openssl@3/include -I/usr/local/opt/gmp/include -I/usr/local/opt/zlib/include -I/usr/local/opt/jansson/include" LDFLAGS="-L/usr/local/opt/jansson/lib -L/usr/local/opt/zlib/lib -L/usr/local/opt/openssl@3/lib -L/usr/local/opt/gmp/lib -Lyes/lib" 




#	CFLAGS="-O3 -march=native -Wall" ./configure --with-crypto=/usr/local/opt/openssl \
#        --with-curl=/usr/local/opt/curl


./nomacro.pl
#        CFLAGS="-march=native -O3 -Wall -DNOASM " ./configure --with-crypto=/usr/local/opt/openssl --with-curl=/usr/local/opt/curl
        CFLAGS="-march=native -O2 -Wall -Ofast -flto -DNOASM " ./configure --with-crypto=/usr/local/opt/openssl --with-curl=/usr/local/opt/curl
    make -j4
    strip cpuminer
    exit 0


make -j 4

strip -s cpuminer
