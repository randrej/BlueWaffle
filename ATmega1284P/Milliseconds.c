#include "Milliseconds.h"

static volatile unsigned long _milliseconds_counter = 0;


void _milliseconds_init()
{
	//Activate CTC (clear timer on compare) mode on Timer1; datasheet page 136.
	//CLEARBIT(TCCR1A, WGM11);
	//CLEARBIT(TCCR1A, WGM10);
	SETBIT(TCCR1B, WGM12);
	//SETBIT(TCCR1B, WGM13);


	//set clock1 to count from /8 prescaler (CLK_io / 8)
	//CLEARBIT(TCCR1B, CS12);
	SETBIT(TCCR1B, CS11);
	//CLEARBIT(TCCR1B, CS10);

	//Set the counter reset value
	OCR1AH = (TIMER1_RESET_COUNT >> 8);
	OCR1AL = TIMER1_RESET_COUNT;

	//enable timer1 compare_A match interrupt
	SETBIT(TIMSK1, OCIE1A);

	sei(); //enable global interrupts
}


unsigned long _milliseconds()
{
	unsigned long rtn;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		rtn = _milliseconds_counter;
	}
	return rtn;
}

ISR(TIMER1_COMPA_vect)
{
	_milliseconds_counter++;
}
