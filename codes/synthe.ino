#include <CapacitiveSensor.h>

// ----- SETTINGS -----
// Baud rate. Should be the same in synthe.py
const int baudRate = 9600;

// Connections to LEDs
const char OctaveLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

//Octave change confirmation LED :(ON during 50ms after each octave change)
const char LEDOCC = 11;

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

// Octave configuration
const char octaveMax = 8;
const char octaveMin = 0;
const char octaveDef = 3; // Default

// Sensitivity configuration (increasing accuracy causes latency)
char accuracy = 15;
int threshold = 250;


// ----- END SETTINGS -----

// Initializing capacitive sensors for every key of the keyboard
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
CapacitiveSensor sensorNextOctave = CapacitiveSensor(pinNextOctave[0],pinNextOctave[1]);
CapacitiveSensor sensorPrevOctave = CapacitiveSensor(pinPrevOctave[0],pinPrevOctave[1]);

//Rising edges:
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
boolean NextOctave = 0;
boolean PrevOctave = 0;

//State of every piano key:
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
boolean NextOctavetmp = 0;
boolean PrevOctavetmp = 0;

char octave = octaveDef;
char dataString[50] = {0};
boolean StateLEDOCC = 0;

// "timers"
unsigned long ToggleTimeLEDOCC = 0;
unsigned long ToggleTimeNextOctave = 0;
unsigned long ToggleTimePrevOctave = 0;

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

  pinMode(LEDOCC, OUTPUT);

  digitalWrite(OctaveLEDs[octave], 1);
}

void loop() {
  refresh();//refresh variables such as "DOtmp"

  changeOctave();//refresh octave

  sendNotes();//refresh variables such as "DO" and send them via serial
}

void envoi(int n) {
  sprintf(dataString,"%02X",n);
  Serial.println(dataString);
}



void sendNotes() {
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

void changeOctave() {
  unsigned long Time = millis();
  if (StateLEDOCC == 1 && Time - ToggleTimeLEDOCC > 50) {
    StateLEDOCC = 0;
    digitalWrite(LEDOCC, 0);
  }
  
  if (NextOctavetmp != NextOctave && NextOctavetmp == 1 && octave < octaveMax && Time - ToggleTimeNextOctave > 150) {
    ToggleTimeLEDOCC = Time;
    ToggleTimeNextOctave = Time;
    digitalWrite(LEDOCC, 1);
    StateLEDOCC = 1;
    digitalWrite(OctaveLEDs[octave], 0);
    octave++;
    digitalWrite(OctaveLEDs[octave], 1);
  }
  NextOctave = NextOctavetmp;

  if (PrevOctavetmp != PrevOctave && PrevOctavetmp == 1 && octave > octaveMin && Time - ToggleTimePrevOctave > 150) {
    ToggleTimeLEDOCC = Time;
    ToggleTimePrevOctave = Time;
    digitalWrite(LEDOCC, 1);
    StateLEDOCC = 1;
    digitalWrite(OctaveLEDs[octave], 0);
    octave--;
    digitalWrite(OctaveLEDs[octave], 1);
  }
  PrevOctave = PrevOctavetmp;
}


void refresh() {
  if (sensorDO.capacitiveSensor(accuracy) >= threshold) {
    DOtmp = 1;
  }
  else {
    DOtmp = 0;
  }

  if (sensorREb.capacitiveSensor(accuracy) >= threshold) {
    REbtmp = 1;
  }
  else {
    REbtmp = 0;
  }

  if (sensorRE.capacitiveSensor(accuracy) >= threshold) {
    REtmp = 1;
  }
  else {
    REtmp = 0;
  }

  if (sensorMIb.capacitiveSensor(accuracy) >= threshold) {
    MIbtmp = 1;
  }
  else {
    MIbtmp = 0;
  }

  if (sensorMI.capacitiveSensor(accuracy) >= threshold) {
    MItmp = 1;
  }
  else {
    MItmp = 0;
  }

  if (sensorFA.capacitiveSensor(accuracy) >= threshold) {
    FAtmp = 1;
  }
  else {
    FAtmp = 0;
  }

  if (sensorFAd.capacitiveSensor(accuracy) >= threshold) {
    FAdtmp = 1;
  }
  else {
    FAdtmp = 0;
  }
  
  if (sensorSOL.capacitiveSensor(accuracy) >= threshold) {
    SOLtmp = 1;
  }
  else {
    SOLtmp = 0;
  }

   if (sensorLAb.capacitiveSensor(accuracy) >= threshold) {
    LAbtmp = 1;
  }
  else {
    LAbtmp = 0;
  }

  if (sensorLA.capacitiveSensor(accuracy) >= threshold) {
    LAtmp = 1;
  }
  else {
    LAtmp = 0;
  }

  if (sensorSIb.capacitiveSensor(accuracy) >= threshold) {
    SIbtmp = 1;
  }
  else {
    SIbtmp = 0;
  }

  if (sensorSI.capacitiveSensor(accuracy) >= threshold) {
    SItmp = 1;
  }
  else {
    SItmp = 0;
  }
  
  if (sensorNextOctave.capacitiveSensor(accuracy) >= threshold) {
    NextOctavetmp = 1;
  }
  else {
    NextOctavetmp = 0;
  }

  if (sensorPrevOctave.capacitiveSensor(accuracy) >= threshold) {
    PrevOctavetmp = 1;
  }
  else {
    PrevOctavetmp = 0;
  }
}
