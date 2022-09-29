#include <Servo.h>

Servo servo1; //base (Grados de 0 a 180)
Servo servo2; //brazo (Grados de 0 a 160) Siempre y cuando el s3 este en 0 grados.
Servo servo3; //antebrazo (Grados de 0 a 120 ) siempre que S2 > 60
Servo servo4; //pinza (Grados de 0 a 80)

int pinservo1 = 2;
int pinservo2 = 4;
int pinservo3 = 7;
int pinservo4 = 10;

void setup() {
  servo1.attach(pinservo1, 610, 2550);
  servo2.attach(pinservo2, 670, 2540);
  servo3.attach(pinservo3, 660, 2600);
  servo4.attach(pinservo4, 660, 2600);
  pinMode(pinservo1, OUTPUT);
  pinMode(pinservo2, OUTPUT);
  pinMode(pinservo3, OUTPUT);
  pinMode(pinservo4, OUTPUT);
  Serial.begin(9600);
}

void doInstruction( String aServo, int aDeg ){

   if( aServo == "s1" ){
    servo1.write(aDeg);  
   } else if( aServo == "s2" ){
    servo2.write(aDeg);  
   } else if( aServo == "s3" ){
    servo3.write(aDeg);  
   } else if( aServo == "s4" ){
    servo4.write(aDeg);  
   }
   Serial.println("todo bien perros");
  

}



bool unCiclo = true;


void loop() {
  
if( unCiclo ){
  unCiclo = false;
  servo3.write(90);
  servo2.write(150);
  delay(200);  
} 

if ( Serial.available() > 0 ){
  String data = Serial.readString();  //read until timeout
  data.trim();// remove any \r \n whitespace at the end of the String

  if ( data.length() == 6 ){
    String servoSerial = data.substring(0,2);
    int grados = data.substring(3,6).toInt();
    
    Serial.println( servoSerial );
    Serial.println( grados );    
    doInstruction( servoSerial, grados);
  } else {
    Serial.println("\n-------------------\nFatal instruction. \nGuide: s3d180\n-------------------");
  }

  
}

}
