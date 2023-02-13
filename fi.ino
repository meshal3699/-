unsigned long  z = 0;
#include <Servo.h>
#define in1 2  
#define in2 3  
#define in3 7 
#define in4 8  
#define ena 5  
#define enb 6  
Servo myservo;  
int pos = 0;    
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance,Cdistance,Rdistance,Ldistance;
#include <EEPROM.h>
#include <OneWire.h>  
#include <DallasTemperature.h>  
#define ONE_WIRE_BUS 4            

OneWire ourWire(ONE_WIRE_BUS);     
DallasTemperature sensors ( &ourWire ) ;

float vout;
float temp;
float value;

void setup() {
 pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  myservo.attach(9);  
  myservo.write(85); 

  
Serial.begin(9600);
delay (500 ) ;          
Serial.begin ( 9600 ) ;   
Serial.println (" Temperature Sensor :  DS18B20 " ) ;
delay ( 1000 ) ;         
sensors.begin ( ) ;  
}

void loop() {
while(z < 10 ){
z++;
  Cdistance=ultrasonic();
  if(Cdistance>30)
  {
    forward();
  }else 
  {
    if(Cdistance<=10&&Cdistance>2)reverse();
    off();                   
    myservo.write(35);       
    delay(300);
    Rdistance=ultrasonic();  
    myservo.write(135);      
    delay(300);
    Ldistance=ultrasonic();  
    myservo.write(85);       
    delay(300);
    comparison(Rdistance, Ldistance); 
    off();                    
    delay(150);
  }
Rdistance=0;
  Ldistance=0;
  Cdistance=0;

sensors.requestTemperatures ( ) ;  

Serial.print  ( " Temperature in degree  is : " ) ; 
Serial.print ( sensors.getTempCByIndex ( 0 ) ) ; 
Serial.println ( "C° " ) ;          
delay ( 500 ) ;  

  
vout= digitalRead(4);
temp= (vout*500)/1023;
int ana;
EEPROM.write(0,temp);
ana=EEPROM.read(0);
Serial.print( sensors.getTempCByIndex ( 0 ) );
Serial.print(ana);
Serial.println();




}


EEPROM.read(0);
Serial.print( sensors.getTempCByIndex ( 0 ) );
off();


}
int ultrasonic(void)
{
  distance=0;
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
return distance;
}

void comparison(int r, int l)
{
  if(r>25||l>25)
  {
   if(r>l||r==l)
   {
     Tright90();
   }else if(l>r)
   {
     Tleft90();
   }
  }else if(r<25&&l<25)
  {
    Tleft180();
  }
}
void forward()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void off()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void Tleft90()
{
  analogWrite(ena,160);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(650);
}
void Tright90()
{
  analogWrite(ena,150);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(750);  
}

void Tleft180()
{
  analogWrite(ena,150);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1500);
}
void reverse()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(450);
}




