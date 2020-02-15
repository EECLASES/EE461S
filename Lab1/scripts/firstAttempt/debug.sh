

cd ../ && 
rm -rf build &&
cd src &&


gcc -ggdb -o debug main.c &&
cd .. &&
mkdir build &&
mv src/debug build &&
cd build &&
gdb debug
