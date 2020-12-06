/// PROJECT :: MIDI controller with 8 capacitive pads.
/// Author....................Gautier Reynes (2020)
/// GitHub.....................github.com/Gautier30
/// Current version.............................1.0
/// Features...........................8 touch-pads
/// ......................3 potentiometers/encoders
/// ...........................1 switch (transpose)
/// To do.......................reduce pads latency
//// Please credit me if this code is reused \\\\
//////////////////////////////////////////////////////////
//Define here all the useful variables.
//Touchpads
int Tv1;
int Tv2;
int Tv3;
int Tv4;
int Tv5;
int Tv6;
int Tv7;
int Tv8;
int t1 = 0;
int t2 = 0;
int t3 = 0;
int t4 = 0;
int t5 = 0;
int t6 = 0;
int t7 = 0;
int t8 = 0;
int midC = 60;
//////////////////////////////////////////////////////////
//Switch
#define switchL 22
#define switchR 23
int octave = 0;
//////////////////////////////////////////////////////////
//Potentiometers
#define Pot1 34
#define Pot2 35
#define Pot3 26
int Pv1_new;
int Pv2_new;
int Pv3_new;
int Pv1_old = 0;
int Pv2_old = 0;
int Pv3_old = 0;
int pDelta1;
int pDelta2;
int pDelta3;
int pThresh = 3;
//////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(switchL, INPUT);
  pinMode(switchR, INPUT);
}
//////////////////////////////////////////////////////////
void loop() {
  for(int i=0; i<10; i++){
    Tv1 += touchRead(T8);
    Tv2 += touchRead(T9);
    Tv3 += touchRead(T6);
    Tv4 += touchRead(T4);
    Tv5 += touchRead(T0);
    Tv6 += touchRead(T7);
    Tv7 += touchRead(T5);
    Tv8 += touchRead(T3);  
  }
  Switch();
  Tv1=Tv1/20;
  Tv2=Tv2/20;
  Tv3=Tv3/20;
  Tv4=Tv4/20;
  Tv5=Tv5/20;
  Tv6=Tv6/20;
  Tv7=Tv7/20;
  Tv8=Tv8/20;
  Touch();
  Pot();
}
//////////////////////////////////////////////////////////
//MIDI message function
void MIDIMessage(byte status, byte data1, byte data2){
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}
//////////////////////////////////////////////////////////
//Potentiometer function
void Pot(){
    Pv1_new = analogRead(Pot1);
    Pv1_new = map(Pv1_new, 0, 4095, 0, 127);
    pDelta1 = abs(Pv1_new - Pv1_old);
    if(pDelta1>pThresh){
      MIDIMessage(177, 0, Pv1_new);
      Pv1_old = Pv1_new;
    }
    
    Pv2_new = analogRead(Pot2);
    Pv2_new = map(Pv2_new, 0, 4095, 0, 127);
    pDelta2 = abs(Pv2_new - Pv2_old);
    if(pDelta2>pThresh){
      MIDIMessage(177, 1, Pv2_new);
      Pv2_old = Pv2_new;
    }
      
    Pv3_new = analogRead(Pot3);
    Pv3_new = map(Pv3_new, 0, 4095, 0, 127);
    pDelta3 = abs(Pv3_new - Pv3_old);
    if(pDelta3>pThresh){
      MIDIMessage(177, 2, Pv3_new);
      Pv3_old = Pv3_new;
    }
}
//////////////////////////////////////////////////////////
//Switch function
void Switch(){
  if(digitalRead(switchL)==HIGH){
    octave = -12;
  }
  if(digitalRead(switchR)==HIGH){
    octave = 12;
  }
  if(digitalRead(switchL)==LOW && digitalRead(switchR)==LOW){
    octave = 0;
  }
}
//////////////////////////////////////////////////////////
//Touchpad function
void Touch(){
//------------------------------------  
  //Pad#1
  if(Tv1 < 20){
    if(t1 != 1){
      MIDIMessage(144, midC + 0 + octave, 127);
      t1 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 0 + octave, 0);
    t1 = 0;
  }
//------------------------------------  
  //Pad#2 
  if(Tv2 < 15){
    if(t2 != 1){
      MIDIMessage(144, midC + 1 + octave, 127);
      t2 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 1 + octave, 0);
    t2 = 0;
  }
//------------------------------------  
  //Pad#3
  if(Tv3 < 20){
    if(t3 != 1){
      MIDIMessage(144, midC + 2 + octave, 127);
      t3 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 2 + octave, 0);
    t3 = 0;
  }
//------------------------------------  
  //Pad#4
  if(Tv4 < 20){
    if(t4 != 1){
      MIDIMessage(144, midC + 3 + octave, 127);
      t4 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 3 + octave, 0);
    t4 = 0;
  }
//------------------------------------  
  //Pad#5
  if(Tv5 < 20){
    if(t5 != 1){
      MIDIMessage(144, midC + 4 + octave, 127);
      t5 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 4 + octave, 0);
    t5 = 0;
  }
//------------------------------------  
  //Pad#6
  if(Tv6 < 20){
    if(t6 != 1){
      MIDIMessage(144, midC + 5 + octave, 127);
      t6 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 5 + octave, 0);
    t6 = 0;
  }
//------------------------------------  
  //Pad#7
  if(Tv7 < 20){
    if(t7 != 1){
      MIDIMessage(144, midC + 6 + octave, 127);
      t7 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 6 + octave, 0);
    t7 = 0;
  }
//------------------------------------  
  //Pad#8
  if(Tv8 < 20){
    if(t8 != 1){
      MIDIMessage(144, midC + 7 + octave, 127);
      t8 = 1;
    }
  }
  else{
    MIDIMessage(144-16, midC + 7 + octave, 0);
    t8 = 0;
  }
}
