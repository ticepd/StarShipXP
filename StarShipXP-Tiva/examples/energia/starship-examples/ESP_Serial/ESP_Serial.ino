
void setup() {
  // initialize both serial ports:
  Serial.begin(921600);
  Serial1.begin(921600);
}

void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte); 
  }
  if (Serial.available()) {
    int outByte = Serial.read();
    Serial1.write(outByte); 
  }

}
