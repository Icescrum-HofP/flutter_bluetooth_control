#include <Arduino.h>
#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial serialBlue(A2, A1);

unsigned long baudrate = 115200; // terminal

void setup() {

    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    rgb_color(0, 0, 0);

    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);

// all as output 
    pinMode(0, OUTPUT); 
    pinMode(1, OUTPUT); 
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);

    Serial.begin(baudrate);
    serialBlue.begin(9600); //bluetooth module

}

void loop() {
    while (!serialBlue.available()) // delay 
    {
    }
    

    if (serialBlue.available()) {
        char task = serialBlue.read();
        
        if(task !='/n' && task != '/r'){
        if (task != 'r'&&task !='g'&&task != 'b'){
            unsigned char r, g, b;
            r = task;
            g = nextByte();
            b = nextByte();
            rgb_flow(r, g, b);
        }

        switch (task) {
            case 'r':
            serialBlue.println("RED"); // Antwort for terminal
            rgb_color(255, 0, 0);
            break;
            case 'g':
            serialBlue.println("GREEN"); // Antwort for terminal
            rgb_color(0, 255, 0);
            break;
            case 'b':
            serialBlue.println("BLUE"); // Antwort for terminal
            rgb_color(0, 0, 255);
            break;
        }

        
        }
        
    }
}

void rgb_color(int r, int g, int b) {

    analogWrite(5, 0xff - r); //red
    analogWrite(6, 0xff - g); //green
    analogWrite(9, 0xff - b); //blue
}

int nextByte()
{
    while (!serialBlue.available())
    {
        //wait
    };

    char ch = serialBlue.read();

    if (ch != '\n' && ch != '\r') // not a new line
    {
        return ch;
    }
    else
    {
        return nextByte(); // retry
    }
}

void rgb_flow(int r, int g, int b)
{

    int n = 1000;
    r = r * r / 255;
    g = g * g / 255;
    b = b * b / 255;

    Serial.print(" r=");
    Serial.print(r);
    Serial.print(" g=");
    Serial.print(g);
    Serial.print(" b=");
    Serial.print(b);
    Serial.println(";");

    analogWrite(5, 0xff - r); //red
    analogWrite(6, 0xff - g); //green
    analogWrite(9, 0xff - b); //blue
}