/*
This program should beep the buzzer after every 200ms.
Make sure the Jumpers are properly connected on the board.

*/
#define BUZZER PF_2

void setup() {                

  pinMode(BUZZER, OUTPUT);     //Make the appropriate pin as OUTPUT
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(BUZZER, HIGH);   //Turn the buzzer pin HIGH
  delay(200);                   //Wait for 200 ms
  digitalWrite(BUZZER, LOW);    //Turn the buzzer pin LOW
  delay(200);                   //Wait for 200 ms
}
