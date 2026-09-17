void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
}

void loop() {
  delay(1000);
  while(1) {
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(7, LOW);
      delay(1000);
  }

}
