
void setup() {
  // initialize both serial ports:
  pinMode(PB_3, OUTPUT);
  pinMode(PC_4, OUTPUT);
  pinMode(PF_0, OUTPUT);

  pinMode(PE_4, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PA_5, OUTPUT);
  pinMode(PC_6, OUTPUT);

  digitalWrite(PE_4, HIGH);
  digitalWrite(PE_3, HIGH);
  digitalWrite(PA_5, HIGH);
  digitalWrite(PC_6, HIGH);
    
  pinMode(PF_4, INPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  // read from port 1, send to port 0:
  digitalWrite(PB_3, digitalRead(PF_4));
  digitalWrite(PC_4, !digitalRead(PF_4));
  digitalWrite(PF_0, digitalRead(PF_4));
  
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte); 
  }
  if (Serial.available()) {
    int outByte = Serial.read();
    Serial1.write(outByte); 
  }

}
