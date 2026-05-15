// 定义LED引脚（Arduino Uno板载LED为13号引脚）
const int ledPin = 2;

// 存储LED当前状态
bool ledState = LOW;

// 存储上一次LED状态翻转的时间戳
unsigned long previousMillis = 0;

// 闪烁间隔（1Hz周期=1000ms，亮灭各500ms）
const long interval = 500;

void setup() {
  // 设置LED引脚为输出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 获取当前系统毫秒数
  unsigned long currentMillis = millis();

  // 判断是否达到翻转间隔
  if (currentMillis - previousMillis >= interval) {
    // 更新上一次翻转时间
    previousMillis = currentMillis;

    // 翻转LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}