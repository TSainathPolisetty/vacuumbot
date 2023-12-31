#include <PS3BT.h>
#include <usbhub.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb); 
PS3BT PS3(&Btd); // Create the instance

// Motor driver pins
const int M11 = 0;
const int M12 = 1;
const int M13 = 2;
const int M14 = 3;
const int M21 = 4;
const int M22 = 5;
const int M23 = 6;
const int M24 = 7;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M13, OUTPUT);
  pinMode(M14, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
  pinMode(M23, OUTPUT);
  pinMode(M24, OUTPUT);
}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    handlePS3Controller();
  }
}

void handlePS3Controller() {
  if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
    printAnalogHatValues();
  }

  if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
    printAnalogButtonValues();
  }

  handlePS3ButtonPress();
}

void printAnalogHatValues() {
  Serial.print(F("\r\nLeftHatX: "));
  Serial.print(PS3.getAnalogHat(LeftHatX));
  Serial.print(F("\tLeftHatY: "));
  Serial.print(PS3.getAnalogHat(LeftHatY));
  if (PS3.PS3Connected) {
    Serial.print(F("\tRightHatX: "));
    Serial.print(PS3.getAnalogHat(RightHatX));
    Serial.print(F("\tRightHatY: "));
    Serial.print(PS3.getAnalogHat(RightHatY));
  }
}

void printAnalogButtonValues() {
  Serial.print(F("\r\nL2: "));
  Serial.print(PS3.getAnalogButton(L2));
  if (PS3.PS3Connected) {
    Serial.print(F("\tR2: "));
    Serial.print(PS3.getAnalogButton(R2));
  }
}

void handlePS3ButtonPress() {
    if (PS3.getButtonClick(PS)) {
        Serial.print(F("\r\nPS"));
        PS3.disconnect();
    } else {
        if (PS3.getButtonClick(TRIANGLE)) {
            Serial.print(F("\r\nTriangle"));
            PS3.moveSetBulb(Red);            
        }

        if (PS3.getButtonClick(CIRCLE)) {
            Serial.print(F("\r\nCircle"));
            PS3.moveSetBulb(Green);
        }

        if (PS3.getButtonClick(CROSS)) {
            Serial.print(F("\r\nCross"));
            PS3.moveSetBulb(Yellow);
        }

        if (PS3.getButtonClick(SQUARE)) {
            Serial.print(F("\r\nSquare"));
            PS3.moveSetBulb(Blue);
        }    

        }
    }
}
