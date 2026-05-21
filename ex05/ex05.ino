// 作业5：多档位触摸调速呼吸灯（终极兼容版，无需任何PWM配置）
const int touchPin = 4;    // 触摸引脚T0 = GPIO4
const int ledPin = 2;       // LED引脚

int speedLevel = 1;         // 1=慢 2=中 3=快
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 200;  // 防抖时间
const int DELAY_TIMES[] = {12, 6, 3};      // 三档延时（数值越小呼吸越快）

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("作业5：多档位触摸呼吸灯启动");
  Serial.println("当前档位：1（慢速）");
}

void loop() {
  // 触摸检测与档位切换（边缘检测+软件防抖）
  bool currentTouch = touchRead(touchPin) < 800;
  unsigned long currentTime = millis();

  if (currentTouch != lastTouchState && 
      currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
    lastDebounceTime = currentTime;
    
    // 仅在触摸按下瞬间切换档位
    if (currentTouch == true) {
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1;  // 循环切换
      Serial.print("切换到档位：");
      Serial.println(speedLevel);
    }
  }
  lastTouchState = currentTouch;

  // 呼吸灯核心逻辑（纯analogWrite实现）
  int currentDelay = DELAY_TIMES[speedLevel - 1];
  
  // 渐亮过程
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(currentDelay);
  }
  // 渐暗过程
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(currentDelay);
  }
}