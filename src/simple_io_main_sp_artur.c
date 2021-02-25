#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

// definir clock do projeto em 24MHz
#define __CONFIG_CLOCK	  (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480)
#define __SYSTEM_CLOCK    (24000000UL)

void main(void){
  SysCtlClockFreqSet(__CONFIG_CLOCK, __SYSTEM_CLOCK); // Funcao para setar o clock usando PLL
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LEDs D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LEDs D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  while(1){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // Apaga LED D4
    SysCtlDelay(8000000); // Uma funcao em loop que executa em 3 ciclos => 8.000.000 = 1segundo/{[1/(24MHz)] * 3ciclos}
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Acende LED D4
    SysCtlDelay(8000000);
  } // while
} // main