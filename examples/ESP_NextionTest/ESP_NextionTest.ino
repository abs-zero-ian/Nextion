/**
 * IAS_NextionTest.ino 
 * Ian Till - https://github.com/abs-zero-ian/Nextion - January 2019
 * 
 * This sketch will run a simple demo with two-way communication with the display - a number is displayed
 * with two buttens marked '-' and '+'.  The displayed number is read from the display and incremented or
 * decremented depending on which button is pressed and the result is written back to the display.
 * 
 * This sketch should be used with the Nextion TFT files included in this folder:
 * 
 *  -  NextionTest.tft  - use this directly on a 2.4" Nextion display
 *  -  Nextiontest.HMI  - the HMI file is provided to allow recompilation and modification    
 */


#include <Nextion.h>


// ================================================ EXAMPLE VARS =========================================

/*
 * Declare a number object [page id:0,component id:3, component name: "n0"]. 
 */
NexNumber n0 = NexNumber(0, 3, "n0");
NexButton b0 = NexButton(0, 1, "b0");
NexButton b1 = NexButton(0, 2, "b1");

char buffer[100] = {0};


/*
 * Register object n0, b0, b1, to the touch event list.  
 */
NexTouch *nex_listen_list[] = 
{
    &n0,
    &b0,
    &b1,
    NULL
};


/*
 * number component pop callback function. 
 */
void n0PopCallback(void *ptr)
{
    dbSerialPrintln("n0PopCallback");
    n0.setValue(50);
}


/*
 * Button0 component pop callback function.
 * In this example,the value of the number component will plus one every time when button0 is released.
 */
void b0PopCallback(void *ptr)
{
    uint32_t number;
    dbSerialPrintln("b0PopCallback");
    n0.getValue(&number);
    number += 1;
    n0.setValue(number);
}


/*
 * Button1 component pop callback function.
 * In this example,the value of the number component will minus one every time when button1 is released.
 */
void b1PopCallback(void *ptr)
{
    uint32_t number;
    dbSerialPrintln("b1PopCallback");
    n0.getValue(&number);
    number -= 1;
    n0.setValue(number);
}


// ================================================ SETUP ================================================
void setup() {

    nexInit();

    /* Register the pop event callback function of the current number component. */
    n0.attachPop(n0PopCallback);

    /* Register the pop event callback function of the current button0 component. */
    b0.attachPop(b0PopCallback);

    /* Register the pop event callback function of the current button1 component. */
    b1.attachPop(b1PopCallback);

    Serial.println("setup done");

}


// ================================================ LOOP =================================================
void loop() 
{
    /*
     * When a pop or push event occured every time, 
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
    
    nexLoop(nex_listen_list);

}
