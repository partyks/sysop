#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
	int i = 0;
	double d = 0;
	for(i = 0 ; i < 299999999 ; i++)
	{
		d = sin(3.14);
		d = log(23.3);
		d = exp(5.4) * cos(23.4);
		d = sqrt(d);
		d = d - sin(d);
		d = d / cos(log(45.6));
	}

	return 0;
}
