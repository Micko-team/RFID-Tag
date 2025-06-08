#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10   
#define RST_PIN 9   
#define OUTPUT_PIN 2 

bool shiva = true;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(OUTPUT_PIN, OUTPUT);  
  digitalWrite(OUTPUT_PIN, LOW); 

  Serial.println("Ready to scan RFID tag...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID Tag: ");
  bool match = true;
  
  byte targetUID[] = {0x79, 0x9B, 0xDB, 0x6D};

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");

    if (rfid.uid.uidByte[i] != targetUID[i]) {
      match = false;
    }
  }
  Serial.println();

  if (match) {
    if (shiva){
    Serial.println("Turning LED ON");
    digitalWrite(OUTPUT_PIN, HIGH);
    shiva = false;
    }

    else {
    Serial.println("Turning LED OFF");
    digitalWrite(OUTPUT_PIN, LOW);
    shiva = true;
  }

  } else {
    Serial.println("Access Denied");
    return;
  }

  rfid.PICC_HaltA();
}
