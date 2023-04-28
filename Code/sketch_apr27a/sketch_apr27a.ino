//source: https://ee-diary.com

void setup () {
  // Pin 6 (OC0A) is output
  pinMode(6, OUTPUT);  
   // Load 191 to generate 75% PWM
  OCR0A = 191;
   // 62.5kHz non-inverted PWM on OC0A with no prescalar
  TCCR0A = (1 << COM0A1) | (1<<WGM01) | (1<<WGM00); 
  TCCR0B = (1 << CS00); 
}
void loop() {
}