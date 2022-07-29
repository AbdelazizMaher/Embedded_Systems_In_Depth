/*
 * main.c
 *
 *  Created on: July 29, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

struct Sdistance
{
	int feet;
	float inch;
};

struct Sdistance ReadDistance(char num[]);
struct Sdistance SumDistance(struct Sdistance a , struct Sdistance b);
void DiplayDistance(struct Sdistance display);

int main()
{
	struct Sdistance dist1 , dist2 , sumdist;

	dist1 = ReadDistance("1st");
	dist2 = ReadDistance("2nd");
	sumdist = SumDistance( dist1 , dist2 );
	DiplayDistance(sumdist);

    return 0;
}

struct Sdistance ReadDistance(char num[])
{
	struct Sdistance read;

	printf("Enter information for %s distance: \n" , num);
	fflush(stdout);

	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d",&read.feet);

	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&read.inch);

	return read;
}

struct Sdistance SumDistance(struct Sdistance a , struct Sdistance b)
{
	struct Sdistance sum;

	sum.feet = a.feet + b.feet;
	sum.inch = a.inch + b.inch;

	while( sum.inch >= 12)
	{
		sum.inch -= 12;
		sum.feet++;
	}

	return sum;
}

void DiplayDistance(struct Sdistance display)
{
	printf("\nTotal Distance =  %d\' %.2f" , display.feet , display.inch );
}
