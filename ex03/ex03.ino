// 定义LED引脚
const int ledPin = 2;

// 摩尔斯电码步骤结构体：存储LED状态和持续时间
struct MorseStep {
  bool ledState;    // true=亮，false=灭
  unsigned long duration;  // 持续时间（ms）
};

// SOS信号完整步骤序列
MorseStep sosSequence[] = {
  {HIGH, 150},  // 短闪1
  {LOW, 150},   // 短灭1
  {HIGH, 150},  // 短闪2
  {LOW, 150},   // 短灭2
  {HIGH, 150},  // 短闪3
  {LOW, 450},   // 字符间隔（S-O）
  {HIGH, 450},  // 长闪1
  {LOW, 150},   // 长灭1
  {HIGH, 450},  // 长闪2
  {LOW, 150},   // 长灭2
  {HIGH, 450},  // 长闪3
  {LOW, 450},   // 字符间隔（O-S）
  {HIGH, 150},  // 短闪4
  {LOW, 150},   // 短灭4
  {HIGH, 150},  // 短闪5
  {LOW, 150},   // 短灭5
  {HIGH, 150},  // 短闪6
  {LOW, 2000}   // 单词间隔（SOS结束停顿）
};

// 计算序列总步数
const int stepCount = sizeof(sosSequence) / sizeof(sosSequence[0]);

// 当前执行的步骤索引
int currentStep = 0;

// 上一次步骤切换的时间戳
unsigned long previousMillis = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // 初始状态熄灭
}

void loop() {
  unsigned long currentMillis = millis();

  // 判断当前步骤是否执行完毕
  if (currentMillis - previousMillis >= sosSequence[currentStep].duration) {
    // 更新步骤切换时间
    previousMillis = currentMillis;

    // 执行当前步骤的LED状态
    digitalWrite(ledPin, sosSequence[currentStep].ledState);

    // 切换到下一步，到达末尾则从头开始循环
    currentStep = (currentStep + 1) % stepCount;
  }
}