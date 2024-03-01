#include<stdio.h>

int main() {
	int a = 8;
	auto b = 9;
	int c = a + b;
	{
		int d;
		d = c;
	}

	printf("Suma este %d\n", c);


	return 0;
}