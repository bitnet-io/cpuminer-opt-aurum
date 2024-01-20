# SSE2
make clean || echo clean
rm -f config.status
CFLAGS="-O3 -msse2 -Wall -fno-common" ./configure --with-curl
make -j 8
strip -s cpuminer
mv cpuminer cpuminer-sse2
