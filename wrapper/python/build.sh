#!/bin/sh

export LD_LIBRARY_PATH=/home/edm/Downloads/git/try/genesis/wrapper/python/lib:$LD_LIBRARY_PATH

rm -rf lib
mkdir lib 

cp -rf ../../build/genesis/libgenesis.so .
clang++ -c -fPIC proxy_genesis.cxx -o proxy_genesis.o -I../../
clang++ -shared -Wl,-soname,libproxy_genesis.so -o libproxy_genesis.so proxy_genesis.o libgenesis.so

rm *.o
mv *.so lib

python genesis.py

