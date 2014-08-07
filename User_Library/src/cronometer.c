#include "cronometer.h"

void init_cronometer(void)
{
	CronoTime = 0;
	CTIME.HOURS = 0;
	CTIME.MINUTES = 0;
	CTIME.SECONDS = 0;
	CTIME.MILISECONDS = 0;
	CTIME.MICROSECONDS = 0;
}
/*
	@brief 
*/
void cronometer(void)
{
	if(FLAG_CRONO) // if the cronometer is activated 
	{
		CronoTime++;
		if(CronoTime<1000)
		{
			CTIME.MICROSECONDS = CronoTime;			
		}
		else
		{
			CronoTime = 0;
			CTIME.MICROSECONDS = 0;
			if(CTIME.MILISECONDS<1000)
			{
				CTIME.MILISECONDS = 1 + CTIME.MILISECONDS; //Counting Miliseconds
			}
			else  
			{
				CTIME.MILISECONDS = 0;  // Reset Miliseconds
				if(CTIME.SECONDS < 60)
				{
					CTIME.SECONDS = 1 + CTIME.SECONDS; // Counting Seconds
				}
				else
				{
					CTIME.SECONDS = 0;  // Reset Seconds
					if(CTIME.MINUTES < 60)
					{
						CTIME.MINUTES = 1 + CTIME.MINUTES; // Counting Minutes
					}
					else
					{
						CTIME.MINUTES = 0; // Reset Minutes
						if(CTIME.HOURS < ErrorTime ) 
						{
							CTIME.HOURS = 1+ CTIME.MINUTES;
						}
					}
				}
			}
		}
	}
}

void start_cronometer(void)
{
		FLAG_CRONO = 1;
}

void stop_cronometer(void)
{
		FLAG_CRONO = 0;
}

crono_time get_cronometer_fulltime(void)
{
		return CTIME;
}

uint8_t	get_cronometer_hours(void)
{
		return CTIME.HOURS;
}
uint8_t	get_cronometer_minutes(void)
{
		return CTIME.MINUTES;
}

uint8_t	get_cronometer_seconds(void)
{
		return CTIME.SECONDS;
}

uint16_t	get_cronometer_miliseconds(void)
{
		return CTIME.MILISECONDS;
}

uint16_t get_cronometer_microseconds(void)
{
		return CTIME.MICROSECONDS;
}
