int a = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
}

void loop() {
  delay(1000);
  while( a < 5 ) {
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(7, LOW);
      delay(1000);
      a = a + 1;
  }

}
