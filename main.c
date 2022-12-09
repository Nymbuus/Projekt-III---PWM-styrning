/********************************************************************************
* main.c: Börjar med typisk setup och sen körs programmet.
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