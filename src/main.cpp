#include <Arduino.h>

int LEDrPin = 11;int LEDgPin = 10;int LEDbPin = 9;int matrixButtonR1pin = 6;
int matrixButtonR2pin = 7;int matrixButtonR3pin = 8;int matrixButtonR4pin = 12;int matrixButtonC1pin = 5;
int matrixButtonC2pin = 4;int matrixButtonC3pin = 3;int matrixButtonC4pin = 2;
int matrixButtonClicked[4][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};int matrixButtonGetRowPinByNumber[4] = {6, 7, 8, 12}; int matrixButtonState[2] = {1, 1};
int matrixButtonGetColumnPinByNumber[4] = {5, 4, 3, 2};

void matrixButtonRefreshSelected() {
  for(int i = 0; i < 4; i++) {
    digitalWrite(matrixButtonGetRowPinByNumber[i], HIGH);
  }
  digitalWrite(matrixButtonGetRowPinByNumber[matrixButtonState[0]-1], LOW);
}
int matrixButtonAddSelectedRow(int space) {
  int nextSelectedMatrixButton = matrixButtonState[0] + space;
  if(nextSelectedMatrixButton > 4) {nextSelectedMatrixButton = 1;}
  if(nextSelectedMatrixButton < 1) {nextSelectedMatrixButton = 4;}
  
  matrixButtonState[0] = nextSelectedMatrixButton;
  matrixButtonRefreshSelected();
}

void matrixButtonUpdateClicked() {
  for(int i = 0; i < 4; i++) {
    for(int i2 = 0; i2 < 4; i2++) {
      matrixButtonClicked[matrixButtonState[0]-1][i2] = digitalRead(matrixButtonGetColumnPinByNumber[i2]);
    }
    matrixButtonAddSelectedRow(1);
  }
}

void LEDsetColor(String color) {
  if(color=="crimson"){analogWrite(LEDrPin,220);analogWrite(LEDgPin,20);analogWrite(LEDbPin,60);}if(color=="emerald"){analogWrite(LEDrPin,80);analogWrite(LEDgPin,200);analogWrite(LEDbPin,120);}if(color=="sapphire"){analogWrite(LEDrPin,15);analogWrite(LEDgPin,82);analogWrite(LEDbPin,186);}if(color=="amber"){analogWrite(LEDrPin,255);analogWrite(LEDgPin,191);analogWrite(LEDbPin,0);}if(color=="violet"){analogWrite(LEDrPin,138);analogWrite(LEDgPin,43);analogWrite(LEDbPin,226);}if(color=="cyan"){analogWrite(LEDrPin,0);analogWrite(LEDgPin,255);analogWrite(LEDbPin,255);}if(color=="charcoal"){analogWrite(LEDrPin,54);analogWrite(LEDgPin,69);analogWrite(LEDbPin,79);}if(color=="rose"){analogWrite(LEDrPin,255);analogWrite(LEDgPin,102);analogWrite(LEDbPin,204);}if(color=="mint"){analogWrite(LEDrPin,152);analogWrite(LEDgPin,255);analogWrite(LEDbPin,152);}if(color=="indigo"){analogWrite(LEDrPin,75);analogWrite(LEDgPin,0);analogWrite(LEDbPin,130);}if(color=="peach"){analogWrite(LEDrPin,255);analogWrite(LEDgPin,218);analogWrite(LEDbPin,185);}if(color=="lime"){analogWrite(LEDrPin,191);analogWrite(LEDgPin,255);analogWrite(LEDbPin,0);}if(color=="coral"){analogWrite(LEDrPin,255);analogWrite(LEDgPin,127);analogWrite(LEDbPin,80);}if(color=="navy"){analogWrite(LEDrPin,0);analogWrite(LEDgPin,0);analogWrite(LEDbPin,128);}if(color=="olive"){analogWrite(LEDrPin,128);analogWrite(LEDgPin,128);analogWrite(LEDbPin,0);}if(color=="lavender"){analogWrite(LEDrPin,230);analogWrite(LEDgPin,230);analogWrite(LEDbPin,250);}

}
void setup() {
  pinMode(LEDrPin, OUTPUT); pinMode(LEDgPin, OUTPUT); pinMode(LEDbPin, OUTPUT);
  pinMode(matrixButtonR1pin, OUTPUT);pinMode(matrixButtonR2pin, OUTPUT);pinMode(matrixButtonR3pin, OUTPUT);
  pinMode(matrixButtonR4pin, OUTPUT);pinMode(matrixButtonC1pin, INPUT_PULLUP);
  pinMode(matrixButtonC2pin, INPUT_PULLUP);pinMode(matrixButtonC3pin, INPUT_PULLUP);
  pinMode(matrixButtonC4pin, INPUT_PULLUP);
  Serial.begin(250000);
}

void loop() {
  matrixButtonUpdateClicked();
  if(matrixButtonClicked[0][0]==0){LEDsetColor("crimson");}if(matrixButtonClicked[0][1]==0){LEDsetColor("emerald");}if(matrixButtonClicked[0][2]==0){LEDsetColor("sapphire");}if(matrixButtonClicked[0][3]==0){LEDsetColor("amber");}if(matrixButtonClicked[1][0]==0){LEDsetColor("violet");}if(matrixButtonClicked[1][1]==0){LEDsetColor("cyan");}if(matrixButtonClicked[1][2]==0){LEDsetColor("charcoal");}if(matrixButtonClicked[1][3]==0){LEDsetColor("rose");}if(matrixButtonClicked[2][0]==0){LEDsetColor("mint");}if(matrixButtonClicked[2][1]==0){LEDsetColor("indigo");}if(matrixButtonClicked[2][2]==0){LEDsetColor("peach");}if(matrixButtonClicked[2][3]==0){LEDsetColor("lime");}if(matrixButtonClicked[3][0]==0){LEDsetColor("coral");}if(matrixButtonClicked[3][1]==0){LEDsetColor("navy");}if(matrixButtonClicked[3][2]==0){LEDsetColor("olive");}if(matrixButtonClicked[3][3]==0){LEDsetColor("lavender");}

for (int i = 0; i < 4; i++) {
  for (int i2 = 0; i2 < 4; i2++) {
    if(matrixButtonClicked[i][i2] == 1) {matrixButtonState[1] = 1;}
    else {matrixButtonState[1] = 0; break;}
  }
    if (matrixButtonState[1] == 0)  {break;}
}

if(matrixButtonState[1] == 1) {analogWrite(LEDrPin, 0);analogWrite(LEDgPin, 0);analogWrite(LEDbPin, 0);}

for (int i = 0; i < 4; i++) {Serial.print(matrixButtonClicked[i][0]);Serial.print(" ");Serial.print(matrixButtonClicked[i][1]);Serial.print(" ");Serial.print(matrixButtonClicked[i][2]);Serial.print(" ");Serial.print(matrixButtonClicked[i][3]);Serial.print(" ");}Serial.print(matrixButtonState[1]);Serial.println();}