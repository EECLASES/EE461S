

cd ../ && 
rm -rf build &&
cd src &&


gcc -ggdb -o debug ~/Downloads/dup1.c &&
cd .. &&
mkdir build &&
mv src/debug build &&
cd build &&
./debug ls 
