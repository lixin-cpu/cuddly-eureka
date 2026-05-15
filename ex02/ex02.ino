const int LED_PIN = 4;
const unsigned long BLINK_INTERVAL = 500;

bool ledState = LOW;
unsigned long lastToggleTime = 0;
unsigned long blinkCount = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("1Hz LED闪烁程序启动");
  Serial.print("闪烁间隔：");
  Serial.print(BLINK_INTERVAL);
  Serial.println("ms");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastToggleTime >= BLINK_INTERVAL) {
    lastToggleTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    blinkCount++;
    
    // 串口输出调试信息
    Serial.print("第");
    Serial.print(blinkCount);
    Serial.print("次翻转，当前状态：");
    Serial.println(ledState ? "亮" : "灭");
  }
}