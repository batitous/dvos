
#include "../include/libs-hardware.h"

//-------------------------- private functions:

void setPwmCycleAndEnableOutput(PWM pwmSelected, UInt32 cycle)
{
    if( (pwmSelected & PWM1) == PWM1)
    {
        LPC_PWM1->MR1 = cycle;
     
        // enable new value in MRx
        SETBIT(LPC_PWM1->LER,1);
        
        // enable pwm output
        SETBIT(LPC_PWM1->PCR,9);
    }
    
    if( (pwmSelected & PWM2) == PWM2)
    {
        LPC_PWM1->MR2 = cycle;
        
        SETBIT(LPC_PWM1->LER,2);
        SETBIT(LPC_PWM1->PCR,10);
    }
    
    if( (pwmSelected & PWM3) == PWM3)
    {
        LPC_PWM1->MR3 = cycle;
        
        SETBIT(LPC_PWM1->LER,3);
        SETBIT(LPC_PWM1->PCR,11);
    }
    
    if( (pwmSelected & PWM4) == PWM4)
    {
        LPC_PWM1->MR4 = cycle;
        
        SETBIT(LPC_PWM1->LER,4);
        SETBIT(LPC_PWM1->PCR,12);
    }
    
    if( (pwmSelected & PWM5) == PWM5)
    {
        LPC_PWM1->MR5 = cycle;
        
        SETBIT(LPC_PWM1->LER,5);
        SETBIT(LPC_PWM1->PCR,13);
    }
    
    if( (pwmSelected & PWM6) == PWM6)
    {
        LPC_PWM1->MR6 = cycle;
        
        SETBIT(LPC_PWM1->LER,6);
        SETBIT(LPC_PWM1->PCR,14);
    }
}


//-------------------------- public functions:


void InitPwm(PWM pwmSelected, UInt32 widthInUs, UInt32 percentage)
{
    UInt32 widthPwm, cycle;
    
    // turn on the pwm module
    SETBIT(LPC_SC->PCONP,6);
    
    
    // set pwm clock to 100MHz
    SETBIT(LPC_SC->PCLKSEL0,12);
    
    // PINSEL
    if( (pwmSelected & PWM1) == PWM1)
    {
        // PWM1.1 PINSEL3 10 to 5:4
//        SETBIT(LPC_PINCON->PINSEL3,5);
        
        // GPIO 2.0
        SETBIT(LPC_PINCON->PINSEL4,0);
    }
    
    if( (pwmSelected & PWM2) == PWM2)
    {
        // PWM1.2 PINSEL3 10 to 9:8
//        SETBIT(LPC_PINCON->PINSEL3,9);
        
        // PWM1.2 PINSEL4 01 to 2:3
        SETBIT(LPC_PINCON->PINSEL4,2);
    }
    
    if( (pwmSelected & PWM3) == PWM3)
    {
        // PWM1.3 PINSEL3 10 to 11:10
        SETBIT(LPC_PINCON->PINSEL3,11);
    }
    
    if( (pwmSelected & PWM4) == PWM4)
    {
        // PWM1.4 PINSEL3 10 to 15:14
//        SETBIT(LPC_PINCON->PINSEL3,15);
        
        // GPIO2.3
        SETBIT(LPC_PINCON->PINSEL4,6);
    }
    
    if( (pwmSelected & PWM5) == PWM5)
    {
        // PWM1.5 PINSEL3 10 to 17:16
//        SETBIT(LPC_PINCON->PINSEL3,17);
        
        // GPIO2.4
        SETBIT(LPC_PINCON->PINSEL4,8);
    }
    
    if( (pwmSelected & PWM6) == PWM6)
    {
        // PWM1.6 PINSEL3 10 to 21:20
//        SETBIT(LPC_PINCON->PINSEL3,21);
        
        // GPIO2.5
        SETBIT(LPC_PINCON->PINSEL4,10);
    }
    
    // WTF ??? 
    // SAME PORT IN PINSEL4 function 01
    // 1:0 pwm1.1
    // 2:3 pwm1.2
    // 5:4 pwm1.3
    // 7:6 pwm1.4
    // 9:8 pwm1.5
    // 11:10 pwm1.6
    
    // ENCORE WTF
    // only on 100pins packages, PINSEL7 function 11
    // 19:18 pwm1.2
    // 21:20 pwm1.3
    
    
    // enable pwm
    SETBIT(LPC_PWM1->TCR,3);
    
    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    
    // prescaler ??
    //LPC_PWM1->PC = 1;
    
    
    // MR0 store the pwm period
    LPC_PWM1->MR0 = widthPwm;

    // MR0 is a new value
    SETBIT(LPC_PWM1->LER,0);

    // MRx store the pwm duty cycle: time the MATx pin is high
    percentage = 100 - percentage;
    cycle = (widthPwm * (100 - percentage)) / 100;
    
    setPwmCycleAndEnableOutput(pwmSelected,cycle);
    
    // if pwm counter == MR0, then reset pwm counter
    SETBIT(LPC_PWM1->MCR,1);
    
}

void EnablePwm(Bool start)
{
    if(start==True)
    {
        // enable pwm
        SETBIT(LPC_PWM1->TCR,0);
        CLRBIT(LPC_PWM1->TCR,1);
    }
    else
    {
        // disable pwm
        CLRBIT(LPC_PWM1->TCR,0);
        SETBIT(LPC_PWM1->TCR,1);
    }
}

void SetPwmDutyCycle(PWM pwmSelected, UInt32 percentage)
{
    UInt32 cycle;
    UInt32 widthPwm = LPC_PWM1->MR0;
    
    percentage = 100 - percentage;
    cycle = (widthPwm * (100 - percentage)) / 100;
    
    setPwmCycleAndEnableOutput(pwmSelected,cycle);
    
}

void SetPwmWidth(UInt32 widthInUs)
{
    UInt32 widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    
    //LPC_PWM1->PC = 1;
    LPC_PWM1->TC = 0;
    
    
    // MR0 store the pwm period
    LPC_PWM1->MR0 = widthPwm;

    // MR0 is a new value
    SETBIT(LPC_PWM1->LER,0);
}


void InitPwmForSound(UInt32 widthInUs, UInt32 percentage)
{
     UInt32 widthPwm, cycle;
    
    // turn on the pwm module
    SETBIT(LPC_SC->PCONP,6);
    
    // set pwm clock to 100MHz
    SETBIT(LPC_SC->PCLKSEL0,12);
    
    // enable pwm
    SETBIT(LPC_PWM1->TCR,3);
    
    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    
    // MR5 store the pwm period
    LPC_PWM1->MR5 = widthPwm;

    // MR5 is a new value
    SETBIT(LPC_PWM1->LER,5);

    // MRx store the pwm duty cycle: time the MATx pin is high
    percentage = 100 - percentage;
    cycle = (widthPwm * (100 - percentage)) / 100;
    
    LPC_PWM1->MR6 = cycle;
    
    SETBIT(LPC_PWM1->LER,6);
    SETBIT(LPC_PWM1->PCR,6);
    SETBIT(LPC_PWM1->PCR,14);
    
    // if pwm counter == MR5, then reset pwm counter
    SETBIT(LPC_PWM1->MCR,16);
    
}
