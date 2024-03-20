const int n_led = 10;
const int led_pin[n_led] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
// biến trở A0
void setup() {
  for (int i = 0; i < n_led; i++) {
    pinMode(led_pin[i], OUTPUT);
    digitalWrite(led_pin, LOW);
  }
  Serial.begin(9600);
}

// sáng dần theo thứ tự từ trái sang phải rồi tắt dần từ phải sang trái
void led_1(int Delay){
  for (int i = 0; i < n_led; i++) {
    digitalWrite(led_pin[i], HIGH);
    delay(Delay);
  }
  for (int i = n_led - 1; i >= 0; i--) {
    digitalWrite(led_pin[i], LOW);
    delay(Delay);
  }
}

// sáng dần từ hai bên vào trong rồi tắt dần từ trong ra hai bên
void led_2(int Delay){
  for (int i =0; i < int(n_led/2); i++){
    digitalWrite(led_pin[i], HIGH);
    digitalWrite(led_pin[n_led - i - 1], HIGH);
    delay(Delay);
  }

  for (int i =int(n_led/2) - 1; i >= 0 ; i--){
    digitalWrite(led_pin[i], LOW);
    digitalWrite(led_pin[n_led - i - 1], LOW);
    delay(Delay);
  }
}

// sáng lần lượt theo chẵn lẻ
void led_3(int Delay){
  for (int i = 0; i < n_led; i++) {
    delay(Delay);
    if (i % 2 == 0)
    digitalWrite(led_pin[i], HIGH);
  }
  for (int i = 0; i < n_led; i++) {
    delay(Delay);
    if (i % 2 != 0)
    digitalWrite(led_pin[i], HIGH);
  }
  delay(Delay);
  for (int i = 0; i < n_led; i++) {
    digitalWrite(led_pin[i], LOW);
  }
}

int bientro(){
  int value = analodRead(A0);
  return value;
} 

// sáng dần từ mờ tới rõ phụ thuộc vào giá trị đọc từ biến trở
void led_4(int value){
  int out_value;
  out_value = map(value,0,1023,0,255);
  for (int i = 0; i < n_led; i++) {
    digitalWrite(led_pin, out_value);
  }
} 

void loop() {
  led_3();
}