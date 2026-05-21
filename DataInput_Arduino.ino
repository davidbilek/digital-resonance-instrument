#include "HX711.h"

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;
HX711 scale5;
HX711 scale6;
HX711 scale7;
HX711 scale8;

long eightScales[8]; 
long bitShiftVal = 8;

void setup() {
  Serial.begin(28800);
  
  scale1.begin(2, 3);
  scale2.begin(4, 5);
  scale3.begin(6, 7);
  scale4.begin(8, 9);
  scale5.begin(22, 23);
  scale6.begin(24, 25);
  scale7.begin(26, 27); 
  scale8.begin(28, 29);  
}

void loop() {
  eightScales[0] = scale1.read() >> bitShiftVal;
  eightScales[1] = scale2.read() >> bitShiftVal;
  eightScales[2] = scale3.read() >> bitShiftVal;
  eightScales[3] = scale4.read() >> bitShiftVal;
  eightScales[4] = scale5.read() >> bitShiftVal;
  eightScales[5] = scale6.read() >> bitShiftVal;
  eightScales[6] = scale7.read() >> bitShiftVal;
  eightScales[7] = scale8.read() >> bitShiftVal;
  
  for(int i = 0; i < 8; i++) {
    Serial.print(eightScales[i]);  
    if (i == 7) {
      break;
    }
    Serial.print(" "); 
  }
  Serial.println();  
}
