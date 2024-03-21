const int n_led = 10;
const int led_pin[n_led] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const int led_pin_tro[n_led] = {11, 10, 9, 6, 5}; // 10 đèn độ sáng tuỳ vào biến trở
int pin = 0;


// biến trở A0
void setup() {
  for (int i = 0; i < n_led; i++) {
    pinMode(led_pin[i], OUTPUT);
    digitalWrite(led_pin, LOW);
  }
  Serial.begin(9600);
}

// sáng dần theo thứ tự từ trái sang phải rồi tắt dần từ phải sang trái
void led_1(int Delay, boolean checkbientro){
  for (int i = 0; i < n_led; i++) {
    digitalWrite(led_pin[i], HIGH);
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
  }
  for (int i = n_led - 1; i >= 0; i--) {
    digitalWrite(led_pin[i], LOW);
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
  }
}

// sáng dần từ hai bên vào trong rồi tắt dần từ trong ra hai bên
void led_2(int Delay, int value, boolean checkbientro){
  for (int i =0; i < int(n_led/2); i++){
    digitalWrite(led_pin[i], value);
    digitalWrite(led_pin[n_led - i - 1], value);
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
  }

  for (int i =int(n_led/2) - 1; i >= 0 ; i--){
    digitalWrite(led_pin[i], abs(value - 255));
    digitalWrite(led_pin[n_led - i - 1], abs(value - 255));
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
  }
}

// sáng lần lượt theo chẵn lẻ
void led_3(int Delay, boolean checkbientro, int check){
  for (int i = 0; i < n_led; i++) {
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
    if (i % 2 == check)
    digitalWrite(led_pin[i], HIGH);
  }
  for (int i = 0; i < n_led; i++) {
    if (checkbientro) Delay = bientro(); 
    delay(Delay);
    if (i % 2 != check)
    digitalWrite(led_pin[i], HIGH);
  }
  if (checkbientro) Delay = bientro(); 
  delay(Delay);
  for (int i = 0; i < n_led; i++) {
    digitalWrite(led_pin[i], LOW);
  }
}

int bientro(){
  int value = analogRead(pin);
  return value;
} 

// sáng dần từ mờ tới rõ phụ thuộc vào giá trị đọc từ biến trở
void led_4(int value){
  value /=4;
  for (int i = 0; i < n_led; i++) {
    analogWrite(led_pin_tro[i], value);
  }

} 

void loop() {
  // sáng dần theo thứ tự từ trái sang phải rồi tắt dần từ phải sang trái delay 200, có biến trở true
  // led_1(200, true);
  
  //sáng dần từ hai bên vào trong rồi tắt dần từ trong ra hai bên delay 200
  // led_2(200, 255, true);
  
  //sáng dần từ trong ra hai bên rồi tắt dần từ hai bên vào trong delay 200, không có biến trở false
  // led_2(200, 0, false);
  
  // sáng lần lượt theo lẻ -> chẵn delay 200, có biến trở true
  // led_3(200, 0, true);
  
  // sáng lần lượt theo chẵn -> lẻ delay 200, có biến trở true
  // led_3(200, 1, true);
  
  //10 đèn độ sáng tuỳ vào biến trở
  // led_4(bientro());
}