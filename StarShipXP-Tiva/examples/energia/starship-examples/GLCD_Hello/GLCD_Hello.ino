#include <SPI.h>
#include <StarShipXP.h>

const int chipSelect = PA_3;

void setup()
{
  SPI.setModule(2);
  
  pinMode(PA_2, OUTPUT);
  digitalWrite(PA_2, HIGH);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  GLCD_Set();
  GLCD();

}


void loop(void) {

}


void GLCD_Set()
{
  pinMode(GLCD_SEL1,OUTPUT);
  digitalWrite(GLCD_SEL1,HIGH);

}

void GLCD()
{
    Tft.begin(GLCD_SEL2,GLCD_DC,PF_0,GLCD_RESET);                // CS,DC,BL,RESET pin
    Tft.TFTinit();                                 // init TFT library
    Tft.backlight_on();                            // turn on the background light
    
    Tft.drawString("Hello",0,10,3,CYAN,BLACK);       // draw string: "hello", (0, 180), size: 3, color: CYAN
    Tft.drawString("World!!",60,60,4,WHITE,BLACK);    // draw string: "world!!", (80, 230), size: 4, color: WHITE
    
 
}

