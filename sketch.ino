#define TEMP_LIMIT 30.0   

const int sensorPin = A0;
const int ledPin = 13;

unsigned long previousMillis = 0;
const unsigned long interval = 200;   // read every 200 ms

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int raw = analogRead(sensorPin);
    float voltage_mV = raw * 5000.0 / 1023.0;      // ADC value to millivolts
    float temp_C = (voltage_mV - 500.0) / 10.0;    

    if (temp_C > TEMP_LIMIT) {
      digitalWrite(ledPin, HIGH);
      Serial.print(temp_C);
      Serial.println(" C - ⚠ ΥΨΗΛΗ ΘΕΡΜΟΚΡΑΣΙΑ");
    } else {
      digitalWrite(ledPin, LOW);
      Serial.print(temp_C);
      Serial.println(" C - OK");
    }
  }
}