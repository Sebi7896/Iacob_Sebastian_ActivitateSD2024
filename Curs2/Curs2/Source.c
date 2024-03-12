#include<stdio.h>
#define NULL 0
//int f() {
//	static int x = 10;
//	x++;
//	return x;
//}
int main() {
	//int a = 8;
	//auto b = 9;//ia numai long int
	//int c = a + b;
	//{
	//	int d;
	//	d = c;
	//}
	//printf("Suma este %d\n", c);

	/*register int vreg;
	int d = 8;
	vreg = d;
	printf("vreg %d\n", vreg);
	__asm {
		mov eax, vreg;
	};*/
	/*int j;
	for (int j = 0; j < 10; j++) {
		printf("Rezultat functie f: %d\n", f());
	}*/
	

	//union
	//1 ^Semn * 1,(0000012324) * 2 ^exp()(BIAS + arhitectura)

	//crash daca apelez NULL ,poate fi folosit ca flag
	//funct(int*) ,funct(int), pe care o va alege? -> rezolvare (nullptr C++)
	//const int * valoare (pointer la int constant), int * const valoare(pointer constant la int)
	return 0;
}