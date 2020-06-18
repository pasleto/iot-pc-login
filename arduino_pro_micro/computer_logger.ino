
#include <CzechKeyboard_QWERTZ.h> //if using czech language based windows
// #include <Keyboard.h> //if using english language based windows
#include <SPI.h>
#include <MFRC522.h>

#define SDA_PIN 10
#define RST_PIN 9

MFRC522 rfid(SDA_PIN, RST_PIN);

String password = "My_computer_password_or_pin";
int pin_login = 4;
int pin_logout = 5;

void setup() {
  pinMode(pin_login, INPUT);
  pinMode(pin_logout, INPUT);
  Keyboard.begin();
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()){ // card detected
    if (rfid.PICC_ReadCardSerial()){ // card readed
      // REPLACE 0xXX to your M1 Chip UID eg. 0xAB 0x01 0xA1 0x0B
      if(rfid.uid.uidByte[0] == 0xXX & rfid.uid.uidByte[1] == 0xXX & rfid.uid.uidByte[2] == 0xXX & rfid.uid.uidByte[3] == 0xXX) { // login on Jakcom R3 M1 Chip
        Keyboard.press(KEY_ESC);
        Keyboard.release(KEY_ESC);
        delay(500);
        Keyboard.print(password);
        delay(500);
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
      }
      // REPLACE 0xXX to your NFC Chip UID eg. 0xAB 0x01 0xA1 0x0B 0xAB 0x01 0xA1
      if(rfid.uid.uidByte[0] == 0xXX & rfid.uid.uidByte[1] == 0xXX & rfid.uid.uidByte[2] == 0xXX & rfid.uid.uidByte[3] == 0xXX & rfid.uid.uidByte[4] == 0xXX & rfid.uid.uidByte[5] == 0xXX & rfid.uid.uidByte[6] == 0xXX) { // logout on Jakcom R3 NFC Chip
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('l');
        delay(500);
        Keyboard.releaseAll();
      }    
    }
  }

  if ( digitalRead(pin_login) == HIGH ){ // login on pin activate
    Keyboard.press(KEY_ESC);
    Keyboard.release(KEY_ESC);
    delay(500);
    Keyboard.print(password);
    delay(500);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
  }
  
  if ( digitalRead(pin_logout) == HIGH ){ // logout on pin activate
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(500);
    Keyboard.releaseAll();
  }
}
