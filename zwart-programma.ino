#include <Servo.h>    //voegt de library's toe die nodig zijn om het allemaal werkend te krijgen.

Servo servoL; // voegt servo Links toe.
Servo servoR; // voegt servo Rechts toe.
Servo servoA; // voegt servo voor wegwerpen blikje toe.

int i = 200; // deze waarde gebruiken we om te definiëren of een sensor licht ziet.

int voorg; // voegt variabele voor getal toe.
int rechtsg; // voegt variabele rechts getal toe.
int linksg; // voegt variabele links getal toe.
int achterg; // voegt variabele achter getal toe.
int afstand; // voegt variabele afstand getal toe.
int tellerdraai = 0; // voegt variabele teller toe voor links of rechts draaien.
int tellerafstanduit = 0; // voegt variabele tellerafstanduit toe voor aan en uit zetten voor servoA.
int tellerafstanddelay = 60; // voegt variabele tellerafstanddelay toe voor delay voordat hij de servo weer omlaag zet.

// benodigheden voordat we in de loop gaan. Hier geven we alle pins aan.
void setup(){
  
  Serial.begin(9600);
  
  servoL.attach(11); // koppelt servoL aan pin 11.
  servoR.attach(10); // koppelt servoR aan pin 10.
  servoA.attach(2); // koppelt servoA aan pin 2.

  // Hier koppelen we pins aan input of output. 
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT); 

  servoA.writeMicroseconds(1600); // zet servoA omhoog.
  
}

// Rijprogramma loop.
void loop(){

  // Kijk waar de lichtsensoren op zitten.
  Lightcheckall();
  
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
//  Serial.print("afstand is scuffed = ");
//  Serial.println(afstand);

// na een delay van 4500ms zet servoA omhoog.
if(tellerafstanddeuit == 45){
  
    digitalWrite(13, LOW); // laat stokje stoppen.
    servoA.writeMicroseconds(1600); // positie omhoog.
    tellerafstanduit = 0; // reset tellerafstanduit
    
}

// als hij iets ziet en 6 seconden zijn al geweest nadat hij hierin kwam, zet servo omlaag.
else if(afstand>280 && (tellerafstanddelay > 60)){
//  Serial.print("afstand is scuffed in functie = ");
//  Serial.println(afstand);
  stil(); // sta stil om aan te geven dat je een obstakel ziet.
  
  servoA.writeMicroseconds(1600); // positie omhoog.
  
  delay(1000); // wacht 1 seconde.
  
  digitalWrite(13, HIGH); // laat stokje draaien.
  servoA.writeMicroseconds(700); // positie omlaag.
  
  delay(2000); // wacht 2 seconden.
  
  tellerafstanddelay = 0; // reset tellerafstanddelay.
}

// als hij links, rechts en achter ziet.
if((linksg>i) && (rechtsg>i) && (achterg>i)){
  
  voor(); // rechtdoor.
}

// als hij voor en achter ziet.
else if((voorg>i) && (achterg>i)){
  
  voor(); // rechtdoor.
}

// als hij alleen links ziet.
else if(linksg>i){

  // zolang hij voor niet ziet.
  while(voorg<i){ 

    // als het 250ms heeft geduurt voor het vinden van voor.
    if(tellerdraai>25){
      slinks(); // draai scherp links.
      Checkall(); // check alles.
      delay(10); // wacht 10ms.
    }

    // als hij net een bocht heeft gevonden.
    else{
      links(); // draai links.
      Checkall(); // check alles.
      delay(10); // wacht 10ms.
      
      tellerdraai++; // optellen variabele tellerdraai.
    }
  }
  
  tellerdraai = 0; // reset tellerdraai.
  
}

// als hij alleen rechts ziet.
else if(rechtsg>i){

  // zolang hij niet voor ziet.
  while(voorg<i){

    // als het 250ms heeft geduurt voor het vinden van voor.
    if(tellerdraai>25){
      srechts(); // draai scherp rechts.
      Checkall(); // check alles.
      delay(10); // wacht 10ms.
    }

    // als hij net een bocht heeft gevonden.
    else{
      rechts();  // draai rechts.
      Checkall(); // check alles.
      delay(10); // wacht 10ms.
      tellerdraai++; // optellen variabele tellerdraai.
    }
  }
  
  tellerdraai = 0; // reset tellerdraai.

}

// als hij alleen voor ziet.
else if(voorg>i){
  
  voor(); // rechtdoor.
  
}

// als hij alleen achter ziet.
else if(achterg>i){

  // zolang hij achter ziet, zoek naar links of rechts.
  while(achterg>i){
    achter(); // achteruit rijden.
    Checkall(); // check alles.
    delay(10); // wacht 10ms.

    // als hij links eerst ziet.
    if(linksg>i){
      slinks(); // scherp naar links.
      delay(750); // wacht 750ms.
      
      break; // ga uit de loop, want hij heeft links gevonden.
    }

    // als hij rechts eerst ziet.
    else if(rechtsg>i){
      srechts(); // scherp naar rechts.
      delay(750); // wacht 750ms.
      
      break; // ga uit de loop, want hij heeft rechts gevonden.
    }
  }
}

// als hij geen van de condities boven heeft voldaan.
else{
  
  voor(); // rechtdoor.

}

tellerafstanduit++; // optellen tellerafstanduit.
tellerafstanddelay++; // optellen tellerafstanddelay.

LEDcheck(); // controleer LEDjes.

delay(100); // wacht 100ms.

}

// functie stilstaan.
int stil(){
  servoL.writeMicroseconds(1500);
  servoR.writeMicroseconds(1500);
}

// functie vooruit rijden.
int voor(){
  servoL.writeMicroseconds(1570);
  servoR.writeMicroseconds(1423);
}

// functie scherp rechts afslaan.
int srechts(){
  servoL.writeMicroseconds(1550);
  servoR.writeMicroseconds(1550);
}

// functie scherp links afslaan.
int slinks(){
  servoL.writeMicroseconds(1450);
  servoR.writeMicroseconds(1450);
}

// functie achteruitrijden.
int achter(){
  servoL.writeMicroseconds(1430);
  servoR.writeMicroseconds(1577);
}

// functie rechts afslaan.
int rechts(){
  servoL.writeMicroseconds(1550);
  servoR.writeMicroseconds(1500);
}

// functie links afslaan.
int links(){
  servoL.writeMicroseconds(1500);
  servoR.writeMicroseconds(1450);
}


// functies voor het checken van de LEDjes.
// functie LEDlinks.
int LEDlinks(){
  if(linksg>i){
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}

// functie LEDvoor.
int LEDvoor(){
  if(voorg>i){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
}

// functie LEDachter.
int LEDachter(){
  if(achterg>i){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }
}

// functie LEDrechts.
int LEDrechts(){
  if(rechtsg>i){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
}

// functie LEDcheck, om alle LEDjes te checken.
int LEDcheck(){
  LEDlinks();
  LEDvoor();
  LEDachter();
  LEDrechts();
}

// functie Lightcheckall, om alle lichtsensoren te checken.
int Lightcheckall(){
  achterg=analogRead(A1);
  linksg=analogRead(A2);
  rechtsg=analogRead(A3);
  voorg=analogRead(A4);
}

// functie Checkall, om alle sensoren te checken. Vooral om dubbele code te vermijden.
int Checkall(){
  Lightcheckall();
  LEDcheck();
  afstand=analogRead(A0);
}
