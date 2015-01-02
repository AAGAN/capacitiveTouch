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

int nx=10;
int ny=10;
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

void setup() {

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
//    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }
  tft.setRotation(2);
  drawGrid(nx ,ny); 
}


void loop(void) {  
   if (! ctp.touched()) {
    return;
  }
  // Retrieve a point  
  TS_Point p = ctp.getPoint();
  int width= 240/nx;
  int height= 240/ny;
  if ( xx != (p.x/width)*width || yy != ((p.y-(320-240))/height)*height+(320-240)){
    if (p.y > (320-240-1) && (p.y != pyy || p.x != pxx)){
      highlight(p.x,p.y,nx,ny,ILI9341_RED);
      highlight(pxx,pyy,nx,ny,ILI9341_BLACK);
      pxx = p.x;
      pyy = p.y;
      xx = (p.x/width)*width;
      yy = ((p.y-(320-240))/height)*height+(320-240);
    }
  }
  
//  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0,0,240,8,ILI9341_BLACK);
  testText(p.x, p.y);  
//  tft.drawPixel(p.x,p.y,ILI9341_YELLOW);  
}

void highlight(int x, int y, int nx, int ny, uint16_t color){
  
  int xx,yy,width,height;
  width=240/nx;
  height=240/ny;
  xx = (x/width)*width;
  yy = ((y-(320-240))/height)*height+(320-240);
  tft.fillRect(xx,yy,width,height,color);
  tft.drawRect(xx,yy,width,height,ILI9341_YELLOW);

}

void drawGrid(int i, int j){
  int x,y,width,height,ii,jj;
  width=240/i;
  height=240/j;
  for (ii = 0; ii < i; ii++){
    for (jj = 0; jj < j; jj++){
        x=ii*width;
        y=320-240+jj*height;
        tft.drawRect(x,y,width,height,ILI9341_YELLOW);
    }
  }
}

void testText(int x, int y) {

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(1);

  tft.print("x= ");
  tft.print(x);

  tft.print(" y= ");
  tft.println(y);
}   

