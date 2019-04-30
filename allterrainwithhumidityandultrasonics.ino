#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
const int trigPin = 10;
const int echoPin = 11;
char t;
long duration;
int distance;
int pinDHT11 = 8;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(9, INPUT);
  pinMode(4,OUTPUT);   //left motors forward
  pinMode(5,OUTPUT);   //left motors reverse
  pinMode(6,OUTPUT);   //right motors forward
  pinMode(10,OUTPUT);   //right motors reverse
}

void loop() {
  // start working...
  int a;
  a=digitalRead(9);
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
   
  Serial.print("Sample OK: ");
  Serial.print("Temperature=");
  Serial.print((int)temperature); Serial.print("*C, "); 
  Serial.print("Humidity=");
  Serial.print((int)humidity); Serial.println("H, ");
  if(a==0)
  {
    Serial.print("Water not detected, ");
  }
  if(a==1)
  {
    Serial.print("Water detected, ");
  }
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.print("cm, ");
 if(distance<=20)
 {
  Serial.print("Object detected");
  }
  if(distance>20)
 {
  Serial.print("Object not detected");
  }
 Serial.println();
 if(Serial.available()){
  t = Serial.read();
  Serial.println(t);

 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(5,HIGH);
  digitalWrite(7,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(6,HIGH);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(4,HIGH);
}

else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}
delay(100);
 }
  
  
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
