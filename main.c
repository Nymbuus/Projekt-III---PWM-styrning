/********************************************************************************
* main.c: B�rjar med typisk setup och sen k�rs programmet.
********************************************************************************/
#include "header.h"

int main(void)
{		
	setup();
	
	while(1)
	{
		pwm_run(POT1, 1000);
	}
	
	return 0;
}