#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;//온도 센서를 제대로 읽고 못 읽었으면 다시 가서 읽기
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature);
  Serial.print((int)humidity); 
  lcd.setCursor(1,1);
   lcd.print((int)temperature);
   lcd.setCursor(3,1);
   lcd.print((char)0xDF);//도씨를 나타내기 위한 똥글뱅이를 나타내는
   lcd.setCursor(4,1);
   lcd.print("C");
  lcd.setCursor(7,1);
  lcd.print((int)humidity);lcd.print("H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);//1500초 이후에 온도 센서 값을 다시 가지고 오겠다.
}
