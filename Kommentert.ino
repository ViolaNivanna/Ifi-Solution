/*
Kode for prototypen til Ifi Solution
2.6.2022
*/

// Variabler
// Pin-plasseringene til fuktighetsmaalerne 
int sensorPinTop = A0; 
int sensorPinBunn = A1;

// Verdiene til fuktighetsmaalerne
int sensorValueBunn;
int sensorValueTop; 
 
// Pin-plasseringene til LED-lysene
int lyspin1 = 11;
int lyspin2 = 12;
int lyspin3 = 13;

/* 
Fuktighetsmaalerne er av forskjellige modeller. 
Den ene er torr naar den viser 0, den andre naar den viser 1023.
Derfor har de forskjellige grenser paa torr og kjempeTorr.
*/
// Fuktighetsmaaleren som er paa bunnen
int bunnTorr = 300;
int bunnKjempeTorr = 200;

// Fuktighetsmaaleren som er paa toppen
int topTorr = 700;
int topKjempeTorr = 800;

// Delay paa loopen som gjoer at maalingene ikke skjer for ofte
int timer = 1000;


void setup() {
 Serial.begin(9600);
 pinMode(11,OUTPUT);
 pinMode(12,OUTPUT);
 pinMode(13,OUTPUT);
 
}

// Metode som sjekker fuktigheten i maaleren paa bunnen
void sjekkBunn(){

  /*
  Hvis maalerens verdi er mindre enn 200, er jorden for torr.
  Da MAA planten vannes og varsler det ved at lysene blinker.
  */
  if (sensorValueBunn < bunnKjempeTorr){
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  
    delay(250);
  
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  
    delay(250);

    // Maalingene skjer hyppig for registrere endringer raskt
    timer = 500;
    
  }
  
  /* 
  Ellers, hvis maalerens verdi er mindre enn 300, men over 200,
  maa planten vannes, men det haster ikke.
  Dette signaliseres ved at lysene lyser, men ikke blinker.
  */
  else if (sensorValueBunn < bunnTorr){
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);

    // Maalingene trenger ikke aa skje like ofte som naar den er veldig torr
    timer = 2000;
  }
  
  // Ellers er ikke jorden saa torr at det behoves vanning og lysene er av
  else{
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);

    // Maalingene kan skje enda sjeldnere
    timer = 10000;
  }
}

// Metode som endrer timeren og skrur av lysene hvis planten blir vannet
void setTimer(){
  /*
  Hvis verdien til maaleren paa toppen er lavere enn torr, 
  vil det si at planten er fuktig nok, altsaa at den har blitt vannet.
  Timeren oekes, slik at der er lenge til neste refistrering av bunnmaaleren.
  Dette gjoer at vannet kan rekke aa trekke ned til bunnmaleren, 
  slik at lysene ikke begynner aa blinke selv om planten har faatt vann.
  Jord i potter pleier aa torke i toppen foer bunnen, 
  derfor kan vanning maales paa denne maaten
  */
  if (sensorValueTop < topTorr){

    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  
    timer = 10000; 
  }
}


void loop() {

 sensorValueTop = analogRead(sensorPinTop); 
 sensorValueBunn = analogRead(sensorPinBunn); 

 Serial.println("Analog Value Top : ");
 Serial.println(sensorValueTop);

 Serial.println("Analog Value Bunn : ");
 Serial.println(sensorValueBunn);

 sjekkBunn();
 setTimer(); // Mulig at denne egentlig skal brukes inne i sjekkBunn

 // Loopen bruker delay for aa styre hvor forte maalingene skal skje
 delay(timer); 
}
