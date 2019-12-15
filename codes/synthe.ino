#include <CapacitiveSensor.h>

// ----- SETTINGS -----
// Baud rate. Should be the same in synthe.py
const int baudRate = 9600;

// Connections to LEDs
const char OctaveLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const char OctaveChangeConfirmation = 11;

// Connections between the keyboard and your Arduino:
const char pinDO[]  = {22, 23};
const char pinREb[] = {24, 25};
const char pinRE[]  = {26, 27};
const char pinMIb[] = {28, 29};
const char pinMI[]  = {30, 31};
const char pinFA[]  = {32, 33};
const char pinFAd[] = {34, 35};
const char pinSOL[] = {36, 37};
const char pinLAb[] = {38, 39};
const char pinLA[]  = {40, 41};
const char pinSIb[] = {42, 43};
const char pinSI[]  = {44, 45};
const char pinNextOctave[] = {46, 47};
const char pinPrevOctave[] = {48, 49};
// ----- END SETTINGS -----

// Initializing capacitive sensors for every tile of the keyboard
// according to above settings
CapacitiveSensor sensorDO  = CapacitiveSensor(pinDO[0],pinDO[1]);
CapacitiveSensor sensorREb = CapacitiveSensor(pinREb[0],pinREb[1]);
CapacitiveSensor sensorRE  = CapacitiveSensor(pinRE[0],pinRE[1]);
CapacitiveSensor sensorMIb = CapacitiveSensor(pinMIb[0],pinMIb[1]);
CapacitiveSensor sensorMI  = CapacitiveSensor(pinMI[0],pinMI[1]);
CapacitiveSensor sensorFA  = CapacitiveSensor(pinFA[0],pinFA[1]);
CapacitiveSensor sensorFAd = CapacitiveSensor(pinFAd[0],pinFAd[1]);
CapacitiveSensor sensorSOL = CapacitiveSensor(pinSOL[0],pinSOL[1]);
CapacitiveSensor sensorLAb = CapacitiveSensor(pinLAb[0],pinLAb[1]);
CapacitiveSensor sensorLA  = CapacitiveSensor(pinLA[0],pinLA[1]);
CapacitiveSensor sensorSIb = CapacitiveSensor(pinSIb[0],pinSIb[1]);
CapacitiveSensor sensorSI  = CapacitiveSensor(pinSI[0],pinSI[1]);
CapacitiveSensor sensorOctaveSuiv = CapacitiveSensor(pinNextOctave[0],pinNextOctave[1]);
CapacitiveSensor sensorOctavePrec = CapacitiveSensor(pinPrevOctave[0],pinPrevOctave[1]);

//Front montant
boolean DO  = 0;
boolean REb = 0;
boolean RE  = 0;
boolean MIb = 0;
boolean MI  = 0;
boolean FA  = 0;
boolean FAd = 0;
boolean SOL = 0;
boolean LAb = 0;
boolean LA  = 0;
boolean SIb = 0;
boolean SI  = 0;
boolean OctaveSuiv = 0;
boolean OctavePrec = 0;

//Etat de chaque touche
boolean DOtmp  = 0;
boolean REbtmp = 0;
boolean REtmp  = 0;
boolean MIbtmp = 0;
boolean MItmp  = 0;
boolean FAtmp  = 0;
boolean FAdtmp = 0;
boolean SOLtmp = 0;
boolean LAbtmp = 0;
boolean LAtmp  = 0;
boolean SIbtmp = 0;
boolean SItmp  = 0;
boolean OctaveSuivtmp = 0;
boolean OctavePrectmp = 0;

//configuration des octaves
char octaveMax = 8;
char octaveMin = 0;
char octaveDef = 3;

char octave = octaveDef;

//configuration de la sensibilité des touches
char precision = 15;
int seuilDeDetection = 250;
char dataString[50] = {0};

//LED 11 (bip de 50ms à chaque changement d'octave)
unsigned long heureAllumageLED11 = 0;
boolean EtatLED11 = 0;

unsigned long lastOctaveSuiv = 0;
unsigned long lastOctavePrec = 0;

void setup() {
  Serial.begin(baudRate);
  
  pinMode(OctaveLEDs[0], OUTPUT);
  pinMode(OctaveLEDs[1], OUTPUT);
  pinMode(OctaveLEDs[2], OUTPUT);
  pinMode(OctaveLEDs[3], OUTPUT);
  pinMode(OctaveLEDs[4], OUTPUT);
  pinMode(OctaveLEDs[5], OUTPUT);
  pinMode(OctaveLEDs[6], OUTPUT);
  pinMode(OctaveLEDs[7], OUTPUT);
  pinMode(OctaveLEDs[8], OUTPUT);

  pinMode(OctaveChangeConfirmation, OUTPUT);

  digitalWrite(OctaveLEDs[octave], 1);
}

void loop() {
  actualiser();//fonction pour actualiser les variables telles que "DOtmp"

  changerOctave();//Fonction pour actualiser l'octave

  envoyerNotes();//fonction pour actualiser les variables telles que "DO" et les envoyer
}

void envoi(int n) {
  sprintf(dataString,"%02X",n);
  Serial.println(dataString);
}



void envoyerNotes() {
  if (DOtmp != DO && DOtmp == 1 && octave != 0) {
    int x = 4 + ( (octave-1) * 12 );
    envoi(x);
  }
  DO = DOtmp;
  
  if (REbtmp != REb && REbtmp == 1 && octave != 0 && octave != 8) {
    int x = 5 + ( (octave-1) * 12 );
    envoi(x);
  }
  REb = REbtmp;

  if (REtmp != RE && REtmp == 1 && octave != 0 && octave != 8) {
    int x = 6 + ( (octave-1) * 12 );
    envoi(x);
  }
  RE = REtmp;

  if (MIbtmp != MIb && MIbtmp == 1 && octave != 0 && octave != 8) {
    int x = 7 + ( (octave-1) * 12 );
    envoi(x);
  }
  MIb = MIbtmp;

  if (MItmp != MI && MItmp == 1 && octave != 0 && octave != 8) {
    int x = 8 + ( (octave-1) * 12 );
    envoi(x);
  }
  MI = MItmp;

  if (FAtmp != FA && FAtmp == 1 && octave != 0 && octave != 8) {
    int x = 9 + ( (octave-1) * 12 );
    envoi(x);
  }
  FA = FAtmp;

  if (FAdtmp != FAd && FAdtmp == 1 && octave != 0 && octave != 8) {
    int x = 10 + ( (octave-1) * 12 );
    envoi(x);
  }
  FAd = FAdtmp;

  if (SOLtmp != SOL && SOLtmp == 1 && octave != 0 && octave != 8) {
    int x = 11 + ( (octave-1) * 12 );
    envoi(x);
  }
  SOL = SOLtmp;

  if (LAbtmp != LAb && LAbtmp == 1 && octave != 0 && octave != 8) {
    int x = 12 + ( (octave-1) * 12 );
    envoi(x);
  }
  LAb = LAbtmp;

  if (LAtmp != LA && LAtmp == 1 && octave != 8) {
    int x = 1 + ( octave * 12 );
    envoi(x);
  }
  LA = LAtmp;

  if (SIbtmp != SIb && SIbtmp == 1 && octave != 8) {
    int x = 2 + ( octave * 12 );
    envoi(x);
  }
  SIb = SIbtmp;

  if (SItmp != SI && SItmp == 1 && octave != 8) {
    int x = 3 + ( octave * 12 );
    envoi(x);
  }
  SI = SItmp;
}

void changerOctave() {
  unsigned long Time = millis();
  if (EtatLED11 == 1 && Time - heureAllumageLED11 > 50) {
    EtatLED11 = 0;
    digitalWrite(OctaveChangeConfirmation, 0);
  }
  
  if (OctaveSuivtmp != OctaveSuiv && OctaveSuivtmp == 1 && octave < octaveMax && Time - lastOctaveSuiv > 150) {
    heureAllumageLED11 = Time;
    digitalWrite(OctaveChangeConfirmation, 1);
    EtatLED11 = 1;
    lastOctaveSuiv = Time;
    digitalWrite(OctaveLEDs[octave], 0);
    octave++;
    digitalWrite(OctaveLEDs[octave], 1);
  }
  OctaveSuiv = OctaveSuivtmp;

  if (OctavePrectmp != OctavePrec && OctavePrectmp == 1 && octave > octaveMin && Time - lastOctavePrec > 150) {
    heureAllumageLED11 = Time;
    digitalWrite(OctaveChangeConfirmation, 1);
    EtatLED11 = 1;
    lastOctavePrec = Time;
    digitalWrite(OctaveLEDs[octave], 0);
    octave--;
    digitalWrite(OctaveLEDs[octave], 1);
  }
  OctavePrec = OctavePrectmp;
}


void actualiser() {
  if (sensorDO.capacitiveSensor(precision) >= seuilDeDetection) {
    DOtmp = 1;
  }
  else {
    DOtmp = 0;
  }

  if (sensorREb.capacitiveSensor(precision) >= seuilDeDetection) {
    REbtmp = 1;
  }
  else {
    REbtmp = 0;
  }

  if (sensorRE.capacitiveSensor(precision) >= seuilDeDetection) {
    REtmp = 1;
  }
  else {
    REtmp = 0;
  }

  if (sensorMIb.capacitiveSensor(precision) >= seuilDeDetection) {
    MIbtmp = 1;
  }
  else {
    MIbtmp = 0;
  }

  if (sensorMI.capacitiveSensor(precision) >= seuilDeDetection) {
    MItmp = 1;
  }
  else {
    MItmp = 0;
  }

  if (sensorFA.capacitiveSensor(precision) >= seuilDeDetection) {
    FAtmp = 1;
  }
  else {
    FAtmp = 0;
  }

  if (sensorFAd.capacitiveSensor(precision) >= seuilDeDetection) {
    FAdtmp = 1;
  }
  else {
    FAdtmp = 0;
  }
  
  if (sensorSOL.capacitiveSensor(precision) >= seuilDeDetection) {
    SOLtmp = 1;
  }
  else {
    SOLtmp = 0;
  }

   if (sensorLAb.capacitiveSensor(precision) >= seuilDeDetection) {
    LAbtmp = 1;
  }
  else {
    LAbtmp = 0;
  }

  if (sensorLA.capacitiveSensor(precision) >= seuilDeDetection) {
    LAtmp = 1;
  }
  else {
    LAtmp = 0;
  }

  if (sensorSIb.capacitiveSensor(precision) >= seuilDeDetection) {
    SIbtmp = 1;
  }
  else {
    SIbtmp = 0;
  }

  if (sensorSI.capacitiveSensor(precision) >= seuilDeDetection) {
    SItmp = 1;
  }
  else {
    SItmp = 0;
  }
  
  if (sensorOctaveSuiv.capacitiveSensor(precision) >= seuilDeDetection) {
    OctaveSuivtmp = 1;
  }
  else {
    OctaveSuivtmp = 0;
  }

  if (sensorOctavePrec.capacitiveSensor(precision) >= seuilDeDetection) {
    OctavePrectmp = 1;
  }
  else {
    OctavePrectmp = 0;
  }
}
