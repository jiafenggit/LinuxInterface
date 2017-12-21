//============================================================================
// Name        : LinuxInterface.cpp
// Author      : xieliming
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "linux.h"
using namespace std;

int main()
{
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	char c[]="87";
//	int z=strtol(c,NULL,16);
//	printf("%x\n",z);
//	int data[9][100];
//	printf("sizeof(data):%d\n",sizeof(data));
//	data[0][1]=1;
//	data[0][1]++;
//	printf("%d\n",data[0][1]);
//
	struct tm tval;
	memset(&tval,0,sizeof(struct tm));
	tval.tm_year=2019-1900;
	tval.tm_mon =9-1;
	tval.tm_mday=1;
	tval.tm_hour=11;
	tval.tm_min=11;
	tval.tm_sec=11;
	xlm::setBiosTime(&tval);
	return 0;
}
