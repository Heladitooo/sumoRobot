#include <IRremote.h>
IRrecv irrecv(4);
decode_results codigo;

int echo = 3;
int trig = 2;
int receptor = 4;
bool on = false;
int lightFront = 5;
int lightBack = 6;

bool found = false;

void motorMode(int pin,int pin2, bool state){
    if(state == false){
        digitalWrite(pin, LOW);
        digitalWrite(pin2, LOW);
    } else {
        digitalWrite(pin,LOW);
        digitalWrite(pin2,HIGH);
    }
}

void setup(){
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(receptor, INPUT);

    pinMode(lightFront, INPUT);
    pinMode(lightBack, INPUT);
    
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    Serial.begin(9600);
    irrecv.enableIRIn(); // INICIA LA RECEPCIÓN

}

void loop(){
    long distance;
    long duration;

    digitalWrite(trig, LOW);
    delayMicroseconds(4);
    digitalWrite(trig, HIGH);

    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    duration = duration / 2;
    distance = duration / 29;
    if (irrecv.decode(&codigo)){
    Serial.println(codigo.value, HEX);
      if(codigo.value == 0xE0E040BF){
          on = true;    
          motorMode(A0,A1, true);
          motorMode(A2,A3, true);
          delay(500);
      }

      if(codigo.value == 0xE4CD1208){
          on = false;   
        }
     irrecv.resume();
    }

    if(on == true){
      Serial.println(distance);
      if(distance <= 20 && distance > 0){
        found = true;
      } 
      else if(digitalRead(lightFront) == LOW && digitalRead(lightBack) == HIGH){
            motorMode(A1,A0, true);
            motorMode(A3,A2, true);
            found = false;
            delay(500);
          } 
      else if(digitalRead(lightBack) == LOW && digitalRead(lightFront) == HIGH){
            motorMode(A0,A1, true);
            motorMode(A3,A2, true);
            found = false;
            delay(500);
       }
     else if (digitalRead(lightBack) == LOW && digitalRead(lightFront) == LOW){
        on = false; 
      }
      else {
        motorMode(A0, A1, true);
        motorMode(A2, A3, false);
      }
      
    if(found == true){
            motorMode(A0,A1, true);
            motorMode(A2,A3, true);
     }
    } else {
      motorMode(A0, A1, false);
      motorMode(A2, A3, false);
    }

   
}
