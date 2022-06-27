#include"TM1637.h"
#define CLK 22
#define DIO 21
TM1637 tm1637(CLK,DIO);
const int sensorIn = 34;
int mVperAmp = 185;

double voltage = 0;
double Vrms = 0;
double AmpsRMS = 0;
double AmpsRMS1 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tm1637.init();
  //tm1637.set(BRIGHT_DARKEST);
  delay(500); 
}
void loop() {
  // put your main code here, to run repeatedly:
  voltage = getVPP();
  Vrms = (voltage/2.0) *0.707;
  AmpsRMS = (Vrms * 1000)/mVperAmp;
  AmpsRMS1 = AmpsRMS - 0.35;
  Serial.print(AmpsRMS1);
  tm1637.display(AmpsRMS1);
  Serial.println("AmpsRMS2");
}
float getVPP()
{
  float result,result1;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 4096;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
        //Serial.print(readValue);
        //Serial.println(" readValue");
       
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       
        //Serial.print(maxValue);
 //Serial.println(" maxValue");
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       
        //Serial.print(minValue);
        //Serial.println(" minValue");
       }
   }

  
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/4096.0;
     //Serial.print(result);
        //Serial.println(" result Value"); 
   
   result1 = (maxValue - minValue);
    //Serial.print(result1);
        //Serial.println(" result1 Value"); 
   return result;
 }
