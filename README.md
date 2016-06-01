# coding-puzzles
g++ -g -o missing missing-integer.cpp
gdb ./missing
b missing-integer.cpp:##
r ./missing
c
s
