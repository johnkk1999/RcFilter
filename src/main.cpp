#include <Arduino.h>
typedef struct{
  float coeff[2];
  float out[2];
}RcFilter;

void RcFilterInit(RcFilter *, float, float);
void RcFilterUpdate(RcFilter* , float);

RcFilter filt;

void setup()
{
  Serial.begin(9600);
  RcFilterInit(&filt,220.0e-6,100);
analogReadResolution(16);
}
void loop() {
 float voltage = analogRead(A0);
 voltage = 3.3 * voltage/65536.0;
 RcFilterUpdate(&filt,voltage);
 Serial.print(">First:");
 Serial.println(voltage);
 Serial.print(">Second:");
 Serial.println(filt.out[0]);

 
}
void RcFilterInit(RcFilter *filt, float sampTime, float cutFreq)
{
  float RC = 1/(6.2831853072f*cutFreq);
  filt->coeff[0] = sampTime/(sampTime+RC);
  filt->coeff[1] = RC /(sampTime + RC);
  //initial outputs to zero
  filt->out[0] = 0.0f;
  filt->out[1] = 0.0f;
}
void RcFilterUpdate(RcFilter* filt , float input)
{

  filt->out[1] = filt->out[0];
  filt->out[0] = filt->coeff[0] * input + filt->coeff[1] * filt->out[1];

  }