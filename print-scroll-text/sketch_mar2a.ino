// Install this by downloading it from library
#include <LiquidCrystal_I2C.h>

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char textA[] = "Sample Text A";
const char textB[] = "Sample Text B";

void setup() {
  // Initialize lcd
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  
  // Turn backlight on
  lcd.backlight();

}

void loop() {

  printOnScreen(0, 0, 0, textA);
  printOnScreen(0, 1, 1, textB);

  delay(1000);
  
  // Clear the screen
  lcd.clear();
}

/**
 * Params
 * int cx - Cursor X
 * int cy - Cursor y
 * int offsetIndex - Which index will be use to scroll the text. Max 3.
 * char *text - Text to print
 **/
void printOnScreen(int cx, int cy, int offsetIndex, char *text) {

  // Keep our index where we left it
  // Just update it when needed
  static int offsets[3] = {0, 0 ,0};
  
  int offset = offsets[offsetIndex];
 
  // Move the cursor into x & y
  lcd.setCursor(cx, cy);

  // Print the adjusted text into screen
  lcd.print(&text[offset]);
  
  // Increment offset value by 1
  offset++;
  
  // Check if the offset exceed max length of the text
  if(offset >= strlen(text)) {
    offset = 0;
  }
  
  // Update offset list
  offsets[offsetIndex] = offset;
}
