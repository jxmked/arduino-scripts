// Install this by downloading it from library
#include <LiquidCrystal_I2C.h>

// Change this only if needed
// Based on your LCD
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

// Our pin is set to 
#define pi_tempSensor A0
#define po_lineOut 7

// Threshold
#define activateThres 40.0

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  // Initialize lcd
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  
  // Turn backlight on
  lcd.backlight();

  // Register our pins
  pinMode(po_lineOut, OUTPUT);
  pinMode(pi_tempSensor, INPUT);
}

void loop() {
  // Get the average reading with 10 samples and 1ms delay interval from
  // our temperature sensor.
  const float result = getAverage(10, pi_tempSensor, 1);
  
  // Note: This formula is not accurate
  //       Look for right calibration of sensor to 
  //       Get accurate data from humidity.
  //       Also try to use actual humidity sensor
  const float temp = (((result / 3.9) / 5.0) + 32);

  // Check if the temp is greater than 40 degree
  // If greater than then turn the relay (light) on
  if(temp > activateThres) {
    digitalWrite(po_lineOut, HIGH);
  } else {
    // Else turn the relay (light) off
    digitalWrite(po_lineOut, LOW);
  }

  // We can also see the actual temperature reading
  // by printing it into LCD
  lcd.print(temp);

  // Add some delay in millisecond to refresh the reading 
  delay(500);

  // Clear the lcd before writting new ones
  lcd.clear();
}


float getAverage(const int sampleCount, int analogInputPin, int delayMs) {
  /**
   * There is a high chance of having noise while reading some analog input
   * so, instead of using single value from input, we get some samples and 
   * then get the average of it so atleast we reduce some noise from input.
   * We also added some delay interval to give it a time to fetch enough data.
   **/
  int sum = 0;

  for(int i = 0; i < sampleCount; i++) {
    sum += analogRead(analogInputPin);
    delay(delayMs);
  }

  return sum / sampleCount;
}

