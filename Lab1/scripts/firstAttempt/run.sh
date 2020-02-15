

cd ../ && 
rm -rf build &&
cd src &&


gcc -ggdb -o main main.c &&
cd .. &&
mkdir build &&
mv src/main build &&
cd build &&
./main
