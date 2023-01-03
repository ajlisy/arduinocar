#include <WiFi.h>
#include <HTTPClient.h>
#include <string>


//Pins
#define IN1 16
#define IN2 17
#define IN3 18
#define IN4 19

char Incoming_value = 0;  //Variable for storing Incoming_value
int lim = 1;

const char* ssid = "gavroche";
const char* password = "grundle99";

//Your Domain name with URL path or IP address with path
String serverName = "https://raw.githubusercontent.com/ajlisy/arduinocar/main/instructions.txt";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
char *ptr;



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  //Serial.begin(9600);   //Sets the data rate in bits per second (baud) for serial data transmission
  Serial.println("******");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      String serverPath = serverName;

      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        delay(2000);
        tokenize(payload);
        delay(100000000);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources

      http.end();

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void tokenize(String in) {
  Serial.println("Tokenizing...");
  String first;
  String second;
  int last, space, newline;
  last = 0;

  //Initial values
  space = in.indexOf(' ');
  newline = in.indexOf('\n');
  while (space != -1) {
    Serial.println("Input string: >>" + in + "<<");
    Serial.println("space = " + String(space) + "; newline=" + String(newline) + "; last=" + String(last));
    first = in.substring(last, space);
    second = in.substring(space + 1, newline);
    Serial.println("Tokens: >>" + first + "<< / >>" + second + "<<");
    parse_and_route(first, second.toInt());
    delay(1000);
    in = in.substring(newline + 1, in.length());
    space = in.indexOf(' ');
    newline = in.indexOf('\n');
  }
}

void parse_and_route(String command, int param) {
  if (command == "go_forward") {
    go_forward(param);
  } else if (command == "go_backward") {
    go_backward(param);
  } else if (command == "turn_degrees_left") {
    turn_degrees_left(param);
  } else if (command == "turn_degrees_right") {
    turn_degrees_right(param);
  } else if (command == "wait") {
    wait(param);
  } else {
    Serial.println("Error on parse_and_route. Received command: >>" + command + "<<. Received param: " + String(param));
  }
}

void wait(int milliseconds) {
  delay(milliseconds);
}

void go_forward(int milliseconds)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(milliseconds);

  stop_wheels();
}

void go_backward(int milliseconds)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(milliseconds);

  stop_wheels();
}

void turn_90_right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(600);

  stop_wheels();
}

void turn_90_left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(600);

  stop_wheels();
}

void turn_degrees_left(float degrees)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(600 * (degrees / 90));

  stop_wheels();
}

void turn_degrees_right(float degrees)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(600 * (degrees / 90));

  stop_wheels();

}

void stop_wheels() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
