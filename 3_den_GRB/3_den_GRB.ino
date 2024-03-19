int redPin = 3;    // Chân kết nối với đèn LED màu đỏ
int greenPin = 6; // Chân kết nối với đèn LED màu xanh lá cây
int bluePin = 5;  // Chân kết nối với đèn LED màu xanh dương

int lastRedValue = 0;
int lastGreenValue = 0;
int lastBlueValue = 0;
int time = 0;

void setup() {
  Serial.begin(9600); // Khởi động cổng Serial với tốc độ 9600 baud
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // Nếu có dữ liệu được nhận từ cổng Serial
    String inputString = Serial.readStringUntil('\n'); // Đọc dữ liệu từ cổng Serial đến khi gặp ký tự xuống dòng
    inputString.trim(); // Loại bỏ các khoảng trắng từ đầu và cuối chuỗi
    inputString.remove(",");
    // Phân tích chuỗi để lấy giá trị của từng màu
    int rIndex = inputString.indexOf('R');
    int gIndex = inputString.indexOf('G');
    int bIndex = inputString.indexOf('B');
    int dIndex = inputString.indexOf('D');

    // Lấy giá trị của màu đỏ
    int redValue = lastRedValue;
    if (rIndex != -1) {
      String redString = inputString.substring(rIndex + 1);
      redValue = min(constrain(redString.toInt(), 0, 255), 255);
      lastRedValue = redValue;
    }

    // Lấy giá trị của màu xanh lá cây
    int greenValue = lastGreenValue;
    if (gIndex != -1) {
      String greenString = inputString.substring(gIndex + 1);
      greenValue = min(constrain(greenString.toInt(), 0, 255), 255);
      lastGreenValue = greenValue;
    }

    // Lấy giá trị của màu xanh dương
    int blueValue = lastBlueValue;
    if (bIndex != -1) {
      String blueString = inputString.substring(bIndex + 1);
      blueValue = min(constrain(blueString.toInt(), 0, 255), 255);
      lastBlueValue = blueValue;
    }
    
    int timeValue = time;
    if (dIndex != -1) {
      String timeString = inputString.substring(dIndex + 1);
      timeValue = constrain(timeString.toInt(), 0, 255);
      time = timeValue;
    }
    else
    {
      time = -1;
    }
    // Điều khiển độ sáng của các đèn LED
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

    if(time != -1)
    {
      // Serial.println("oke");
      delay (time*1000);

      lastRedValue = 0;
      lastGreenValue = 0;
      lastBlueValue = 0;

      analogWrite(redPin, lastRedValue);
      analogWrite(greenPin, lastGreenValue);
      analogWrite(bluePin, lastBlueValue);
    }
  }
}