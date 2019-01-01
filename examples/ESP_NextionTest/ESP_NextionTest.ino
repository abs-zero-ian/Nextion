/**
 * Some mods made to the Nextion Library by Ian Till to work with SoftwareSerial on pins D5 and D6 
 * (which should match with the ESP-NexUpload Lib used by iotappstory.
 * 
 * Mods are:
 * 
 *  1)  In NexHardware.CPP
 *      line 229:     nexSerial.begin(9600); 
 *      
 *  2)  In NexHardware.h
 *      line 37:      //#define nexSerial SoftwareSerial (commented this out)
 */



//
//
//#define COMPDATE __DATE__ __TIME__
//#define MODEBUTTON 0                                        // Button pin on the esp for selecting modes. D3 for the Wemos!
//
//
//#include <IOTAppStory.h>                                    // IotAppStory.com library
//#include <FS.h>
//IOTAppStory IAS(COMPDATE, MODEBUTTON);                      // Initialize IotAppStory

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
//  /* TIP! delete lines below when not used */
//  IAS.preSetDeviceName("NextionTest");                       // preset deviceName this is also your MDNS responder: http://virginsoil.local
//
//  // You can configure callback functions that can give feedback to the app user about the current state of the application.
//  // In this example we use serial print to demonstrate the call backs. But you could use leds etc.
//
//  IAS.onModeButtonShortPress([]() {
//    Serial.println(F(" If mode button is released, I will enter in firmware update mode."));
//    Serial.println(F("*-------------------------------------------------------------------------*"));
//  });
//
//  IAS.onModeButtonLongPress([]() {
//    Serial.println(F(" If mode button is released, I will enter in configuration mode."));
//    Serial.println(F("*-------------------------------------------------------------------------*"));
//  });
//
//  IAS.onModeButtonVeryLongPress([]() {
//    Serial.println(F(" If mode button is released, I won't do anything unless you program me to."));
//    Serial.println(F("*-------------------------------------------------------------------------*"));
//    /* TIP! You can use this callback to put your app on it's own configuration mode */
//  });
// 
// 
//  //IAS.begin();
//  IAS.begin('P');                                     // Optional parameter: What to do with EEPROM on First boot of the app? 'F' Fully erase | 'P' Partial erase(default) | 'L' Leave intact
//
//  IAS.setCallHome(true);                              // Set to true to enable calling home frequently (disabled by default)
//  IAS.setCallHomeInterval(60);                        // Call home interval in seconds, use 60s only for development. Please change it to at least 2 hours in production


  //-------- Your Setup starts from here ---------------

    /* Set the baudrate which is for debug and communicate with Nextion screen. */
    Serial.println("Pre-Nex_init");
    nexInit();
    Serial.println("Post-Nex_init");

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
//  IAS.loop();                                   // this routine handles the calling home functionality and reaction of the MODEBUTTON pin. If short press (<4 sec): update of sketch, long press (>7 sec): Configuration


  //-------- Your Sketch starts from here ---------------


    /*
     * When a pop or push event occured every time, 
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
    
    nexLoop(nex_listen_list);

}
