#include <SoftwareSerial.h>

// Serial reading defaults
char buffer [32];
int cnt = 0;
boolean ready = false;

// LED values
int ledValueA = 0;
int ledValueB = 0;
int ledValueC = 0;

// Serial comms between the Jevois and the Arduino
SoftwareSerial mySerial(10, 11); // RX, TX

// Define LED pins
int ledPinA = 3;
int ledPinB = 5;
int ledPinC = 6;

// max length of serial reading
char value[15];

void setup() {
  // Hardware serial
  Serial.begin(57600);

  // Software serial
  mySerial.begin(115200);
}

void ParseLine()
{
char* value;
    value = strtok(buffer, "\n");  // Everything else is the color value
    
    if (value != NULL)
    {
        char ledA[] = "000";
        char ledB[] = "000";
        char ledC[] = "000";
        ledA[0] = value[0];
        ledA[1] = value[1];
        ledA[2] = value[2];
        ledB[0] = value[3];
        ledB[1] = value[4];
        ledB[2] = value[5];
        ledC[0] = value[6];
        ledC[1] = value[7];
        ledC[2] = value[8];
        int ledValueA = atoi(ledA);
        int ledValueB = atoi(ledB);
        int ledValueC = atoi(ledC);
        analogWrite(ledPinA, ledValueA*2);
        analogWrite(ledPinB, ledValueC*2);
        analogWrite(ledPinC, ledValueB*2);
        //Serial.println(ledValueA);
        Serial.println(ledB);
        //Serial.println(ledValueC);
    }
}

void loop()
{
    if (ready)
    {
        ParseLine();
        ready = false;
    } else while (mySerial.available())
    {
        char c = mySerial.read();
        buffer[cnt++] = c;
        if ((c == '\n') || (cnt == sizeof(buffer)-1))
        {
            buffer[cnt] = '\0';
            cnt = 0;
            ready = true;
        }
    }
}



