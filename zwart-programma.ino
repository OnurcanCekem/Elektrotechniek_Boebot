#include <Servo.h>    //voegt de library's toe die nodig zijn om het allemaal werkend te krijgen.

Servo servoL; // voegt servo Links toe.
Servo servoR; // voegt servo Rechts toe.
Servo servoA; // voegt servo voor wegwerpen blikje toe.
int i = 200; // deze waarde gebruiken we om te definiëren 
int voorg;
int rechtsg;
int linksg;
int achterg;
int afstand;
int tellerdraai = 0;
int tellerafstanduit = 0;
int tellerafstanddelay = 60;

void setup(){
  Serial.begin(9600);
  servoL.attach(11);    //koppelt servoL aan pin 11
  servoR.attach(10);    //koppelt servoR aan pin 10
  servoA.attach(2);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  
  servoA.writeMicroseconds(1600);
}

void loop(){
  afstand=analogRead(A0);
  voorg=analogRead(A4);
  rechtsg=analogRead(A3);
  linksg=analogRead(A2);
  achterg=analogRead(A1);
//  Serial.print("afstand = ");
//  Serial.println(afstand);
//  Serial.print("voor = ");
//  Serial.println(voorg);
//  Serial.print("rechts = ");
//  Serial.println(rechtsg);
//  Serial.print("links = ");
//  Serial.println(linksg);
//  Serial.print("achter = ");
//  Serial.println(achterg);
  Serial.print("afstand is scuffed = ");
  Serial.println(afstand);
//if((afstand>250)&& (afstand<300) ){

if(tellerafstanduit == 45){
    digitalWrite(13, LOW);                //laat stokje stoppen
    servoA.writeMicroseconds(1600);       //positie omhoog
    tellerafstanduit = 0;
}

else if(afstand>280 && (tellerafstanddelay > 60)){
//  stil();
//  delay(100);
//  Checkall();
//  if(afstand>280){
    Serial.print("afstand is scuffed in functie = ");
    Serial.println(afstand);
    stil();
    servoA.writeMicroseconds(1600);       //positie omhoog
    delay(1000);
    digitalWrite(13, HIGH);               //laat stokje draaien
    servoA.writeMicroseconds(700);        //positie omlaag
    delay(2000);
    tellerafstanddelay = 0;
//  }
}

//if(afstand>250){
//  stil();
//  delay(100);
//  Checkall();
//  if(afstand>250){
//    voor();
//    delay(500);
//    achter();
//    delay(500);
//    slinks();
//    delay(500);
//    srechts();
//    delay(500);
//  }
//}

//if((linksg>i) && (rechtsg>i) && (voorg>i) && (achterg>i)){
//  voor();
//}

if((linksg>i) && (rechtsg>i) && (achterg>i)){
  voor(); 
}

else if((voorg>i) && (achterg>i)){
  voor();
}

else if(linksg>i){
  while(voorg<i){
    if(tellerdraai>25){
      slinks();
      Checkall();
      delay(10);
    }
    else{
      links();  
      Checkall();
      delay(10);
      tellerdraai++;
    }
  }
  tellerdraai = 0;
}

else if(rechtsg>i){
  while(voorg<i){
    if(tellerdraai>25){
      srechts();
      Checkall();
      delay(10);
    }
    else{
      rechts();  
      Checkall();
      delay(10);
      tellerdraai++;
    }
  }
  tellerdraai = 0;
}

else if(voorg>i){
  voor();
}

else if(achterg>i){
  while(achterg>i){
    achter();
    delay(10);
    Checkall();
    if(linksg>i){
      slinks();
      delay(750);
      break;
    }
    else if(rechtsg>i){
      srechts();
      delay(750);
      break;
    }
  }
}

//else if(achterg>i){
//  while(achterg>i){
//    achter();
//    delay(10);
//    Checkall();
//    if(linksg>i){
//      slinks();
//      delay(750);
//      voor();
//      delay(175);
//      while(voorg<i){
//        slinks();
//        delay(10);
//        Checkall();
//      }
//      break;
//    }
//    else if(rechtsg>i){
//      srechts();
//      delay(750);
//      voor();
//      delay(175);
//      while(voorg<i){
//        srechts();
//        delay(10);
//        Checkall();
//      }
//      break;
//    }
//  }
//  
//}

else{
  voor();
}

tellerafstanduit++;
tellerafstanddelay++;
LEDcheck();
delay(100);
}

int stil(){
  servoL.writeMicroseconds(1500);
  servoR.writeMicroseconds(1500);
}

int voor(){
  servoL.writeMicroseconds(1570);
  servoR.writeMicroseconds(1423);
}

int srechts(){
  servoL.writeMicroseconds(1550);
  servoR.writeMicroseconds(1550);
}

int slinks(){
  servoL.writeMicroseconds(1450);
  servoR.writeMicroseconds(1450);
}

int achter(){
  servoL.writeMicroseconds(1430);
  servoR.writeMicroseconds(1577);
}

int rechts(){
  servoL.writeMicroseconds(1550);
  servoR.writeMicroseconds(1500);
}

int links(){
  servoL.writeMicroseconds(1500);
  servoR.writeMicroseconds(1450);
}


int LEDlinks(){
  if(linksg>i){
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}

int LEDvoor(){
  if(voorg>i){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
}

int LEDachter(){
  if(achterg>i){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }
}

int LEDrechts(){
  if(rechtsg>i){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
}

int LEDcheck(){
  LEDlinks();
  LEDvoor();
  LEDachter();
  LEDrechts();
}

int Lightcheckall(){
  voorg=analogRead(A4);
  rechtsg=analogRead(A3);
  linksg=analogRead(A2);
  achterg=analogRead(A1);
}

int Checkall(){
  Lightcheckall();
  LEDcheck();
  afstand=analogRead(A0);
}
