void setup() {
  //////////////////////////////////////////////////////////////////////

  // set up PWM timer with default values:
  OCR0A = 100;
  OCR0B = 20;
  // 160kHz non-inverted PWM on OC0A with no prescaler
  TCCR0A = (1 << COM0A1) | (1<<WGM01) | (1<<WGM00); 
  TCCR0B = (1 << CS00);

//////////////////////////////////////////////////////////////////////

}

void loop() {
  // put your main code here, to run repeatedly:

}
