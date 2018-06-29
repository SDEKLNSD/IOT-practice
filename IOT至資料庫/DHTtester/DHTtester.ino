// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <Bridge.h>
#define DHTPIN A0     // what pin we're connected to
const int pinAdc = A1;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
    Serial.begin(9600); 
    Serial.println("DHTxx test!");
    Bridge.begin();
    dht.begin();
}

void loop() 
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    int value = analogRead(A2);
    value = map(value, 0, 800, 0, 200);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    long sum = 0;

    
    for(int i=0;i<32;i++){
        sum += analogRead(pinAdc);
    }
    
    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");
        Bridge.put("h", String(h));
        Bridge.put("t", String(t));
    }
    
    sum >>= 5;

    Serial.print("Sound: "); 
    Serial.println(sum);
    Serial.print(" %\t");

    Serial.print("Light: "); 
    Serial.println(value);
    
    Bridge.put("s", String(sum));
    Bridge.put("l", String(value));
    delay(10);
}
