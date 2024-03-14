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
#define activateThres 38.0

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  // Initialize lcd
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  
  // Turn backlight on
  lcd.backlight();

  // Register our pins
  pinMode(po_lineOut, OUTPUT);
}

void loop() {
  // Get the average reading with 10 samples and 1ms delay interval from
  // our temperature sensor.
  const float thermisVal = getAverage(10, pi_tempSensor, 1, true);

  float temperature = resistanceToCelsius(thermisVal, 4750, .18);

  // Check if the temp is greater than 40 degree
  // If greater than then turn the relay (light) on
  if(temperature > activateThres) {
    digitalWrite(po_lineOut, LOW);
  } else {
    // Else turn the relay (light) off
    digitalWrite(po_lineOut, HIGH);
  }

  lcd.clear();

  lcd.setCursor(0, 0);

  // We can also see the actual temperature reading
  // by printing it into LCD
  lcd.print("Temp: ");
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print("Thr: ");
  lcd.print(activateThres);
  lcd.print(" deg C");

  // Add some delay in millisecond to refresh the reading 
  delay(500);
}

float resistanceToCelsius(float t1, float t2, float coef) {
  /**
   * t1 = input value
   * t2 = expected resistance at coef
   * coef = temperature at t2 resistance
   **/
   return ((t2 / t1) - 1) / coef;
}


float getAverage(const int sampleCount, int analogInputPin, int delayMs, bool invertValue) {
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

  if(invertValue)
    return 1023 - (sum / sampleCount);

  return sum / sampleCount;
}

bool isInRange(int readIn, int minInp, int maxInp) {
  /**
   * Check whether the readIn is within range of a min and max value
   **/
  return minInp < readIn && readIn < maxInp;
}



