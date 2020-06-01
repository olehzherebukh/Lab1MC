bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

void writeData() {
  byte two = 0b00000001; //1 0x01 0x02 0xFF 0x03 0x04 0xFF 0x01 0x03 0x03 0x05
  byte four = 0b00000010; //2
  byte zero = 0b00000011; //3
  byte eight = 0b00000100; //4
  byte one = 0b00000101; //5
  byte point = 0b11111111; // 255
  unsigned long n = 51340;
  byte firstByteOfCheckSum = (n >> 8) & 0xFF;
  byte secondByteOfCheckSum = n & 0xFF;

  byte message[12] = {two, four, point, zero,
                      eight, point, two, zero,
                      zero, one, firstByteOfCheckSum, secondByteOfCheckSum};

  for (int i = 0; i < 12; i++) {
    Serial.write(message[i]);
  }
}

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

ISR(USART_TX_vect)
{
  PORTD &= ~(1 << PD2); 
}

void setup() {
  delay(1000);

  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0xEA;
}

void loop() {
  data = (~PIND);
  data = data >> 3;
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
