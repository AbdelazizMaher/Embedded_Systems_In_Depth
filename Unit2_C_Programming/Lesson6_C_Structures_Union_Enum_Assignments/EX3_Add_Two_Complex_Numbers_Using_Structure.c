/*
 * main.c
 *
 *  Created on: July 29, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

struct S_Complex
{
	float Real;
	float Imaginary;
};

struct S_Complex ReadComplex(char num[]);
struct S_Complex SumComplex(struct S_Complex a , struct S_Complex b);
void DiplayComplex(struct S_Complex display);

int main()
{
	struct S_Complex complex1 , complex2 , sum_complex;

	complex1 = ReadComplex("1st");
	complex2 = ReadComplex("2nd");
	sum_complex = SumComplex( complex1 , complex2 );
	DiplayComplex(sum_complex);

    return 0;
}


struct S_Complex ReadComplex(char num[])
{
	struct S_Complex read;

	printf("Enter %s complex number: \n" , num);
	fflush(stdout);

	printf("Enter Real and Imaginary respectively : ");
	fflush(stdout);
	scanf("%f %f",&read.Real , &read.Imaginary);

	return read;
}

struct S_Complex SumComplex(struct S_Complex a , struct S_Complex b)
{
	struct S_Complex sum;

	sum.Real = a.Real + b.Real;
	sum.Imaginary = a.Imaginary + b.Imaginary;

	return sum;
}

void DiplayComplex(struct S_Complex display)
{
	printf("\nsum = %.2f + %.2fi" , display.Real,display.Imaginary );
}
