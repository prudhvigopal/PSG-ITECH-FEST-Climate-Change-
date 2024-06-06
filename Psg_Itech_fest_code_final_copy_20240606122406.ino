  #include <Wire.h>
  #include <DHT.h>
  #include <RTClib.h>

#define DHTPIN 2       // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11   // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;  // Create an instance of the RTC_DS3231 class

const int irPin = 3;      // Digital pin connected to the IR sensor
int irSensorValue = 0;    // Variable to store the IR sensor value

const int ldrPin = A0;    // Analog pin connected to the LDR module

const int waterLevelPin = A1;  // Analog pin connected to the water level sensor

const int loadPin = 4; 
const int loadPin1 = 5;    
  const int loadPin2 = 6; 
const int loadPin3 = 7;   // Digital pin connected to the load

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(irPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(waterLevelPin, INPUT);
  pinMode(loadPin, OUTPUT);
  pinMode(loadPin1, OUTPUT);
  pinMode(loadPin2, OUTPUT);
  pinMode(loadPin3, OUTPUT);
  Wire.begin();
  rtc.begin();

  // Set today's date and time at 9:00 AM
  rtc.adjust(DateTime(2023, 8, 15, 9, 0, 0));
  
  // Turn off all loads initially
  digitalWrite(loadPin, LOW);
  digitalWrite(loadPin1, LOW);
  digitalWrite(loadPin2, LOW);
  digitalWrite(loadPin3, LOW);
}

void loop() {
  DateTime now = rtc.now();  // Get the current date and time from RTC

  // Read DHT11 temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read IR sensor
  irSensorValue = digitalRead(irPin);
  
  // Read LDR module
  int ldrSensorValue = analogRead(ldrPin);
  float ldrVoltage = (ldrSensorValue / 1023.0) * 5.0;

  // Read water level sensor
  int waterSensorValue = analogRead(waterLevelPin);

  // Check if the current time is between 9:00 AM and 9:01 AM
  if (now.hour() == 9 && now.minute() >= 0 && now.minute() <= 1) {
    // Control load based on temperature sensor reading
    if (temperature > 25) { // Modify the condition as needed
      digitalWrite(loadPin, HIGH);  // Turn on the load
      Serial.println("Load 1 is ON");
    } else {
      digitalWrite(loadPin, LOW);   // Turn off the load
      Serial.println("Load 1 is OFF");
    }
  } else {
    digitalWrite(loadPin, LOW);   // Turn off the load outside the specified time
    Serial.println("Load 1 is OFF (outside time)");
  }
  if (now.hour() == 9 && now.minute() >= 1 && now.minute() <= 2) {
   lock(1)
  }
  if (now.hour() == 9 && now.minute() >= 2 && now.minute() <= 3) {
    // Control load based on LDR sensor reading
    if (ldrSensorValue > 400) { // Modify the condition as needed
      digitalWrite(loadPin2, LOW);  // Turn on the load
      Serial.println("Load 3 is ON");
    } else {
      digitalWrite(loadPin2, HIGH);   // Turn off the load
      Serial.println("Load 3 is OFF");
    }
  } else {
    digitalWrite(loadPin2, LOW);   // Turn off the load outside the specified time
    Serial.println("Load 3 is OFF (outside time)");
  }
    if (now.hour() == 9 && now.minute() >= 3 && now.minute() <= 4) {
    // Control load based on LDR sensor reading
    if (waterSensorValue > 400) { // Modify the condition as needed
      digitalWrite(loadPin3, LOW);  // Turn on the load
      Serial.println("Load 4 is ON");
    } else {
      digitalWrite(loadPin3, HIGH);   // Turn off the load
      Serial.println("Load 4 is OFF");
    }
  } else {
    digitalWrite(loadPin3, LOW);   // Turn off the load outside the specified time
    Serial.println("Load 4 is OFF (outside time)");
  }

  // Print sensor readings and date/time
  Serial.print("DHT11 - Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("IR Sensor - ");
  if (irSensorValue == HIGH) {
    Serial.println("Object Detected");
  } else {
    Serial.println("No Object Detected");
  }

  Serial.print("LDR Module - Sensor Value: ");
  Serial.print(ldrSensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(ldrVoltage);
  Serial.println(" V");

  Serial.print("Water Level Sensor - Sensor Value: ");
  Serial.println(waterSensorValue);

  // Print current date and time
  Serial.print("Current Date and Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  printDigits(now.month());
  Serial.print('/');
  printDigits(now.day());
  Serial.print(' ');
  printDigits(now.hour());
  Serial.print(':');
  printDigits(now.minute());
  Serial.print(':');
  printDigits(now.second());
  Serial.println();

  delay(2000); // Wait for 2 seconds before taking another reading
}

void printDigits(int digits) {
  // Prints a leading zero if the value is less than 10
  if (digits < 10) {
    Serial.print('0');
  }
  Serial.print(digits);
}