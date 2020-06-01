#define CRC16 0x8005

bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

ISR(USART_TX_vect)
{
  PORTD &= ~(1 << PD2); 
}

int writeData() {
  byte Z = 0b00000001; //1 0x01 0x02 0x03 0x04 0x03 0x05 0x06 0x07 0x02 0xFF 0x08 0x09 0x03 0x02 0xFF 0x0A 0x08 0x09 0x08 0x0B 0x0C 0x0D 0x0C 0x04 0x08 0x0A 0x0C 0x0E 0x02
  byte H = 0b00000010; //2
  byte E = 0b00000011; //3
  byte R = 0b00000100; //4
  byte B = 0b00000101; //5
  byte U = 0b00000110; //6
  byte K = 0b00000111; //7
  byte O = 0b00001000; //8
  byte L = 0b00001001; //9
  byte V = 0b00001010; //10
  byte D = 0b00001011; //11
  byte Y = 0b00001100; //12
  byte M = 0b00001101; //13
  byte C = 0b00001110; //14
  byte space = 0b11111111; // 255
  unsigned long n = 53054;
  byte firstByteOfCheckSum = (n >> 8) & 0xFF;
  byte secondByteOfCheckSum = n & 0xFF;

  byte message[31] = {Z, H, E, R, E, B,
                      U, K, H, space, O, L,
                      E, H, space, V, O, L,
                      O, D, Y, M, Y, R,
                      O, V, Y, C, H, firstByteOfCheckSum
                      , secondByteOfCheckSum};

  for (int i = 0; i < 31; i++) {
    Serial.write(message[i]);
  }
}

void setup() {
  delay(1000);

  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0x0B;
}

void loop() {
  if (Serial.available()) {
    byte inByte = Serial.read();
    if (isAddress) {
      if (address == inByte) {
          isAddress = false;
          isCommand = true;
          UCSR0A &= ~(1 << MPCM0);
        }
    } else if (isCommand) {
      command = inByte;
      isCommand = false;
      if (command = 0xB1) {
          isAddress = true;
          setWriteModeRS485();
          writeData();
        }
    }
  }
}
