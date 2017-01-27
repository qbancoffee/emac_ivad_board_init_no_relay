



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

    writeToIvad(70, 0x01 , 0xAE);
    writeToIvad(70, 0x02 , 0xAA);
    writeToIvad(70, 0x03 , 0xB6);
    writeToIvad(70, 0x04 , 0xBF);
    writeToIvad(70, 0x05 , 0xBC);
    writeToIvad(70, 0x06 , 0x3B);
    writeToIvad(70, 0x07 , 0xCE);
    writeToIvad(70, 0x08 , 0xB9);
    writeToIvad(70, 0x09 , 0xB3);
    writeToIvad(70, 0x0A , 0x96);
    writeToIvad(70, 0x0B , 0xD3);
    writeToIvad(70, 0x0C , 0xDB);
    writeToIvad(70, 0x0D , 0x1A);
    writeToIvad(70, 0x0E , 0xC5);
    writeToIvad(70, 0x0F , 0xC2);
    writeToIvad(70, 0x10 , 0x8A);
    writeToIvad(70, 0x11 , 0x0B);
    writeToIvad(70, 0x12 , 0x46);
    writeToIvad(70, 0x14 , 0x37);
    writeToIvad(70, 0x15 , 0x43);
    writeToIvad(76, 0x00 , 0xD4);
    writeToIvad(76, 0x01 , 0xCE);
    writeToIvad(76, 0x02 , 0xCE);
    writeToIvad(76, 0x03 , 0x9D);
    writeToIvad(70, 0x00 , 0xFF);

  }
}








