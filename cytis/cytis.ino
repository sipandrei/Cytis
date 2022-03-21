 #include <SoftwareSerial.h>
#include <string.h>

const int pressurePin = A0;
const float voutLower = 0.5;
const float voutUpper = 4.5;
const int transducerMaxPsi = 174;
const int intakePin1 = 2, intakePin2 = 3, exhaustPin1 = 4, exhaustPin2 = 5;
const int tx = 7, rx = 6;
float pressureValue = 0;
float currentPressurePsi = 0;
float pressureVolts = 0;
int targetPressure;
char serialInput[16];
bool toSetPressure = false;

SoftwareSerial ble(rx, tx);

float analogToPsi(float analogValue){
  pressureVolts = analogValue * 5.0 / 1023.0;
  return transducerMaxPsi * ((pressureVolts - voutLower) / (voutUpper - voutLower));
}

void pressureDebugDisplay(){
  Serial.print(toSetPressure);
  Serial.print(" Value ");
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

void pinsLow() {
  digitalWrite(intakePin1, LOW);
  digitalWrite(intakePin2, LOW);
  digitalWrite(exhaustPin1, LOW);
  digitalWrite(exhaustPin2, LOW);
}

int wholePart(float number) {
  int wholeNum;
  wholeNum = number;
  return wholeNum;
}

void pressureAdjust(int intakePin, int exhaustPin) {
  readPressure();
  if(wholePart(currentPressurePsi) >= targetPressure)
    valveCycle(exhaustPin); //let pressure out
  else
    valveCycle(intakePin); //let pressure in

  if(wholePart(currentPressurePsi) == targetPressure)
    {
      toSetPressure = false;
      Serial.println("Pressure Adjusted");
    }
}

void initializeTargetPressure() {
  pressureValue = analogRead(pressurePin);
  currentPressurePsi = analogToPsi(pressureValue);
  targetPressure = currentPressurePsi;
}

void commandProcessing(char command[]) {   
  Serial.println(command);
  Serial.println(strcmp(command, "c"));
  if(strcmp(command, "c") == 0){
    Serial.print('.');
    ble.print("current ");
    ble.println(currentPressurePsi);
  }
  else if (strstr(command, "setPressure")) {
    char* slicedCommand = strtok(command, " ");   
    slicedCommand = strtok(NULL, " ");
    if(atoi(slicedCommand) != 0)
    {
      targetPressure = atoi(slicedCommand);
      Serial.print("target pressure set to ");
      Serial.println(targetPressure);
      toSetPressure = true;
      Serial.println("Pressure is adjusting to given target...");
    }
    else
      Serial.println("givenPressure is NULL");
  }
}

void readPressure(){
  pressureValue = analogRead(pressurePin);
  currentPressurePsi = analogToPsi(pressureValue);
}

void setup(){
  Serial.begin(9600);
  ble.begin(9600);
  ble.println("Connected to Cytis");
  Serial.print("Welcome to Cytis\n");
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  pinMode(intakePin1, OUTPUT);
  pinMode(intakePin2, OUTPUT);
  pinMode(exhaustPin1, OUTPUT);
  pinMode(exhaustPin2, OUTPUT);
  pinsLow();
  initializeTargetPressure();
}

void loop(){
  int letter = 0;
  readPressure();
  if(ble.available() > 0){
    while(ble.available() > 0){
      serialInput[letter] = ble.read();
      letter++;
    }
    serialInput[letter]='\0';
    commandProcessing(serialInput);
  }
  if (toSetPressure) {
    pressureAdjust(intakePin1, exhaustPin1);
  }
  pressureDebugDisplay();
  
  delay(500);
}
