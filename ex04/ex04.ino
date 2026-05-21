// 作业4：触摸自锁开关
const int touchPin = 4;    // 触摸引脚T0(GPIO4)
const int ledPin = 2;       // LED引脚

bool ledState = false;      // LED当前状态
bool lastTouchState = false;// 上一次触摸状态
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;  // 防抖时间200ms

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);  // 初始状态熄灭
}

void loop() {
  // 读取当前触摸状态（触摸时返回值<30，可根据实际调整阈值）
  bool currentTouchState = touchRead(touchPin) < 800;
  unsigned long currentTime = millis();

  // 检测触摸状态变化且过了防抖时间
  if (currentTouchState != lastTouchState && 
      currentTime - lastDebounceTime > debounceDelay) {
    lastDebounceTime = currentTime;
    
    // 仅在触摸按下瞬间（上升沿）翻转LED状态
    if (currentTouchState == true) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }

  lastTouchState = currentTouchState;
}