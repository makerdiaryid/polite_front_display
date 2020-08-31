#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

JQ6500_Serial mp3(8,9);
Servo myservo; 
int pos = 0;

const int trigPin = 2;
const int echoPin = 3;
const int mindistance=35;
long duration;
int distance;



void setup() {
  Serial.begin(9600);
  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(80);
  mp3.setLoopMode(MP3_LOOP_NONE);
  
  myservo.attach(11);
  myservo.write(180);

  pinMode(12, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if(digitalRead(10)!=HIGH){
      Serial.println(checkdisntance());
      if(checkdisntance()<mindistance){
         bowsequence();
         delay(10000);
      }
  }
  
 if(digitalRead(7)!=HIGH){
   // Serial.println("pin 7 press");
    bowsequence();
    //while(digitalRead(7)!=HIGH){
          delay(5000);
    //}
  }else if(digitalRead(12)!=HIGH){
   // Serial.println("pin 12 press");
    bowsequence();
    //while(digitalRead(12)!=HIGH){
          delay(5000);
    //}
  }
  
}


int checkdisntance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
}


void bowsequence(){
  playmp3();
  for (pos = 180; pos >= 130; pos -= 1) { 
    myservo.write(pos);             
    delay(20);                       
  }
  
  for (pos = 130; pos <= 180; pos += 1) { 
    myservo.write(pos);              
    delay(20);                      
  }
}

void playmp3(){
  mp3.playFileByIndexNumber(1);  
}

