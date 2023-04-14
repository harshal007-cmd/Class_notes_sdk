#include<stdio.h>
#using <MSCorLib.dll>
using namespace System;

int main(void)
{
	printf("This line is from Native CPP...\n");
	Console::WriteLine("This line is from DOT NET managed CPP..\n");
	return 0;
}

