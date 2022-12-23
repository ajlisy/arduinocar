#include <AFMotor.h>
char Incoming_value = 0;  //Variable for storing Incoming_value
int lim=1;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);   //Sets the data rate in bits per second (baud) for serial data transmission
  Serial.println("******"); 
}

void loop() {

  go_forward(5800);
  delay(1000);
  turn_degrees_left(100);
  delay(1000);
  go_forward(2000);
//   delay(1000);
//  // turn_degrees_right(30);
//   go_forward(4);

  delay(60000);
  // go_backward(2);
  // delay(3000);
  // turn_90_right();
  // turn_90_right();
  // turn_90_right();
  // turn_90_right();
  // delay(50000);
}

void go_forward(int milliseconds)
{
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  delay(milliseconds);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void go_backward(int seconds)
{
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  delay(seconds * 1000);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void turn_90_right()
{
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  delay(600);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void turn_90_left()
{
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  delay(600);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void turn_degrees_left(float degrees)
{
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  delay(600*(degrees/90));

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void turn_degrees_right(float degrees)
{
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  delay(600*(degrees/90));

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}
