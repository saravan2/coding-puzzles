#include<iostream>
#include<limits>
#include<math.h>
int main() {
	int ntemp = 5;
	std::cout << "floor " << floor(ntemp/2.0) << std::endl;
	std::cout << "ceil " << ceil(ntemp/2.0) << std::endl;
	ntemp = std::numeric_limits<int>::min(); 
	std::cout << "Int min : " << ntemp << std::endl;
//	std::cout << "Int min * -1 : " << (ntemp * -1) << std::endl;
	ntemp++;
//	std::cout << "ntemp++ : " << ntemp << std::endl;	
	ntemp = ntemp * std::numeric_limits<int>::max();
	std::cout << "ntemp * -3 : " << ntemp << std::endl;	
	std::cout << "Int max : " << std::numeric_limits<int>::max() << std::endl;
	return 0;
}
