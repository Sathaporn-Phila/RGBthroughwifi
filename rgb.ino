#include <stdio.h>
#include <string.h>
#include<stdlib.h>

int R = 11;
int G = 10;
int B = 9;
int led = 8;
const int pingPin = 13;
int inPin = 12;
const int pingPin2 = 7;
int inPin2 = 4;
unsigned int person = 0;
unsigned int state_left = 0;
unsigned int state_right = 0;  
unsigned int red = 0;
unsigned int green = 0;
unsigned int blue = 255;
long duration,cm,cm2,duration2;
unsigned long temp_time = 0;
unsigned int lock_time = 0;
void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(inPin2, INPUT);
  Serial.begin(115200);
}

void loop() {
   if(Serial.available()){
    while (Serial.available()) {
      String inchar = Serial.readStringUntil("\n");
      int str_len = inchar.length() + 1;
      char char_array[str_len];
      inchar.toCharArray(char_array, str_len); 
      if(strchr(char_array,',') != NULL){
        char *rgb = strtok(char_array, ",");
        int count = 0;
        while( rgb != NULL ) {
          char *item = malloc(100);
          strcpy(item,rgb);
          if (count == 0){
            red = atoi(item);
          }
          else if (count == 1) {
            green = atoi(item);
          }
          else if (count == 2) {
            blue = atoi(item);
          }
          free(item);
          rgb = strtok(NULL, ",");
          count++;
         }
        }
      check_person();
    }
  }
  else{
    check_person();
  }
}
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
void ultrasonic(){
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    duration = pulseIn(inPin, HIGH);
     
    cm = microsecondsToCentimeters(duration);
     
    digitalWrite(pingPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin2, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin2, LOW);
    duration2 = pulseIn(inPin2, HIGH);
    
    cm2 = microsecondsToCentimeters(duration2);
    
    if(cm < 50){
      lock_time = 0;
      if(state_left == 0){
        state_left = 1;
        delay(500);  
      }
      else if (state_right == 1){
        state_right = 0;
        if(person > 0){
          person--;
        }
        delay(500);
      }
    }
    if(cm2 < 50){
      lock_time = 0;
      if (state_left == 1){
        state_left = 0;
        person++;
        delay(500);
      }
      else if (state_right == 0){
        state_right = 1;
        delay(500);
      }
   }
   if( cm >= 50 && cm2 >= 50){
    if(lock_time == 0){
      temp_time = millis();
      lock_time = 1;
    }
    if(millis()-temp_time > 4000){
      state_left = 0;
      state_right = 0;
      }
   }
}
void check_person(){
  ultrasonic();
    if(person>0){
      analogWrite(R,red);
      analogWrite(G,green);
      analogWrite(B,blue);
    }
    else{
      analogWrite(R,0);
      analogWrite(G,0);
      analogWrite(B,0);
    }
    
}
