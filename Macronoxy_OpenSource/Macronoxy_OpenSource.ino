//This is an example version, so you can get an idea of how it works
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <EEPROM.h>

#define ENCA 14 //clk
#define ENCB 16 //dt
#define ENCS 10
#define SDAP 2
#define SCLP 3

//display soft
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);
// debounce variables
const unsigned long debounceTime = 30; // debounce time in ms
unsigned long lastDebounceTime = 0;


int stat=EEPROM.read(0);
int cst=stat;
void setup() {
  Serial.begin(9600);
pinMode(ENCA, INPUT);
pinMode(ENCB, INPUT);
pinMode(ENCS, INPUT_PULLUP);
u8g2.begin();
lightshow(stat);
}
bool recheck=false;
void loop() {
pulse();
pulseloop();
if(cst!=stat){
lightshow(stat);}
if(btncheck()){
  if(!recheck){
  cmdshell(stat); // TRY MOVING BTNCHECK OUT OF THE SWITCH INTO THE LOOP
  recheck=true;
  delay(250);
   }
}else
  recheck=false;
//if(cst!=stat)
//Serial.println(stat);
cst=stat;
}
int clk=0;
int lst=digitalRead(ENCA);

void pulse(){
  clk=digitalRead(ENCA);
  if(clk!=lst&&clk==1) {
    // debounce the signal
    if (millis() - lastDebounceTime > debounceTime) {
      lastDebounceTime = millis();
      
      if(digitalRead(ENCB)!=clk)
        stat++;
      else
        stat--;
    }
  }
  lst=clk;
}


const int min=1;
const int max=8;

void pulseloop(){
if(stat>max)
stat=min;
if(stat<min)
stat=max;
}

void displayo(){

}
void lightshow(int input){
  switch(input){
  case 1:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Settings");	// write something to the internal memory
    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
    u8g2.drawStr(105,22,"H");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 2:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Email");	// write something to the internal memory
    u8g2.drawStr(0,20,"Email Input");
    u8g2.setFont(u8g2_font_profont22_tr);
    u8g2.drawStr(110,20,"@");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 3:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Email Password");	// write something to the internal memory
    u8g2.drawStr(0,20,"Password Input");
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawStr(105,22,"@");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 4:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Network 2");	// write something to the internal memory
    u8g2.drawStr(0,20,"Wi-Fi Password");
    u8g2.drawStr(120,22,"1");
    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
    u8g2.drawStr(105,22,"P");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 5:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Network 2");	// write something to the internal memory
    u8g2.drawStr(0,20,"Wi-Fi Password");
    u8g2.drawStr(120,22,"2");
    u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
    u8g2.drawStr(105,22,"P");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 6:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"These are just");// write something to the internal memory
    u8g2.drawStr(0,20,"examples of what");// write something to the internal memory
    u8g2.drawStr(0,30,"you could do");// write something to the internal memory
    u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
    u8g2.drawStr(105,22,"W");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 7:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Shutdown");	// write something to the internal memory
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawStr(105,22,"A");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
  case 8:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_helvB08_tr);	// choose a suitable font
    u8g2.drawStr(10,10,"Crafted with love");	// write something to the internal memory
    u8g2.drawStr(10,20,"by Jason Kyi ");
    u8g2.setFont(u8g2_font_open_iconic_human_2x_t);
    u8g2.drawStr(105,22,"B");
    u8g2.sendBuffer(); // transfer internal memory to the display
    delay(10);
    break;
  }
}
void cmdshell(int input){
  switch(input){
  case 1:
    Keyboard.press(KEY_LEFT_CTRL);
    delay(250);
    Keyboard.press(KEY_LEFT_GUI);
    delay(250);
    Keyboard.press(KEY_ESC);
    delay(1000);
    Keyboard.releaseAll();
    break;
  case 2:
    Keyboard.println("email output 1");
    break;
  case 3:
    Keyboard.println("password output 1");
    break;
  case 4:
    Keyboard.println("network password 1");
    break;
  case 5:
    Keyboard.println("network password 2");
    break;
  case 6:
    Keyboard.press(KEY_LEFT_GUI);
    delay(20);
    Keyboard.release(KEY_LEFT_GUI);
    break;
  case 7:
    Keyboard.println("dropbox.com or something");
    break;    
  case 8:
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_profont11_tr);	// choose a suitable font
    u8g2.drawStr(0,15,"Need help? msg me");	// write something to the internal memory
    u8g2.drawStr(0,25,"(626) 614-3889");
    u8g2.setFont(u8g2_font_open_iconic_text_2x_t);
    u8g2.drawStr(105,22,"E");
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(10);
    break;
   }
}
bool btncheck(){
if(digitalRead(ENCS)==LOW)
{
EEPROM.update(0,stat);
return true;}
return false;
}
