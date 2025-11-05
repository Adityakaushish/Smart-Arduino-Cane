// Smart_Arduino_Cane.ino
// Developed by Aditya Kaushish & Team
// Smart cane for visually impaired — detects obstacles and alerts via buzzer and vibration

// --- Pin Definitions ---
#define TRIG 9         // Ultrasonic sensor TRIG pin
#define ECHO 8         // Ultrasonic sensor ECHO pin
#define BUZZER 7       // Buzzer pin
#define VIBRATION 6    // Vibration motor pin

// --- Variables ---
long duration;
float distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(VIBRATION, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Calculate distance (in cm)
  duration = pulseIn(ECHO, HIGH);
  distance = (duration * 0.0343) / 2;

  // Print distance to Serial Monitor (for testing)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Alert logic
  if (distance > 0 && distance <= 100) { // Within 1 meter
    // Inverse frequency logic: closer = faster beep
    int beepDelay = map(distance, 10, 100, 50, 500); // Adjust mapping as needed
    tone(BUZZER, 1000); // Beep sound
    digitalWrite(VIBRATION, HIGH);
    delay(beepDelay);
    noTone(BUZZER);
    digitalWrite(VIBRATION, LOW);
    delay(beepDelay);
  } 
  else {
    noTone(BUZZER);
    digitalWrite(VIBRATION, LOW);
  }

  delay(100);
}
