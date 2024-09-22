#include <Arduino.h>
#include <Servo.h>
#include <LCD_I2C.h>

//Initialize servo object
Servo myservo;
//Initialize LCD I2C object
LCD_I2C lcd(0x27);
//Initializing Pins
int trigPin = 10;
int echoPin = 11;
int buzzer = 6;

long microtocm(long);

void setup() {
  // put your setup code here, to run once:
  
  //Turn on LCD Backlight
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  //Define servo pin and set default position
  myservo.attach(9);
  myservo.write(0);
  //Beginning Serial Monitor
  Serial.begin(9600);
  //Setting pin modes
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzer,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, cm;

  for(int pos = 0; pos <=180; pos++)
  {
    //Clearing lcd at the beginning of every loop
    lcd.clear();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    //Getting the time taken for the pulse to return value in micro seconds
    duration = pulseIn(echoPin,HIGH);
    //converting time into distance
    cm = microtocm(duration);
    //displaying data on the lcd
    lcd.print(pos);
    lcd.print(" deg, ");
    lcd.print(cm);
    lcd.print("cm");
    //Write servo positon
    myservo.write(pos);
    //conditional statement, if object too close buzzer makes sound
    //Uncomment if you would like to add a buzzer that acts like an alarm
    /*
    if (cm < 20)
    {
      digitalWrite(buzzer,HIGH);
    }
    else
    {
      digitalWrite(buzzer,LOW);
    }
    */
    //Adjust delay to increase or decrease speed
    delay(50); 

  }
  //Same as above, except the servo turns in the other direction
  for(int pos = 180; pos >=0; pos--)
  {
    lcd.clear();
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    duration = pulseIn(echoPin,HIGH);

    cm = microtocm(duration);
    lcd.print(pos);
    lcd.print(" deg,");
    lcd.print(cm);
    lcd.print("cm");
    myservo.write(pos);
    //Uncomment if you would like to add a buzzer that acts like an alarm
    /*if (cm < 20)
    {
      digitalWrite(buzzer,HIGH);
    }
    else
    {
      digitalWrite(buzzer,LOW);
    }*/
    //Adjust delay to increase or decrease speed
    delay(50); 
  }
}
/*
Speed of sound is 0.0343 cm/µs so we can find the distance 
if we have the time in microseconds using this function
*/
long microtocm(long seconds)
{
  return seconds/29/2;
}
