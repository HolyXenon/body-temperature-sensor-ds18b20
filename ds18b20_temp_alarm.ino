#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2   // Pin data sensor DS18B20
#define BUZZER_PIN 8     // Pin buzzer (sesuaikan dengan rangkaian kamu)

#define SUHU_NORMAL_MAX 37.2  // Ambang batas atas suhu tubuh normal (°C)

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD, 16x2 karakter

void setup() {
  lcd.begin(16, 2);        // Inisialisasi LCD
  sensors.begin();         // Inisialisasi sensor DS18B20
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  sensors.requestTemperatures(); // Meminta pembacaan suhu
  float temperature = sensors.getTempCByIndex(0); // Mendapatkan suhu dalam derajat Celsius

  lcd.clear();

  if (temperature == -127.00) {
    // Sensor gagal terbaca / tidak terhubung
    lcd.print("Error Sensor");
    digitalWrite(BUZZER_PIN, LOW); // pastikan buzzer mati saat error
  } else {
    lcd.print("Suhu: ");
    lcd.print(temperature);
    lcd.print(" C");

    if (temperature > SUHU_NORMAL_MAX) {
      // Suhu di atas normal -> aktifkan alarm
      lcd.setCursor(0, 1);
      lcd.print("Suhu Tinggi!");
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  delay(1000); // Delay 1 detik sebelum membaca kembali suhu, sekarang berjalan di semua kondisi
}
