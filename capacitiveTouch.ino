/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

int nx=8;
int ny=8;
int pxx=(240/nx)*3;
int pyy=(320-240)+(240/ny)*3;
int xx = 0;
int yy = 0;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

class button
{
	// Class member variables
	// These are initialized at the startup
	String text; //The text displayed on the button
	int width; //width of the button
	int height; //height of the button
	int x; // the x-coordinate of the upper left corner of the button
	int y; // the y-coordinate of the upper lect corner of the button
	uint16_t color;

        boolean state; //The state of the button can be LOW or HIGH
	int long previousTime;

public:
	button(boolean buttonState, String buttonText, int buttonWidth, 
	int buttonHeight, int buttonX, int buttonY)
	{          
		state = buttonState;
		text = buttonText;
		if (buttonWidth> 6*buttonText.length()){width = buttonWidth;}
		else{width = 6*buttonText.length()+1;}
		height = buttonHeight;
		x = buttonX;
		y = buttonY;
		color = ILI9341_RED;   
		previousTime = 0;      
		tft.fillRect(x,y,width,height,color);
		tft.setCursor(x,y); 
		tft.print(text);
                Serial.println("Button created.");
	}
	
	void update(int touchX,int touchY)
	{
		if (touchX < (x+width) && touchX > x){
			if (touchY< (y+height) && touchY > y){
				state = !state;
//				if (state){on();}else{off();}
				tft.fillRect(x,y,width,height,color);
				tft.setCursor(x,y);
				tft.print(text);
			}
		}
	}

//private:
//
//	void on()
//	{
//		color = ILI9341_DARKGREEN;
//	}
//
//	void off()
//	{
//		color = ILI9341_BLACK;
//	}
};

void setup() {

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    while (1);
  }
  tft.setRotation(2);
  Serial.println("constructing the button...");
  button button1(LOW, "BUTTON", 30, 10, 100, 5);
  button button2(LOW, "BUTTON", 30, 30, 100, 5);
  button button3(LOW, "BUTTON", 30, 50, 100, 5);
  button button4(LOW, "BUTTON", 30, 70, 100, 5);
  button button5(LOW, "BUTTON", 30, 90, 100, 5);
}

void loop(void) {  
   if (! ctp.touched()) {
    return;
  }
  
  // Retrieve a point  
  TS_Point p = ctp.getPoint();
  if (p.x > 200){
    Serial.println(p.x);
    Serial.println(p.y);
  }
}
