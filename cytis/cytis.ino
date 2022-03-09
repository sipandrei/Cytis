const int pressurePin = A0;
float pressureValue = 0;
float currentPressurePsi = 0;
float pressureVolts = 0;
const float voutLower = 0.5;
const float voutUpper = 4.5;
const int transducerMaxPsi = 174;
int targetPressure;
const int intakePin1 = 2, intakePin2 = 3, exhaustPin1 = 4, exhaustPin2 = 5;

float analogToPsi(float analogValue){
  pressureVolts = analogValue * 5.0 / 1023.0;
  return transducerMaxPsi * ((pressureVolts - voutLower) / (voutUpper - voutLower));
}

void pressureDebugDisplay(){
  Serial.print("Value ");
  Serial.print(pressureValue);
  Serial.print(" Volt ");
  Serial.print(pressureVolts);
  Serial.print(" Pressure ");
  Serial.print(currentPressurePsi);
  Serial.println("psi");
}

void openValve(int valvePin) {
  digitalWrite(valvePin, HIGH);
}

void closeValve(int valvePin) {
  digitalWrite(valvePin, LOW);
}

void valveCycle(int valvePin) {
  openValve(valvePin);
  delay(100); //valve open time
  closeValve(valvePin);
}

int wholePart(float number){
  int wholeNum;
  wholeNum = number;
  return wholeNum;
}

void pressureAdjust(int intakePin, int exhaustPin) {
  if(wholePart(currentPressurePsi) >= targetPressure)
    valveCycle(exhaustPin); //let out pressure 
  else
    valveCycle(intakePin); //let pressure in
}

void initializeTargetPressure() {
  pressureValue = analogRead(pressurePin);
  currentPressurePsi = analogToPsi(pressureValue);
  targetPressure = currentPressurePsi;
}

void setup(){
  Serial.begin(9600);
  Serial.print("Welcome to Cytis\n");
  pinMode(intakePin1, OUTPUT);
  pinMode(intakePin2, OUTPUT);
  pinMode(exhaustPin1, OUTPUT);
  pinMode(exhaustPin2, OUTPUT);
  initializeTargetPressure();
}

void loop(){
  pressureValue = analogRead(pressurePin);
  currentPressurePsi = analogToPsi(pressureValue);
  //pressureAdjust(intakePin1, exhaustPin1);
  valveCycle(intakePin1);
  pressureDebugDisplay();
  delay(500);
}
