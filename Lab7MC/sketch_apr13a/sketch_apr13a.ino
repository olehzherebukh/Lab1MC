

const int buttonPin1 = 21;
const int buttonPin2 = 20;
const int buttonPin3 = 19;
const int buttonPin4 = 18;
const int num0 = 0xC0; // 0
const int num1 = 0xF9; // 1
const int num2 = 0xA4; // 2
const int num3 = 0xB0; // 3
const int num4 = 0x99; // 4
const int num5 = 0x92; // 5
const int num6 = 0x82; // 6
const int num7 = 0xF8; // 7
const int num8 = 0x80; // 8
const int num9 = 0x90; // 9
const int dot = 0x7F; // .
int timer1 = 1;
int timer5 = 0;
bool beepingt1 = 1;
bool beepingt5 = 1;

char sixty[60][3] = {
  {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"},
  {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"},
  {"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"},
  {"30"}, {"31"}, {"32"}, {"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"},
  {"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"},
  {"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"},
};

char mysym[6][7] = {"HELLOi", "iHELLO", "OiHELL", "LOiHEL", "LLOiHE", "ELLOiH"};

struct Time
{
  unsigned char second, minute, hour;
};
Time T1 = {6, 0, 0};

Time T5 = {4, 0, 0};

void seg_disp(String str, int type)
{
  if (type == 1) {
    char a = str.charAt(1);
    char b = str.charAt(0);
    PORTB = 0b00100000;
    setValue(a);
    delay(1);
    PORTB = 0b00010000;
    setValue(b);
    delay(1);
    PORTB = 0b00000000;
  } else if (type == 2) {
    char c = str.charAt(1);
    char d = str.charAt(0);
    PORTB = 0b00001000;
    setValue(c);
    delay(1);
    setValue('d');
    delay(1);
    PORTB = 0b00000100;
    setValue(d);
    delay(1);
    PORTB = 0b00000000;
  } else if (type == 3) {
    char e = str.charAt(1);
    char f = str.charAt(0);
    PORTB = 0b00000010;
    setValue(e);
    delay(1);
    setValue('d');
    delay(1);
    PORTB = 0b00000001;
    setValue(f);
    delay(1);
    PORTB = 0b00000000;
  } else if (type == 4) {
    char g = str.charAt(0);
    char h = str.charAt(1);
    char i = str.charAt(2);
    char j = str.charAt(3);
    char k = str.charAt(4);
    char m = str.charAt(5);
    PORTB = 0b00000001;
    setValue(g);
    delay(1);
    PORTB = 0b00000010;
    setValue(h);
    delay(1);
    PORTB = 0b00000100;
    setValue(i);
    delay(1);
    PORTB = 0b00001000;
    setValue(j);
    delay(1);
    PORTB = 0b00010000;
    setValue(k);
    delay(1);
    PORTB = 0b00100000;
    setValue(m);
    delay(1);
//  PORTC = 0b10001001;
//  delay(1);
//  PORTB = 0b00000010;
//  PORTC = 0b10000110;
//  delay(1);
//  PORTB = 0b00000100;
//  PORTC = 0b11000111;
//  delay(1);
//  PORTB = 0b00001000;
//  PORTC = 0b11000111;
//  delay(1);
//  PORTB = 0b00010000;
//  PORTC = num0;
//  delay(1);
  }
}

//void seg_hello(char a) {
//  setValue(a);
//}

ISR(TIMER1_COMPA_vect)
{
  if (T1.second-- == 00)
  {
    T1.second = 59;
    if (T1.minute-- == 00)
    {
      T1.minute = 59;
      if (T1.hour-- == 00)
       if (T1.second == 0 && T1.minute == 0 && T1.hour == 1) {
          T1.hour = 0;
          T1.second = 59;
          T1.minute = 59;
        } else {
        T1.hour = 00;
      T1.second = 00;
      T1.minute = 00;
        }
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
        if (T5.second == 0 && T5.minute == 0 && T5.hour == 1) {
          T5.hour = 0;
          T5.second = 59;
          T5.minute = 59;
        } else {
        T5.hour = 00;
      T5.second = 00;
      T5.minute = 00;
        }
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
}

void setValue(char a) {
  if (a == '0') {
    PORTC = num0;
    delay(1);
  } else if (a == '1') {
    PORTC = num1;
    delay(1);
  } else if (a == '2') {
    PORTC = num2;
    delay(1);
  } else if (a == '3') {
    PORTC = num3;
    delay(1);
  } else if (a == '4') {
    PORTC = num4;
    delay(1);
  } else if (a == '5') {
    PORTC = num5;
    delay(1);
  } else if (a == '6') {
    PORTC = num6;
    delay(1);
  } else if (a == '7') {
    PORTC = num7;
    delay(1);
  } else if (a == '8') {
    PORTC = num8;
    delay(1);
  } else if (a == '9') {
    PORTC = num9;
    delay(1);
  } else if (a == 'd') {
    PORTC = dot;
    delay(1);
  } else if (a == 'H') {
    PORTC = 0b10001001;
    delay(1);
  } else if (a == 'E') {
    PORTC = 0b10000110;
    delay(1);
  } else if (a == 'L') {
    PORTC = 0b11000111;
    delay(1);
  } else if (a == 'O') {
    PORTC = num0;
    delay(1);
  } else if (a == 'i') {
    PORTC = 0b11110111;
    delay(1);
  }
}

void setup() {
  noInterrupts();
  Serial.begin(9600);
  DDRA = 0xFF;
  PORTA = 0x00;
  DDRB = 0xFF;
  PORTB = 0x00;
  DDRC = 0xFF;
  PORTC = 0x00;
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 = (0 << OCIE1A);
  OCR1A = 0x2DC6;

  TCCR5A = 0x00;
  TCCR5B = (1 << WGM52) | (1 << CS52) | (1 << CS50);
  TIMSK5 = (0 << OCIE5A);
  OCR5A = 0x2DC6;
  interrupts();
}

void loop() {
//  if (digitalRead(buttonPin1) == LOW && timer1 == 1) {
//    T1.hour ++;
//    beepingt1 = 1;
//    delay(200);
//  } else if (digitalRead(buttonPin1) == LOW && timer5 == 1) {
//    T5.hour ++;
//    beepingt5 = 1;
//    delay(200);
//  }
//
//  if (digitalRead(buttonPin2) == LOW && timer1 == 1) {
//    T1.minute ++;
//    beepingt1 = 1;
//    delay(200);
//  } else if (digitalRead(buttonPin2) == LOW && timer5 == 1) {
//    T5.minute ++;
//    beepingt5 = 1;
//    delay(200);
//  }
//
//  if (digitalRead(buttonPin3) == LOW && timer1 == 1) {
//    timer1 = 0;
//    timer5 = 1;
//    delay(200);
//  } else if (digitalRead(buttonPin3) == LOW && timer5 == 1) {
//    timer1 = 1;
//    timer5 = 0;
//    delay(200);
//  }
//
//  if (digitalRead(buttonPin4) == LOW && timer1 == 1 && TIMSK1 == (1 << OCIE1A)) {
//    TIMSK1 = (0 << OCIE1A);
//    T1.hour = 0;
//    T1.minute = 0;
//    T1.second = 0;
//    beepingt1 = 0;
//    delay(200);
//  } else if (digitalRead(buttonPin4) == LOW && timer5 == 1 && TIMSK5 == (1 << OCIE5A)) {
//    TIMSK5 = (0 << OCIE5A);
//    T5.hour = 0;
//    T5.minute = 0;
//    T5.second = 0;
//    beepingt5 = 0;
//    delay(200);
//  }
//
//  if (digitalRead(buttonPin4) == LOW && timer1 == 1) {
//    TIMSK1 = (1 << OCIE1A);
//    delay(200);
//  } else if (digitalRead(buttonPin4) == LOW && timer5 == 1) {
//    TIMSK5 = (1 << OCIE5A);
//    delay(200);
//  }
//
//  if (T1.hour == 00 && T1.minute == 00 && T1.second == 00 && beepingt1 == 1) {
//    for (int i = 0; i < 3; i++) {
//      PORTA = 0b00000010;
//      delay(500);
//      PORTA = 0b00000000;
//      delay(500);
//    }
//    TIMSK1 = (0 << OCIE1A);
//    beepingt1 = 0;
//  }
//
//  if (T5.hour == 00 && T5.minute == 00 && T5.second == 00 && beepingt5 == 1) {
//    for (int i = 0; i < 3; i++) {
//      PORTA = 0b00000010;
//      delay(500);
//      PORTA = 0b00000000;
//      delay(500);
//    }
//    TIMSK5 = (0 << OCIE5A);
//    beepingt5 = 0;
//  }
//
//  if (timer1 == 1) {
//    seg_disp(sixty[T1.second], 1);
//    seg_disp(sixty[T1.minute], 2);
//    seg_disp(sixty[T1.hour], 3);
//  }
//
//  if (timer5 == 1) {
//    seg_disp(sixty[T5.second], 1);
//    seg_disp(sixty[T5.minute], 2);
//    seg_disp(sixty[T5.hour], 3);
//  }

 
//  PORTB = 0b00000001;
//  PORTC = 0b10001001;
//  delay(1);
//  PORTB = 0b00000010;
//  PORTC = 0b10000110;
//  delay(1);
//  PORTB = 0b00000100;
//  PORTC = 0b11000111;
//  delay(1);
//  PORTB = 0b00001000;
//  PORTC = 0b11000111;
//  delay(1);
//  PORTB = 0b00010000;
//  PORTC = num0;
//  delay(1);
  

  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[0], 4);
    delay(1);
    }
  delay(50);
  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[1], 4);
    delay(1);
    }
  delay(50);
  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[2], 4);
    delay(1);
    }
  delay(50);
  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[3], 4);
    delay(1);
    }
    delay(50);
  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[4], 4);
    delay(1);
    }
    delay(50);
  for (int i = 0; i < 6; i ++) {
    seg_disp(mysym[5], 4);
    delay(1);
    }
    delay(50);
}
