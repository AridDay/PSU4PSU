/*
Jenny Lynn Kelly & Petr Esakov
PSU4PSU Microcontroller Integration

This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin 4 to digital pin 7
 * LCD Enable pin 6 to digital pin 8
 * LCD D4 pin 9 to digital pin 5
 * LCD D5 pin 10 to digital pin 4
 * LCD D6 pin 11 to digital pin 3
 * LCD D7 pin 12 to digital pin 2
 * 
 * LCD R/W pin 5 to ground
 * LCD VSS pin 1 to ground
 * LCD VCC pin 2 to 5V
 * 10K resistor:
 * ends to +5V and GND
 * wiper to LCD VO pin (pin 3)
 
 
 This sketch connects the HC-05 to the
 Arduino Uno R3
 
 The circuit:
 
 * HC-05 Enable pin 1 to digital pin 9
 * HC-05 VCC pin 2 to 5V
 * HC-05 GND pin 3 to GND
 * HC-05 TX pin 4 to digital pin 10 (RX)
 * HC-05 RX pin 5 to digital pin 11 (TX)
 * HC-05 STATE pin 6 not connected

 */


#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

float setVoltage = 0;
int dutyCycle = 0;
const int Vmon = A1;
float VmonVal;
const int Imon = A2;
float ImonVal;

SoftwareSerial BTSerial(10, 11);   // RX | TX

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  pinMode(9, OUTPUT);    /* this pin will pull the HC-05 pin 34 (KEY pin) HIGH to switch module to AT mode */
  pinMode(6, OUTPUT);    /* PWM controlling the flyback */
  digitalWrite(9, HIGH); 
  Serial.begin(9600);
  Serial.println("Enter AT Commands:");
  BTSerial.begin(9600);  // HC-05 default speed in AT command mode
  
//////////////////////////////////////////////////////////////////////

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
//////////////////////////////////////////////////////////////////////

  // set up PWM timer with default values:
  OCR0A = 100;
  OCR0B = 0;
  // 160kHz non-inverted PWM on OC0A with no prescaler
  TCCR0A = (1 << COM0A1) | (1<<WGM01) | (1<<WGM00); 
  TCCR0B = (1 << CS00);

//////////////////////////////////////////////////////////////////////

}

void setPWM(int dC){ //Value between 0 and 100
  OCR0B = dutyCycle;
  dutyCycle = dC;
}

void adjustPWM(){
  float vread = (30 * VmonVal)/1023;
  if((setVoltage-vread)>0.6){
	  if(dutyCycle > 0){
		  dutyCycle = dutyCycle - 1;
	  }
  }
  
  if((vread-setVoltage)>0.6){
	  if(dutyCycle < 50){
		  dutyCycle = dutyCycle + 1;
	  }
  }
  setPWM(dutyCycle);
}

void loop(){
	
  
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // read the input on voltage monitor pin:
  VmonVal = analogRead(Vmon);
  ImonVal = analogRead(Imon);
  
  //Feed back read voltage value and adjust PWM duty cycle to make it match the set voltage value
  adjustPWM(); 

  // print out the value you read:
  //Serial.println(voltage);

  // Print a message to the LCD.
  //lcd.print(voltage); //connect this later to Vout/Iout sensors and Bluetooth 
  if (Serial.available()){
	setVoltage = Serial.parseFloat();
  }	  

  /* CURRENTLY COMMENTED OUT BLUETOOTH CODE
  //The code below allows for commands and messages to be sent from COMPUTER (serial monitor) -> HC-05
  if (Serial.available())           // Keep reading from Arduino Serial Monitor 
    BTSerial.write(Serial.read());  // and send to HC-05

  //The code below allows for commands and messages to be sent from HC-05 -> COMPUTER (serial monitor)    
  if (BTSerial.available())         // Keep reading from HC-05 and send to Arduino 
    Serial.write(BTSerial.read());  // Serial Monitor
	
  */

//////////////////////////////////////////////////////////////////////

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

//////////////////////////////////////////////////////////////////////

}
