const int pressurePin = A0;
float pressureValue = 0;
float pressurePsi = 0;
float pressureVolts = 0;
const float voutLower = 0.5;
const float voutUpper = 4.5;
const int transducerMaxPsi = 174;

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
  Serial.print(pressurePsi);
  Serial.println("psi");
}

void setup(){
  Serial.begin(9600);
  Serial.print("Welcome to Cytis\n");
}

void loop(){
  pressureValue = analogRead(pressurePin);
  pressurePsi = analogToPsi(pressureValue);
  pressureDebugDisplay();
  delay(500);
}
