# coding-puzzles
g++ -g -o missing missing-integer.cpp

gdb ./missing

b missing-integer.cpp:##

r ./missing

c

s

To view STL containers, include the custom ./gdbinit file present in the working directory

gdb -iex "set auto-load safe-path /<pwd>/" ./powerset.exe


Breakpoint 1, recursivePowerSet (iset=..., sofar=..., pos=2) at powerSet.cpp:25
25                      stringstream elm;
(gdb) p sofar
$3 = {
  static npos = <optimized out>,
  _M_dataplus = {
    <std::allocator<char>> = {
      <__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>},
    members of std::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Alloc_hider:
    _M_p = 0x60004b188 "1,2"
  }
}
