

cd ../ && 
rm -rf build &&
cd src &&


gcc -o main main.c &&
cd .. &&
mkdir build &&
mv src/main build &&
cd build &&
./main
