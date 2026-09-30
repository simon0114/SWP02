// Arduino pin assignment
#define PIN_LED  9    // PWM 가능 핀 (Uno 기준 3, 5, 6, 9, 10, 11)
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 300.0   // maximum distance to be measured (unit: mm)
#define _DIST_MID 200.0   // LED가 가장 밝은 거리 (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficent to convert duration to distance

unsigned long last_sampling_time;   // unit: msec

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  float distance;
  int duty;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO);

  // 측정 실패(0)이거나 범위를 벗어나면 경계값으로 고정
  if ((distance == 0.0) || (distance > _DIST_MAX)) {
    distance = _DIST_MAX;
  } else if (distance < _DIST_MIN) {
    distance = _DIST_MIN;
  }

  // 200mm에서 0(최대 밝기), 100mm/300mm에서 255(꺼짐)
  duty = (int)(255.0 * fabs(distance - _DIST_MID) / (_DIST_MID - _DIST_MIN));
  analogWrite(PIN_LED, duty);

  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.print(",duty:");      Serial.print(duty);
  Serial.println("");

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}
