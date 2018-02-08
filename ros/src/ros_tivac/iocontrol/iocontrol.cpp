#include <stdbool.h>
#include <stdint.h>
#include <algorithm>
#include <string>

// TivaC specific includes
extern "C"
{
  #include <driverlib/interrupt.h>
  #include <driverlib/sysctl.h>
  #include <driverlib/gpio.h>
  #include <driverlib/adc.h>
  #include "inc/hw_ints.h"
  #include "driverlib/ssi.h"
  #include "driverlib/pin_map.h"
  #include "driverlib/timer.h"

    #include "inc/hw_types.h"
  #include "inc/hw_gpio.h"
  #include "inc/hw_memmap.h"
}

// ROS includes
#include <ros.h>

//message includes
#include "tivac_iocontrol_msg/IO_Control.h"

// ROS nodehandle
ros::NodeHandle nh;

#define PERIODIC_UPDATE_RATE_HZ 32

//
// function declarations
//
// void ReadADC(void);
void enableSysPeripherals(void);
// void setupAnalog(void);


void IOControlHandler(const tivac_iocontrol_msg::IO_Control &msg){

  uint32_t port;

  switch((char) msg.port){
    case 'A':
      port = GPIO_PORTA_BASE;
      break;
    case 'B':
      port = GPIO_PORTB_BASE;
      break;
    case 'C':
      port = GPIO_PORTC_BASE;
      break;
    case 'D':
      port = GPIO_PORTD_BASE;
      break;
    case 'E':
      port = GPIO_PORTE_BASE;
      break;
    case 'F':
      port = GPIO_PORTF_BASE;
      break;
    default:
      return;
  }

  GPIOPinWrite(port, msg.mask, msg.value);
}

ros::Subscriber<tivac_iocontrol_msg::IO_Control> io_control("MuscleLikeActuator/IOControl", &IOControlHandler);

void PeriodicUpdate(void){

  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

  if(nh.connected())
  {
    // tendon1_status.publish(&Tendon1Stepper.status);
  }

  nh.spinOnce();

  // ADCProcessorTrigger(ADC0_BASE, 1);
}

int main(void)
{
    // TivaC application specific code
    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    // TivaC system clock configuration. Set to 80MHz.
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    IntMasterDisable();
    enableSysPeripherals();

    GPIOPinWrite(GPIO_PORTA_BASE,                           GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 255);
    // GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 255);
    GPIOPinWrite(GPIO_PORTC_BASE,                                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 255);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 255);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5                          , 255);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4                                       , 255);

    // setupAnalog();

    nh.initNode();

    nh.subscribe(io_control);

    while(!nh.connected()) {nh.spinOnce();}
    
    TimerDisable(TIMER0_BASE, TIMER_A);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); //Periodic tasks
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet() / PERIODIC_UPDATE_RATE_HZ)-1);
    TimerIntRegister(TIMER0_BASE, TIMER_A, PeriodicUpdate);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    IntMasterEnable();

    while(1)
    {
    }
}

//
// Initialization functions
//

void enableSysPeripherals(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
  {
  }

  HWREG(GPIO_PORTC_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;  //unlock pins C 0-3 for use
  HWREG(GPIO_PORTC_BASE+GPIO_O_CR) |= (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
  
  HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY; //Unlock pin D7 for use
  HWREG(GPIO_PORTD_BASE+GPIO_O_CR) |= GPIO_PIN_7;

  HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY; //unlock pin F0 for use
  HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;


  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,                           GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  // GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,                                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5                          );
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4                                       );

}
