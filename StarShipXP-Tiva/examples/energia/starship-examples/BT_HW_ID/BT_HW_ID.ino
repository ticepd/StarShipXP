void setup() {
  // initialize both serial ports:
  Serial.begin(38400);
  Serial1.begin(38400);
  Serial1.setTimeout(200);
  Serial1.print("AT+ADDR?\r\n");
  char btAddr[30];
  int num = Serial1.readBytesUntil('\r', btAddr, 25);
  int j;
  Serial.print("Setting Name : STARSHIP-");
  Serial1.print("AT+NAME=STARSHIP-");
  for(j = 14; j < num; j++)
  {
    Serial1.write(btAddr[j]);
    Serial.write(btAddr[j]);
  }
  
  Serial1.print("\r\n");
  Serial.print("\n");
  
  char response[5];
  num = Serial1.readBytesUntil('\r', btAddr, 5);
  for(j = 0; j < num; j++)
  {
    Serial.write(btAddr[j]);
  }

  Serial1.print("AT+RESET\n\r");
}

void loop() {
  
}
