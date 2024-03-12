#include<stdio.h>
#include<string.h>
#include<stdarg.h>
//int* (*fp[5])(char*)

double sumaArgumentatavariabila(int nr, ...) {
	va_list ap;
	int i;
	double suma = 0;
	va_start(ap, nr);
	for (i = 0; i < nr; i++) {
		suma += va_arg(ap, double);
	}
	va_end(ap);
	return suma;
}
int main() 
{
	//pointer ct la int
	int i = 7,j = 10;
	int* const pi = &i;
	printf("\nAdresa(pi) = %p,Continut = %p\n", &pi, pi);
	//pi = &j;

	//pointer la int ct
	int const* pint, l = 7;
	pint = &i;
	printf("\nAdresa(pint) = %p,Continut = %p\n", &pint, pint);
	//pint = 10;
	printf("\nAdresa(pint) = %p,Continut = %p\n", &pint, pint);


	//pointer constant la int constant
	const int* const pint2 = &i;//trebuie initializat
	printf("\nAdresa(pint2) = %p,Continut = %p\n", &pint2, pint2);
	
	double c = sumaArgumentatavariabila(3, 1.2f, 2.34f, 5.64f);//3
	printf("Suma este %f", c);

	double c1 = sumaArgumentatavariabila(2, 1.2f, 2.34f);//2
	printf("\nSuma este %f", c1);
	
	return 0;
}