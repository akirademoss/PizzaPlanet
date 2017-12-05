#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <Timer.h>
#include <lcd.h>

void adc_init(void)
{
    //enable ADC 0 module on port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //enable clock for ADC
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port B pin 4 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0x10;

    //set disable digital
    GPIO_PORTB_DEN_R &= ~0x10;

    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |=0x10;

    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;

    //enable raw interrupt
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

    //enable hardware oversampling (averaging)
    ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
}


unsigned ADC_read(char channel)
{
    //disable ADC0SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //set 1st sample to use the channel ADC pin
    ADC0_SSMUX0_R |= channel;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //initiate SS0 conversion
    ADC0_PSSI_R = ADC_PSSI_SS0;

    //wait for ADC conversion to be complete
    while ((ADC0_RIS_R & ADC_RIS_INR0) == 0);

    //clear interrupt
    ADC0_ISC_R = ADC_ISC_IN0;

    return ADC0_SSFIFO0_R;
}

/**
 * Returns the distance of an object from the IR sensor
 * Calibration for CyBot #2
 * @return distance
 */
float ir_getDistance(void){
        int digital_v = 0;
        int distance = 0;
        lcd_init();
        adc_init();

        digital_v = ADC_read(10);
        distance = 4570.56*pow(digital_v, -0.8263013);
        lcd_printf("digital_v %d  (V)\n distance %d (cm)",digital_v,distance);
        return distance;
}



