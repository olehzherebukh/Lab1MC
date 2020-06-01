#include <LiquidCrystal.h>

#define DDR_KEYPAD  DDRF
#define PORT_KEYPAD PORTF
#define PIN_KEYPAD  PINF
#include "keypad4x4.h"

const int buzzerPin = 21;
bool beeping = 1;
int clicked = 0;
int i = 1;
int a;
int b;
int c;
int d;
int e;
int f;
bool value1 = 1;
bool value2 = 1;
bool value3 = 1;
bool value4 = 1;
bool value5 = 1;
bool value6 = 1;
char abc[] = {'0', '0'};



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A8, rw = A9, en = A10, d4 = A11, d5 = A12, d6 = A13, d7 = A14;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);

const PROGMEM  char sixty[60][3] = {
  {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"},
  {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"},
  {"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"},
  {"30"}, {"31"}, {"32"}, {"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"},
  {"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"},
  {"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"}, 
};


struct Time
{
  unsigned char second, minute, hour;
};
Time T1 = {9, 0, 0};
Time T5 = {6, 0, 0};

void LCD_WriteStrPROGMEM(char *str, int n)  //вивід масиву символів,
{ //записаних у флеші
  for (int i = 0; i < n; i++)
    lcd.print( (char)pgm_read_byte( &(str[i]) ) );
}

ISR(TIMER1_COMPA_vect)
{
  if (T1.second-- == 00)
  {
    T1.second = 59;
    if (T1.minute-- == 00)
    {
      T1.minute = 59;
      if (T1.hour-- == 00)
        T1.hour = 00;
        T1.second = 00;
        T1.minute = 00;
         
    }
   if (T1.second == 0 && T1.minute == 0) {
    T1.second = 59;
    T1.minute = 59;
    if (T1.hour == 0) {
       T1.second = 0;
       T1.minute = 0;
       T1.hour = 0;
      }
    }
  }

  lcd.setCursor(0, 0);
  LCD_WriteStrPROGMEM(abc, 2);
  lcd.write(':');
  LCD_WriteStrPROGMEM(sixty[T1.minute], 2);
  lcd.write(':');
  LCD_WriteStrPROGMEM(sixty[T1.second], 2);
}

ISR(TIMER5_COMPA_vect)
{
  if (T5.second-- == 00)
  {
    T5.second = 59;
    if (T5.minute-- == 00)
    {
      T5.minute = 59;
      if (T5.hour-- == 00)
        T5.hour = 00;
        T5.second = 00;
        T5.minute = 00;
         
    }
   if (T5.second == 0 && T5.minute == 0) {
    T5.second = 59;
    T5.minute = 59;
    if (T5.hour == 0) {
       T5.second = 0;
       T5.minute = 0;
       T5.hour = 0;
      }
    }
  }

  lcd.setCursor(0, 0);
  LCD_WriteStrPROGMEM(sixty[T5.hour], 2);
  lcd.write(':');
  LCD_WriteStrPROGMEM(sixty[T5.minute], 2);
  lcd.write(':');
  LCD_WriteStrPROGMEM(sixty[T5.second], 2);
}

void setup() {
  noInterrupts();
  TCCR1A = 0x00;
  TCCR1B = (0 << WGM12) | (0 << CS12) | (0 << CS10); //CTC mode & Prescaler @ 1024
  TIMSK1 = (1 << OCIE1A); // дозвіл на переривання по співпадінню
  OCR1A = 0x3D08;// compare value = 1 sec (16MHz AVR)
  
  TCCR5A = 0;
  TCCR5B = 0;
  TCNT5 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR5A = 15624;
  // CTC
  TCCR5B |= (0 << WGM52);
  // Prescaler 1024
  TCCR5B |= (0 << CS52) | (0 << CS50);
  // Output Compare Match A Interrupt Enable
  TIMSK5 |= (0 << OCIE5A);
  initKeyPad();

  lcd.begin(16, 2);
  lcd.print("Press A to set 1");
  lcd.setCursor(0, 1);
  lcd.print("Press B to set 2");
  interrupts();  // Enable global interrupts

  //Buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

int concat(int a, int b) 
{ 
  
    char s1[20]; 
    char s2[20]; 
  
    sprintf(s1, "%d", a); 
    sprintf(s2, "%d", b); 
  
    strcat(s1, s2); 
  
    int c = atoi(s1); 
  
    return c; 
} 

int toInt(char c) {
    return c - '0';
}

char readKeyBoard(int check) {
  if ( isButtonPressed()) {
      lcd.setCursor(0, 0);
      return readKeyFromPad4x4();
    }
}

char buttonClicking(int column, int row) {
  if (isButtonPressed()) {
      lcd.setCursor(column, row);
      lcd.print(readKeyFromPad4x4());
      clicked++;
      return readKeyFromPad4x4();
    }
}

void loop() {
  if (readKeyFromPad4x4() == 'A') {
    if (value1) {
        lcd.clear();
        lcd.print("Enter hour t1");
        value1 = 0;
      }
      a = 0;
      b = toInt(buttonClicking(1, 1));
  }
  if (readKeyFromPad4x4() == 'B') {
    if (value1) {
        lcd.clear();
        lcd.print("Enter hour t2");
        value1 = 0;
      }
      e = 0;
      f = toInt(buttonClicking(1, 1));
  }
  
  if (readKeyFromPad4x4() == 'C') {
    if (value3) {
        lcd.clear();
        T5.hour = concat(a, b);
        T5.minute = concat(c, d);
        value3 = 0;
      }
      TCCR5B |= (1 << WGM52);
      TCCR5B |= (1 << CS52) | (1 << CS50);
      TIMSK5 |= (1 << OCIE5A);
    }
  if (readKeyBoard(0) == 'E') {
    if (value4) {
        lcd.clear();
        lcd.print("Enter minute");
        value4 = 0;
      }
      c = 0;
      d = toInt(buttonClicking(1, 1));
  }
  if (readKeyFromPad4x4() == 'D') {
    if (value5) {
        lcd.clear();
        T1.hour = concat(e, f);
        T1.minute = concat(c, d);
        value5 = 0;
      }
      TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    }
  if (readKeyFromPad4x4() == 'F') {
    if (value6) {
      lcd.clear();
      lcd.print("Press A to set 1");
      lcd.setCursor(0, 1);
      lcd.print("Press B to set 2");
      value6 = 0;
      }
    }
    
    if (T5.hour == 00 && T5.minute == 00 && T5.second == 00 && beeping == 1) {
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      beeping = 0;
    }

    if (T1.hour == 00 && T1.minute == 00 && T1.second == 00 && beeping == 1) {
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      beeping = 0;
    }
}
