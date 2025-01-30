#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// ---- 定数の設定 ----
#define MAX_SIGNAL 1700  // 最大のPWM信号幅（マイクロ秒単位）
#define MIN_SIGNAL 1300  // 最小のPWM信号幅（マイクロ秒単位）
#define NUM_CHANNELS 4   // 使用するモーターの数

// Adafruit PWM Servo Driverのインスタンスを作成
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(115200); // シリアル通信を初期化
  pwm.begin();
  pwm.setPWMFreq(50); // 50Hz（サーボモーター用）

  Serial.println("Enter PWM value (1300-1700):");
}

void loop() {
  if (Serial.available()) {
    int pulseWidth = Serial.parseInt(); // シリアルから数値を取得
    if (pulseWidth >= MIN_SIGNAL && pulseWidth <= MAX_SIGNAL) {
      int pulse = map(pulseWidth, MIN_SIGNAL, MAX_SIGNAL, 102, 512);
      
      // すべてのチャネルに送信
      for (int i = 0; i < NUM_CHANNELS; i++) {
        pwm.setPWM(i, 0, pulse);
      }

      Serial.print("PWM set to: ");
      Serial.println(pulseWidth);
    } else {
      Serial.println("Invalid input. Enter a value between 1300 and 1700.");
    }
  }
}
