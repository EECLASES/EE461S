

cd ../ && 
rm -rf build &&
cd src &&


gcc -ggdb -o yashMain yash.c functions.c &&
cd .. &&
mkdir build &&
mv src/yashMain build &&
cd build &&
./yashMain
