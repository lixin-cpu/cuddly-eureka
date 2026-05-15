const int LED_PIN = 2;
const unsigned long DOT = 150;
const unsigned long DASH = 450;

const unsigned long sequence[][2] = {
  {HIGH, DOT}, {LOW, DOT},   // S
  {HIGH, DOT}, {LOW, DOT},
  {HIGH, DOT}, {LOW, 3*DOT},
  {HIGH, DASH}, {LOW, DOT},  // O
  {HIGH, DASH}, {LOW, DOT},
  {HIGH, DASH}, {LOW, 3*DOT},
  {HIGH, DOT}, {LOW, DOT},   // S
  {HIGH, DOT}, {LOW, DOT},
  {HIGH, DOT}, {LOW, 2000}
};

const int TOTAL_STEPS = sizeof(sequence) / sizeof(sequence[0]);
int step = 0;
unsigned long prevMillis = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("SOS摩尔斯电码闪烁程序启动");
  Serial.print("总步数：");
  Serial.println(TOTAL_STEPS);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= sequence[step][1]) {
    prevMillis = currentMillis;
    digitalWrite(LED_PIN, sequence[step][0]);

    // 串口输出调试信息
    Serial.print("步骤：");
    Serial.print(step);
    Serial.print("，状态：");
    Serial.print(sequence[step][0] ? "亮" : "灭");
    Serial.print("，时长：");
    Serial.println(sequence[step][1]);

    step = (step + 1) % TOTAL_STEPS;
    if (step == 0) {
      Serial.println("--- SOS信号循环完成 ---");
    }
  }
}