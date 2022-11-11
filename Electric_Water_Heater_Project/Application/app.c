/************************************************************************/
/*                         Application.c                                */
/*
* APP_INIT();
* APP_START();
*/
/************************************************************************/
/************************************************************************/
/*                          Needed files                                */
#include "app.h"
/************************************************************************/


/************************************************************************/
/*                   Static Function Prototype                          */
/*
* All of this functions will be used only in this file that is why they 
* are defined as static
*/

/*                     Off Mode Functions prototypes                    */
/*offMode function is the function that will be running in off mode*/
static void OffMode(void);

/*                     On Mode Functions prototypes                     */
/*onMode function is the function that will be running in on mode*/
static void OnMode(void);
/*TempSense used to get the current temperature based on the last 10 readings*/
static f32 TempSense(void);


/*             Temperature Setting Functions prototypes                 */
/*setState function is the function that will be running in set mode*/
static void setState(void);
/*SevenSegmentBlink to blink the Seven segment in setting mode*/
static void SevenSegmentBlink(void);
/************************************************************************/


/************************************************************************/
/*                        Global variables                              */
/*state while be the switch value*/
u8 state = OFF;  
/*prevState will hold where i come from (on mode , off mode or set mode)*/
u8 prevState = 0 ;
/*timerFlag the flag of the timer to control the delay*/
u8 timerFlag = 0;
/*counterFlag counter flag to control the wait*/
u8 counterFlag = 0;
/*currentTemp to hold the readings of LM35*/
f32 currentTemp = 0;
/*setTemp holds the initial value of the set temperature*/
u8 setTemp = INITIAL_SET_TEMP;
/************************************************************************/


/************************************************************************/
/* APP_init(void) function is where we initialize every hardware and    */
/*                 peripheral we need in the project                    */
void APP_init(void)
{
	/*In Water Heater Project we have */
	
	/*          Interrupt               */
	interrupt_init(EX_INT0,FALLING_MODE);  /*Up Button as Interrupt 0*/
	interrupt_init(EX_INT1,FALLING_MODE);  /*Down Button as Interrupt 1*/
	interrupt_init(EX_INT2,FALLING_MODE);  /*Off/On Button as Interrupt 2*/
	
	/*          Timer                  */
	timer0_init(OVERFLOW_MODE);     /*timer 0 set as Overflow timer*/
	timer0_interrupt(OVERFLOW_MODE);   /*to allow timer interrupt*/
	
	/*          Button                 */
	/* UP Button is Pull up */
	PB_init(D,2,PULL_UP);
	/* Down Button is Pull up */  
	PB_init(D,3,PULL_UP);
	/* ON/OFF Button is Pull up */
	PB_init(B,2,PULL_UP);
	
	/*          7 Segment               */
	Seven_segment_init(A,LSB); 
	Seven_segment_init(B,MSB);
	
	/*          EEPROM                  */
	EEPROM_init();
 	EEPROM_WRITE(ADDRESS,setTemp);
 	_delay_ms(10);
	
	/*               Heater             */
	HEAT_INIT();
	COOL_INIT();
	State_led_INIT();
	/*          Temp Sensor            */
	LM35_init(A,ADC7);
	
	
}
/************************************************************************/


/************************************************************************/
/* APP_start(void) function is where we put our super loop which contain*/
/*                      the flow of our project                         */
void APP_start(void)
{
	/*Enter Super Loop*/
	while(1)
	{
		/*switch on the state*/
		switch (state)
		{
			case OFF:
			/*state = OFF*/
			OffMode();   /*OffMode function*/
			break;  /*to get out of switch*/
			case ON:
			/*state = ON*/
			OnMode();   /*OnMode function*/
			break;  /*to get out of switch*/
			case SET:
			/*state = SET*/
			setState();  /*setState*/
			break;  /*to get out of switch*/
			default:
			/*state = anything else*/
			state = OFF;  
			break; /*to get out of switch*/
		}
	}
}
/************************************************************************/

/************************************************************************/
/*                          Off mode Functions                          */
static void OffMode(void)
{
	/*disable interrupt as there is no way to enter setting mode without system is on first*/
	interrupt_disable(EX_INT0);
	interrupt_disable(EX_INT1);
	prevState = OFF;   /*set prevState by current state*/
	/*stop every hardware or display in the project*/
	HEAT_STOP();
	COOL_STOP();
	State_led_stop();
	Seven_segment_disable(UNIT);
	Seven_segment_disable(TENS);
}
/************************************************************************/




/************************************************************************/
/*                           On mode Functions                          */
/************************************************************************/


/************************************************************************/
/*                           On mode Function                           */
static void OnMode(void)
{
	u8 savedTemp = 0;
	/*enable interrupt*/
	interrupt_enable(EX_INT0);
	interrupt_enable(EX_INT1);
	/*find if the prevState is Off state or it was set*/
	if (prevState == OFF)
	{
		/*if it was off state then we get the saved value in the EEPROM*/
		EEPROM_READ(ADDRESS,&savedTemp);
	}
	else
	{
		/*if it was not off state the it is the setTemp value*/
		savedTemp = setTemp;
	}
	prevState = ON;  /*set prevState by current state*/
	f32 temp = 0.0;
	/*get the average of the last 10 LM35 Readings*/
	temp = TempSense();
	/*Display the Value on Seven Segment*/  
	SevenSegmentWriteFloat(A,LSB,ceil(temp));
	SevenSegmentWriteFloat(B,MSB,ceil(temp));
	/*find if the Temperature is less the set temperature by 5 or not*/
	if ((temp - savedTemp) > 5)
	{
		/*if current Temperature is larger than set temperature 
		then cooler will be on and heater will be on*/
		HEAT_STOP();
		COOL_START();
	}
	else if ((savedTemp - temp) > 5)
	{
		/*if current temperature is less than the set temperature then
		cooler will be off and heater will be on*/
		COOL_STOP();
		HEAT_START();
	}
	else
	{
		/*if the difference in any case less than 5 then we are in range everything will
		be off */
		COOL_STOP();
		HEAT_STOP();
		State_led_stop();
	}
	/*check what is on*/
	if (getState()==HEAT_ON)
	{
		/*if heater was on then toggle the state led for 1000 ms*/
		State_led_tog();
	}
	else if (getState()==COOL_ON)
	{
		/*if cooler was on then state led is on*/
		State_led_start();
	}
	else
	{
		/*do nothing*/
	}
}
/************************************************************************/

/************************************************************************/
/*                 Temperature sensing function                         */
static f32 TempSense(void)
{
	f32 temp = 0.0 ;
	f32 readings[SIZE];  /*to save the last 10 readings of LM35*/
	u8 i = 0;
	/*loop to stuck in for 10 times till the array is full*/
	for (i = 0 ; i < SIZE ; i++)
	{
		/* timer calculation  
		(256/10^6) * 10*3 * 2^8 = 65.536ms  
		number of overflow = 100ms/65.536ms = 1.5258 then 2 overflows
		initial value = 2^8 - (100ms/0.256)/2 = 60.6875 = 61 */
		timer0_start(PRE256);  /*start timer*/
		timer0_intial_val(READ_VALUE);  /*set initial timer value*/
		while(timerFlag != ON_NUM_OVERFLOWS);  // wait for 100ms
		readings[i] = currentTemp; /*save the current Temperature */
		timer0_stop();   /*stop timer*/
		timerFlag = 0; 
	}
	/*to get sum of the last 10 readings*/
	for (i = 0 ; i < SIZE ; i++)
	{
		temp = temp + readings[i];
	}
	/*to get the average*/
	temp = temp / SIZE ;
	/*return the average*/
	return temp;
}
/************************************************************************/










/************************************************************************/
/*                      Temperature Setting Functions                   */
/************************************************************************/


/************************************************************************/
/*                   Setting Temperature state Function                 */
static void setState(void)
{
	u8 temp = 0 ;
	/*Enter a Super loop */
	while(1)
	{
		/*get the saved temperature*/
		EEPROM_READ(ADDRESS,&temp);
		/*check if the saved temperature is the set temperature*/
		if (temp == setTemp)
		{
			/*if they are equal then increase the counter flag*/
			counterFlag++;
		}
		else
		{
			/*do nothing*/
		}
		/*check on the counter flag value*/
		if (counterFlag > 5)
		{
			/*if it is > 5 then break the super loop */
			break;
		}
		else
		{
			/*if not*/
			/*start the timer then set initial value*/
			/*timer calculation
			(1024/10^6)*10^3*2^8 = 262.144
			1000/262.144 = 3.8146 then 4 overflows 
			initial value = 2^8 - (1000/1.024)/4 = 11.859 = 12*/
			/*start timer and set initial value*/
			timer0_start(PRE1024);
			timer0_intial_val(SET_INTIAL_VALUE);
			/*write the value of the set temperature in EEPROM*/
			EEPROM_WRITE(ADDRESS,setTemp);
			/*blink seven segment*/
			SevenSegmentBlink();
			/*wait for 1 second and we use counter flag to do this 5 times */
			while(timerFlag != SET_NUM_OVERFLOWS);
			timer0_stop();  /*stop timer*/
			timerFlag = 0;
		}
	}
	/*set state back to ON*/
	state = ON;
}
/************************************************************************/


/************************************************************************/
/*                   Seven Segment Blink Function                       */
static void SevenSegmentBlink(void)
{
	/*prev is static to keep its value even after the function*/
	static u8 prev = 0;
	/*check on prev*/
	if (prev == 1)
	{
		/*if it is equal 1 then this is the second timer we enter this function*/
		/*stop seven segment*/
		Seven_segment_disable(UNIT);
		Seven_segment_disable(TENS);
		/*set prev to zero*/
		prev = 0 ;
	}
	else
	{
		/*then this is the first time we visit this function so we display the value of the 
		seven segment*/
		SevenSegmentWriteFloat(A,LSB,setTemp);
		SevenSegmentWriteFloat(B,MSB,setTemp);
		/*set prev to zero*/
		prev = 1 ;
	}
}
/************************************************************************/




/************************************************************************/
/*                                ISRs                                  */
/************************************************************************/


/************************************************************************/
/*                           Up Button ISR                              */
ISR (EXT_INT0_VECT)
{
	/*check on state*/
	if (state != SET)
	{
		/*if state was not equal SET then this is the first interrupt
		then set state to SET*/
		state = SET;
	}
	else
	{
		/*then we pressed the button in setting mode*/
		/*we check if the setTemp value is larger than or equal 75*/
		if (setTemp >= 75)
		{
			/*if yes the put it by 75*/
			setTemp = 75 ;
		}
		else
		{
			/*if no then increase it by 5*/
			setTemp = setTemp + 5 ;
		}
	}
	/*but both timerFlag and counterFlag equal zero*/
	timerFlag = 0;
	counterFlag = 0;
}
/************************************************************************/


/************************************************************************/
/*                         DOWN Button ISR                              */
ISR (EXT_INT1_VECT)
{
	/*check on state*/
	if (state != SET)
	{
		/*if state was not equal SET then this is the first interrupt
		then set state to SET*/
		state = SET;
	}
	else
	{
		/*then we pressed the button in setting mode*/
		/*we check if the setTemp value is smaller than or equal 35*/
		if (setTemp <= 35)
		{
			/*if yes the put it by 35*/
			setTemp = 35 ;
		}
		else
		{
			/*if no then decrease it by 5*/
			setTemp = setTemp - 5 ;
		}
	}
	/*but both timerFlag and counterFlag equal zero*/
	timerFlag = 0;
	counterFlag = 0;
}
/************************************************************************/


/************************************************************************/
/*                        ON/OFF Button ISR                             */
ISR (EXT_INT2_VECT)
{
	/*check on state*/
	if (state == OFF)
	{
		/*if Off make it ON*/
		state = ON;
	}
	else if (state == ON)
	{
		/*if On make it Off*/
		state = OFF;
	}
	else
	{
		/*do nothing*/
	}
}
/************************************************************************/


/************************************************************************/
/*                           Timer 0 ISR                                */
ISR(TIMER0_OVF_vect)
{
	/*increase timerFlag*/
	timerFlag++;
	/*check on state*/
	if (state == ON)
	{
		/*if on then check if timerFlag is 2*/
		if (timerFlag == 2)
		{
			/*if yes read temperature*/
			currentTemp = LM35_Read(ADC7);
		}
	}
}
/************************************************************************/

