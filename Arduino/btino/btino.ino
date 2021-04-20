#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial serialBlue(D2, D3);

unsigned long baudrate = 115200;

void setup() {

    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    rgb_color(0, 0, 0);

    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);

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
    serialBlue.begin(19200);

}

void loop() {

    while (!serialBlue.available())
    {
    }
    

    if (serialBlue.available()) {
        char task = serialBlue.read();
        switch (task) {
            case 'r':
            serialBlue.println("RED");
            rgb_color(255, 0, 0);
            break;
            case 'g':
            serialBlue.println("GREEN");
            rgb_color(0, 255, 0);
            break;
            case 'b':
            serialBlue.println("BLUE");
            rgb_color(0, 0, 255);
            break;
        }
    }
}

void rgb_color(int r, int g, int b) {

    analogWrite(5, 0xff - r); //red
    analogWrite(6, 0xff - g); //green
    analogWrite(9, 0xff - b); //blue
}

void seg_number(int n) {
    serialBlue.end();
    delay(100);

    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);     
    serialBlue.begin(baudrate);
    delay(100);
}
