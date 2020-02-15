

cd ../ && 
rm -rf build &&
cd src &&


gcc -ggdb -o debug yash.c functions.c &&
cd .. &&
mkdir build &&
mv src/debug build &&
cd build &&
gdb debug
