cd build
del /q *.*
cmake -G "MinGW Makefiles" ../
cmake --build .
pause