
// We need to include some prewritten code to function with the LCD
#include <LiquidCrystal.h>

// #define allows us to make changes in one place that effect the whole code base
// We define the pins that controls the ultrasonic sensor
#define trigPin 7
#define echoPin 6

// We define the pin that controls the piezo buzzer
#define buzzerPin 9

// This creates an lcd object that we can use to update the display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// The setup code block is where we put the code that we want to exectue once
void setup() {
  lcd.begin(16,2); // gets the LCD ready to use and sets the screen size
  lcd.clear(); // clears any text that may already be on the lcd
  lcd.print("PLab 101 Ruler"); //Sets the first line to have a title

  // We need to define the ultrasonic sensor's pins
  pinMode(trigPin, OUTPUT); // The trigger pin creates the ultrasonic sound
  pinMode(echoPin, INPUT);  // The echo pin measure how long it takes for the sound to return
}

void loop() {
  // Defines the variables needed for the ultrasonic sensor
  long duration;
  long distance;

  // Activate the trigger
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration on the echo pin in milliseconds
  duration = pulseIn(echoPin, HIGH);

  // convert the duration to inches
  distance = duration / 74 / 2;

  // Only display the distance if it makes reasonable sense
  // The distance must be between 0 and 144 inches
  if (distance >= 0 && distance <= 144){
    lcd.setCursor(0,1); // moce the cursor on the lcd to the second line
    lcd.print("                "); //clear the second line
    lcd.setCursor(0,1); //move the cursor back to the beginning of the line
    lcd.print(distance); // print the distance value
    lcd.print(" in"); // print the distance units
  }

  // Define the distance alarm
  // Alarm will sound at or below 6 inches
  if (distance >= 0 && distance <= 6) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }
}
