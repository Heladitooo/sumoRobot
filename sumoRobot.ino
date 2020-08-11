#include <IRremote.h>
IRrecv irrecv(4);
decode_results code;

int echo = 3;
int trig = 2;
int receptor = 4;
bool on = false;
int lightFront = 5;
int lightBack = 6;

bool found = false;

//Función para trabajar los 2 motores
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
    irrecv.enableIRIn();

}

void loop(){

    //Detección del sensor ultrasónico
    
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
    
    //----------------------------------


 
    //Detencción del receptor inflarrojo
    
    if (irrecv.decode(&code)){
    
      if(codigo.value == 0xE0E040BF){
          //arranca con 500 segundos hacia adelante para buscar
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
    
    //----------------------------

    
    if(on == true){

     
      if(distance <= 20 && distance > 0){
        //si el sensor ultrasónico encuentra algo
        found = true;
      } 
      else if(digitalRead(lightFront) == LOW && digitalRead(lightBack) == HIGH){
            //se sale por delante
            motorMode(A1,A0, true);
            motorMode(A3,A2, true);
            found = false;
            delay(500);
      } 
      else if(digitalRead(lightBack) == LOW && digitalRead(lightFront) == HIGH){
            //se sale por atras
            motorMode(A0,A1, true);
            motorMode(A3,A2, true);
            found = false;
            delay(500);
      }
      else if (digitalRead(lightBack) == LOW && digitalRead(lightFront) == LOW){
        //se sale por los dos lados
        on = false; 
      }
      else {
        //estado normal al buscar
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
