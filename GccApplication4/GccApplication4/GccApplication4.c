
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int count1;
int count2;
int count3;
int count4;
int count5;
int count6;
int count7;
int count0;

int present0;
int present1;
int present2;
int present3;
int present4;
int present5;
int present6;
int present7;

int roadCount1;
int roadCount2;
int roadCount3;
int roadCount4;

uint16_t volt0;
uint16_t volt1;
uint16_t volt2;
uint16_t volt3;
uint16_t volt4;
uint16_t volt5;
uint16_t volt6;
uint16_t volt7;

void InitADC()
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!

	ADCSRA|=(1<<ADIF);

	return(ADC);
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	uint16_t adc_result0;
	uint16_t adc_result1;
	uint16_t adc_result2;
	uint16_t adc_result3;
	uint16_t adc_result4;
	uint16_t adc_result5;
	uint16_t adc_result6;
	uint16_t adc_result7;
	
	InitADC();
	present7=present6=present5=present4=present3=present2=present1=present0=0;
	

	count0=count1=count2=count3=count4=count5=count6=count7=0;
	
	
	roadCount1=roadCount2=roadCount3=roadCount4=0;
	
	PORTD=0b00000000;
	while(1)
	{
		InitADC();
		adc_result0=ReadADC(0);
		// PORTD = 0b11111111;
		if( adc_result0<400)
		{
			if(present0==0){
				present0=1;
				count0++;
				
			}
			
		}
		else
		{
			//do nothing
		}
		if(present0==1 && adc_result0>400){
			present0=0;
		}

		InitADC();
		adc_result1=ReadADC(1);
		// PORTD = 0b11111111;
		if( adc_result1<613)
		{
			if(present1==0){
				present1=1;
				count1++;
				
			}
			
		}
		else
		{
			//do nothing
		}
		if(present1==1 && adc_result1>613){
			present1=0;
		}

		
		InitADC();
		adc_result2=ReadADC(2);
		// PORTD = 0b11111111;
		if( adc_result2<480)
		{
			if(present2==0){
				present2=1;
				count2++;
				
			}
			
		}
		else
		{
			//do nothing
		}
		if(present2==1 && adc_result2>480){
			present2=0;
		}

		InitADC();
		adc_result3=ReadADC(3);
		// PORTD = 0b11111111;
		if( adc_result3<562)
		{
			if(present3==0){
				present3=1;
				count3++;
				
			}
			
		}
		else
		{
			//do nothing
		}
		if(present3==1 && adc_result3>562){
			present3=0;
		}
		
		InitADC();
		adc_result4=ReadADC(4);
		// PORTD = 0b11111111;
		if( adc_result4<572)
		{
			if(present4==0){
				present4=1;
				count4++;
			}
			
		}
		else
		{
			//do nothing
		}
		if(present4==1 && adc_result4>572){
			present4=0;
		}

		InitADC();
		adc_result5=ReadADC(5);
		// PORTD = 0b11111111;
		if( adc_result5<204)
		{
			if(present5==0){
				present5=1;
				count5++;
				
			}
			
		}
		else
		{
			//do nothing
		}
		if(present5==1 && adc_result5>204){
			present5=0;
		}

		InitADC();
		adc_result6=ReadADC(6);
		// PORTD = 0b11111111;
		if( adc_result6<523)
		{
			if(present6==0){
				present6=1;
				count6++;
			}
			
		}
		else
		{
			//do nothing
		}
		if(present6==1 && adc_result6>523){
			present6=0;
		}

		InitADC();
		adc_result7=ReadADC(7);
		// PORTD = 0b11111111;
		if( adc_result7<163)
		{
			if(present7==0){
				present7=1;
				count7++;
			}
			
		}
		else
		{
			//do nothing
		}
		if(present7==1 && adc_result7>163){
			present7=0;
		}

		roadCount1=count6-count0;
		roadCount2=count2-count3;
		roadCount3=count7-count5;
		roadCount4=count1-count4;
		
		if(roadCount1>=roadCount2 && roadCount1>=roadCount3 && roadCount1>=roadCount4)PORTD=0b10101001;
		else if(roadCount2>=roadCount1 && roadCount2>=roadCount3 && roadCount2>=roadCount4) PORTD=0b10100110;
		else if((roadCount3>=roadCount2 && roadCount3>=roadCount1 && roadCount3>=roadCount4)) PORTD=0b10011010;
		else PORTD=0b01101010;
	}
}