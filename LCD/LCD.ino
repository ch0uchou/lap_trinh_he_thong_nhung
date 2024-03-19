#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 5      // Chân dữ liệu của cảm biến DHT11 được kết nối với chân 2 trên Arduino
#define DHTTYPE DHT11 // Loại cảm biến DHT11

int button = 11;

DHT dht(DHTPIN, DHTTYPE);
bool c = true;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Địa chỉ I2C của màn hình LCD và kích thước 16x2

void setup() {
  dht.begin(); // Khởi động cảm biến DHT11
  lcd.init(); // Khởi động màn hình LCD
  lcd.backlight(); // Bật đèn nền cho màn hình LCD
  lcd.print("Nhiet do:"); // In dòng chữ "Nhiet do:" lên màn hình LCD
  pinMode(button, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
  attachInterrupt(0, change, RISING);
}

void loop() {
  delay(2000); // Đợi 2 giây giữa các lần đo để tránh đọc dữ liệu quá nhanh từ cảm biến

  float humidity = dht.readHumidity(); // Đọc độ ẩm từ cảm biến DHT11
  float temperatureC = dht.readTemperature(); // Đọc nhiệt độ từ cảm biến DHT11
  float temperatureF = dht.readTemperature(true); // Đọc nhiệt độ từ cảm biến DHT11
  
  
  lcd.setCursor(0, 1); // Di chuyển con trỏ đến dòng thứ hai của màn hình LCD
  lcd.print("            "); // Xóa nội dung cũ
  lcd.setCursor(0, 1); // Di chuyển con trỏ đến dòng thứ hai của màn hình LCD
  
  // Kiểm tra nếu đọc dữ liệu từ cảm biến thành công
  if (isnan(humidity) || isnan(temperatureC)) {
    lcd.print("Error"); // In ra màn hình nếu có lỗi khi đọc dữ liệu từ cảm biến
  } else {
    if (c == true){
      lcd.print(temperatureC); // In nhiệt độ lên màn hình LCD
      lcd.write(223);
      lcd.print("C"); // In đơn vị đo nhiệt độ (độ C)
    }
    else{
      lcd.print(temperatureF); // In nhiệt độ lên màn hình LCD
      lcd.write(223);
      lcd.print("F"); // In đơn vị đo nhiệt độ (độ C)
    } 
  }
  
}

void change(){
  if (c == true) {
    c=false;
  }
  else {
    c = true;
  }
}