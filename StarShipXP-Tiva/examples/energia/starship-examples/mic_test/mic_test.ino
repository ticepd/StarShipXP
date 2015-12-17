void setup()
{
  // put your setup code here, to run once:
  pinMode(PE_2, INPUT);
  pinMode(PF_2, OUTPUT);
  pinMode(PF_3, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int micValue = analogRead(PE_2);
  micValue = 127 + ((micValue - 2048)/4);
  analogWrite(PF_2, micValue);
  analogWrite(PF_3, micValue);
}
