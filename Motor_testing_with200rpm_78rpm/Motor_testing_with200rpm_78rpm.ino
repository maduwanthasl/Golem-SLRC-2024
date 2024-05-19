#define leftmotor_pwm 9
#define rightmotor_pwm 8
#define leftmotor_forward 26
#define rightmotor_forward 22
#define leftmotor_backward 28
#define rightmotor_backward 24

const int lspeed = 255;
const int rspeed = 40;


void setup() {
  // put your setup code here, to run once:
  pinMode(leftmotor_pwm, OUTPUT);
  pinMode(leftmotor_forward, OUTPUT);
  pinMode(leftmotor_backward, OUTPUT);
  pinMode(rightmotor_pwm, OUTPUT);
  pinMode(rightmotor_forward, OUTPUT);
  pinMode(rightmotor_backward, OUTPUT);

  analogWrite(leftmotor_pwm, lspeed);
  analogWrite(rightmotor_pwm, rspeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(leftmotor_forward, LOW);
  digitalWrite(leftmotor_backward, LOW);
  digitalWrite(rightmotor_forward, LOW);
  digitalWrite(rightmotor_backward, HIGH);
}
