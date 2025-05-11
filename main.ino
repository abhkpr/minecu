//Assumptions
//Crank sensor: 2 pulses per revolution
//Throttle: Analog input using a potentiometer
//Ignition: Digital pulse based on RPM
//Fuel injection: Simulated with pulse width based on RPM and throttl

//Wiring
//Hall sensor D2
//Ignition LED D8
//Injector LED D9 (PWM)
//Potentiometer A0

// Pins
const int crankPin = 2;       // Interrupt pin for RPM sensor
const int ignitionPin = 8;    // Simulated spark output
const int injectorPin = 9;    // Simulated fuel injector (PWM-capable)
const int throttlePin = A0;   // Throttle position (potentiometer)

// Variables
volatile int pulseCount = 0;
unsigned long lastRPMCheck = 0;
float rpm = 0;

void setup() {
  pinMode(ignitionPin, OUTPUT);
  pinMode(injectorPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(crankPin), countPulse, RISING);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // Calculate RPM every 1 second
  if (now - lastRPMCheck >= 1000) {
    rpm = pulseCount * 30.0; // 2 pulses per revolution → 60 / 2 = 30
    pulseCount = 0;
    lastRPMCheck = now;
    Serial.print("RPM: "); Serial.print(rpm);
    Serial.print(" | Throttle: "); Serial.println(analogRead(throttlePin));
  }

  // Simulate ignition at RPM > 0
  if (rpm > 0) {
    triggerIgnition();
    injectFuel();
  }
}

// Interrupt: counts crankshaft pulses
void countPulse() {
  pulseCount++;
}

// Simulate spark output
void triggerIgnition() {
  digitalWrite(ignitionPin, HIGH);
  delay(5);
  digitalWrite(ignitionPin, LOW);
}

// Simulate fuel injector pulse width based on RPM & throttle
void injectFuel() {
  int throttle = analogRead(throttlePin); // 0–1023
  int pulseWidth = map(throttle, 0, 1023, 2, 10); // Pulse width in ms

  digitalWrite(injectorPin, HIGH);
  delay(pulseWidth);
  digitalWrite(injectorPin, LOW);
}
