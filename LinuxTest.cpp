//============================================================================
// Name        : LinuxTest.cpp
// Author      : xieliming
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "linux.h"
#include <iostream>
using namespace std;
using namespace xlm;
int main(int argc,char** argv)
{
	int srcval[]={5,1,9,0,2,3,1};
	int *p=srcval;
//	xlm::quicksort<int>(p,0,6);
	xlm::insertsort<int>(p,7);
	for(int i=0;i<7;++i)
		printf("%d\n",*(srcval+i));
	return 0;
}
