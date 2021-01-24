#define WRITE_PIN A5
#define ADDRESS_START 2
#define ADDRESS_SIZE 4
#define DATA_START 6
#define DATA_SIZE 8
#define FLASH_TIME 500
#define INTERVAL 1000

void setup() {
  pinMode(WRITE_PIN, OUTPUT);
  for (int i = ADDRESS_START; i < ADDRESS_START+ADDRESS_SIZE; i++)
    pinMode(i, OUTPUT);
  for (int i = DATA_START; i < DATA_START+DATA_SIZE; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
  while (!Serial.available())
    delay(100);
  int byte;
  while (Serial.available()) {
    byte = Serial.read();
    for (int i = 0; i < ADDRESS_SIZE; i++)
      digitalWrite(ADDRESS_START+i, byte & (1<<i) ? HIGH : LOW);
    byte = Serial.read();
    for (int i = 0; i < DATA_SIZE; i++)
      digitalWrite(DATA_START+i, byte & (1<<i) ? HIGH : LOW);
    delay(FLASH_TIME); digitalWrite(WRITE_PIN, HIGH);
    delay(FLASH_TIME); digitalWrite(WRITE_PIN, LOW);
    delay(INTERVAL);
  }
}

void loop() {}
