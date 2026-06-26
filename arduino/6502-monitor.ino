char ADDR[16];
const char DATA[] = {39, 41, 43, 45, 47, 49, 51, 53};
#define CLOCK 2
#define READ_WRITE 3

void setup() {
  for (int i = 0; i < 16; i++) {
    ADDR[i] = 22 + 2 * i;    //[22, 24, .., 50, 52]
    pinMode(ADDR[i], INPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(DATA[i], INPUT);
  }
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);
  
  Serial.begin(57600);
}

void onClock() {
  char output[15];
  
  unsigned int address = 0;
//  for (int i = 0; i < 16; i++) {
  for (int i = 15; i >= 0; i--) {  // 22 is A0
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }
  
  Serial.print("    ");
  
  unsigned int data = 0;
//  for (int i = 0; i < 8; i++) {
  for (int i = 7; i >= 0; i--) {  // 39 is D0
    int bit = digitalRead(DATA[i]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }
  
  sprintf(output, "    %04x  %c %02x", address, digitalRead(READ_WRITE) ? 'r' : 'w', data);
  Serial.println(output)  ;

  if (address >= 0x8000) {
    Serial.println("    addressing EEPROM");
  } else if (address >= 0x6000 && address < 0x7000) {
    Serial.println("    addressing VIA");
  }
}

void loop() {
}
