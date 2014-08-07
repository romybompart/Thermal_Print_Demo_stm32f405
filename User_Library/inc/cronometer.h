#ifndef __CRONOMETER_H
#define	__CRONOMETER_H

#include "Delay.h"

static __IO uint32_t CronoTime;
static __IO uint8_t FLAG_CRONO=0;

typedef struct
{
	uint8_t HOURS;
	uint8_t MINUTES;
	uint8_t SECONDS;
	uint16_t MILISECONDS;
	uint16_t MICROSECONDS;
}crono_time;

static 	crono_time  CTIME;
static  uint8_t ErrorTime = 2;

extern void init_cronometer(void);
extern void start_cronometer(void);
extern void stop_cronometer(void);
extern void cronometer(void);
extern crono_time get_cronometer_fulltime(void);
extern uint8_t	get_cronometer_hours(void);
extern uint8_t	get_cronometer_minutes(void);
extern uint8_t	get_cronometer_seconds(void);
extern uint16_t	get_cronometer_miliseconds(void);
extern uint16_t get_cronometer_microseconds(void);

#endif

