int LDR = A0;
int value;
void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  value = analogRead(LDR);
  // put your main code here, to run repeatedly:
  Serial.print("Value ");
  Serial.println();
  Serial.println(value);
  delay(1000);
}
