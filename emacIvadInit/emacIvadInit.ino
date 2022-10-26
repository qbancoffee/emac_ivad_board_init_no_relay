#include <Wire.h>

//define relay and power button pins

int powerButtonPin = 3;

//define state variables
int isEmacOn = LOW;
int buttonState = LOW;

//counters
int buttonPressedTime = 0;

void setup() {

  //define pin direction

  pinMode(powerButtonPin, INPUT);

  Wire.begin(); // join i2c bus (address optional for master)
  delay(5000);
  initIvadBoard();

}

byte x = 0;

void loop() {
  buttonState = digitalRead(powerButtonPin);

  if (buttonState == HIGH)
  {
    buttonPressedTime++;
    //  Serial.println("HIGH");

  }
  else
  {
    buttonPressedTime = 0;

  }
  delay(1000);

  //turn everything off if button is pressed for 5 seconds
  if (buttonPressedTime >= 5 && isEmacOn == HIGH) {
    buttonPressedTime = 0;
    isEmacOn=LOW;

  }

  //turn everything on if button is pressed for 1 second
  if (buttonPressedTime >= 2 && isEmacOn == LOW) {
    delay(5000);
    initIvadBoard();
    buttonPressedTime = 0;
    isEmacOn=HIGH;

  }

}

void writeToIvad(int address, int message) {
  Wire.beginTransmission(address);
  Wire.write(message);
  Wire.endTransmission();

}//end method

void writeToIvad(int address, int message1, int message2) {
  Wire.beginTransmission(address);
  Wire.write(message1);
  Wire.write(message2);
  Wire.endTransmission();

}//end method

void  readFromIvad(int address, int bytes) {
  char buf[bytes + 1];
  int bytesRead = 0;
  Wire.requestFrom(address, bytes);
  while (Wire.available())
  {
    char c = Wire.read();
    buf[bytesRead++] = c;
  }
  buf[bytesRead] = '\0';
  //return buf;

}//end method

void initIvadBoard() {

  for (int j = 0 ; j < 1 ; j++) {

    writeToIvad(70, 0 , 0);

    for (int i = 0 ; i <= 100 ; i += 10) {
      writeToIvad(83, i);
      readFromIvad(83, 10);

    }//end for

    //  SENDING TO DEVICE 0x46      PROPERTY                        RANGE
    writeToIvad(70, 0x00 , 0xE0);/* CONTRAST                        0x80-0xFF       */
    writeToIvad(70, 0x01 , 0xAA);/* GREEN COLORTEMP                 0x00-0xFF       */
    writeToIvad(70, 0x02 , 0xAA);/* BLUE COLORTEMP                  0x00-0xFF       */
    writeToIvad(70, 0x03 , 0xAA);/* RED COLORTEMP                   0x00-0xFF       */
    writeToIvad(70, 0x04 , 0xBF);/* TOP PINCH/WIDTH                 0x00-0xFF       */
    writeToIvad(70, 0x05 , 0xBC);/* TOP 'LEAN'                      0x00-0xFF	      */
    writeToIvad(70, 0x06 , 0x3B);/* BOTTOM 'LEAN'                   0x00-0xFF	      */
    writeToIvad(70, 0x07 , 0xCE);/* HORIZONTAL POSITION             0x80-0xFF      	*/
    writeToIvad(70, 0x08 , 0xB9);/* VERTICAL SIZE                   0x80-0xFF      	*/
    writeToIvad(70, 0x09 , 0xB3);/* VERTICAL POSITION               0x00-0xFF	      */
    writeToIvad(70, 0x0A , 0x96);/* ROUNDNESS ADJUSTMENT            0x00-0xFF      	*/
    writeToIvad(70, 0x0B , 0xD3);/* KEYSTONE                        0x00-0xFF      	*/
    writeToIvad(70, 0x0C , 0xDB);/* PINCUSHION                      0x00-0xFF      	*/
    writeToIvad(70, 0x0D , 0x1A);/* HORIZONTAL SIZE                 0x00-0xFF	      */
    writeToIvad(70, 0x0E , 0xC5);/* TOP & BOTTOM PULL LEFT/RIGHT    0x00-0xFF      	*/
    writeToIvad(70, 0x0F , 0xC2);/* PARALELLOGRAM                   0x00-0xFF     	*/
    writeToIvad(70, 0x10 , 0x8A);/* GAMMA                           0x80-0xFF	      */
    writeToIvad(70, 0x11 , 0x01);/* BRIGHTNESS                      0x00-0x7F	      */
    writeToIvad(70, 0x12 , 0x46);/* ALTERNATE HORIZONTAL SIZE ?     0x00-0xFF      	*/
    writeToIvad(70, 0x14 , 0x37);/* ALTERNATE VERTICAL SIZE ?       0x00-0xFF	      */
    writeToIvad(70, 0x15 , 0x43);/* BOTTOM PINCH/WIDTH              0x00-0xFF     	*/
    //  SENDING TO DEVICE 0x46      PROPERTY                        RANGE
    writeToIvad(76, 0x00 , 0xD4);/* COLORTEMP BLUE > RED            0x00-0xFF	      */
    writeToIvad(76, 0x01 , 0xCE);/* COLORTEMP YELLOW > BLUE         0x00-0xFF	      */
    writeToIvad(76, 0x02 , 0xCE);/* COLORTEMP MAGENTA > BLUE        0x00-0xFF	      */
    writeToIvad(76, 0x03 , 0x9D);/* ROTATION                        0x00-0xFF	      */

  }
}
