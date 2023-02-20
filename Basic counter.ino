/*
 A simple counter using a Max7219 4 way matrix
 Using MD_max72xx and MD_Parola
 using ESP2866

 code can work with esp32 and arduino

 if using arduino you need to load the Libprint Library
 
 www.flixmyswitch.com
 search YouTube for Flixmyswitch
*/

#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>
#include "Font_Data.h"
// #include <LibPrintf.h>  if using arduino

// change this pins to work with your board
#define MAX_DEVICES   4
#define CLK_PIN       14    // or SCK
#define DATA_PIN      13    // or MOSI
#define CS_PIN        15    // or SS

// Change this to work with your matrix - see video 1 you have 4 choices
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

char Buffer[3] = " ";  // create a buffer to hold the numbers
int counter = 0;      // the counter will start from 0 you can set any value

void setup() {
  //Serial.begin(115200);
  P.begin();
  P.setIntensity(1);        // keep it 3 or below as we are powering off the chip/usb
  P.setFont(dig5x8sq);      // If you use the standard built in font the numbers on the matrix will jump around as the number 1 not as wide
                            // as the other numbers.  Comment out this line to see what happens.  I will have a video in the future to show
                            // how to create your own fonts or adjust the ones you find online.
}


void loop() {

  if (P.displayAnimate()) {

    sprintf(Buffer, "%01d", counter);  // the number "1" is the number of digits that you want always shown on the screen for this font we can have 5
    P.displayText(Buffer, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

    counter++;              // add one to the counter
    delay(1000);            // a dirty way to wait for 1 second but good enough for this example
                            // we could have used a mills loop
  }
                            // if needed to stop and reset the counter
  if (counter == 10000) {   //  change this value to increse or decrease the counter reset value you need to set something otherwise the counter
                            // will overflow on the matrix
    counter = 0;            // reset the counter
  }
}                           // end of the loop, loop again