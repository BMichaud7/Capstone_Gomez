
#include <xc.h>


/* Configuration Word */

#pragma config FOSC = INTOSCIO// Clock
#pragma config WDTE = OFF	//
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// CONFIG --- Configuration Word --- END


void PORTA_init(void);
void ADC_Disp(void);
void Delay_LED_On(void);

int ADC_Value = 0;

const char PORTA_Value[3] = {
	0b010000,	// D0 RA4
	0b100000, 	// D1 RA5
	0b000100, 	// D2 
};
    
const char TRISA_Value[3] = {
    0b001111, 	// D0
	0b001111, 	// D1
	0b111011, 	// D2
};
    
int main(void)
{

    PORTA_init();

    ANSEL = 1;                  //  Just RA0 is an Analog Input
    TRISA0 = 1;					//  Corresponding TRIS bit is set as input

    ADCON0 = 0b00000001;
                                
    ADCON1 = 0b00010000;


    ADC_Disp();
    GO_DONE = 1;			// Start A/D Conversion


    while(1 == 1)               //  Loop Forever
    {
	    if (GO_DONE == 0)			// Is A/D Conversion complete?
        	{	ADC_Disp();		// Display A/D Conversion Results
	        	ADC_Value = ((ADRESH<<7)+ADRESL);	// Get new A/D value
	        	GO_DONE = 1;		// Start the next A/D Conversion
	        }
	    else				// A/D Conversion still in progress
	    		ADC_Disp();

	} 
}

/******** END OF main ROUTINE ***************************/


void PORTA_init(void)
{
    PORTA = 0;                  //  All PORTA Pins are low
    CMCON0 = 7;                 //  Turn off Comparators
    ANSEL = 0;                  //  Turn off ADC

    return;

}
/******** END OF PORTA_init ****************************/




void ADC_Disp(void)
{
if (ADC_Value <= 0b1000000000){
            
            PORTA = 0b000000;
            TRISA = 0b111111;
            Delay_LED_On();
        }
        else if ((ADC_Value >= 0b1000000001) && (ADC_Value <= 0b11111010000)){
            
            PORTA = 0b010000;
            TRISA = 0b001111;
            Delay_LED_On();
        }
        else if ((ADC_Value >= 0b11111010001) && (ADC_Value <= 0b101110111000)){
            Delay_LED_On();
            PORTA = 0b100000;
            TRISA = 0b001111;
        }
        else {
            
            PORTA = 0b000100;
            TRISA = 0b111011;
            Delay_LED_On();
        }
return;
}

void Delay_LED_On(void)
{
	int j;
	
	for (j = 0; j < 1000; j++);  		//  Display "On" Loop 
    			
	return;

}
/******** END OF Delay_LED_On *************************/
