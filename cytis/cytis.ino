#include <SoftwareSerial.h>
#include <Servo.h>
#include <string.h>

Servo servoIntake;
const int pressurePin = A0;
const float voutLower = 0.5;
const float voutUpper = 4.5;
const int transducerMaxPsi = 174;
const int exhaustPin = 2;
const int servoPin = 5;
const int tx = 4, rx = 3;
float pressureValue = 0;
float currentPressurePsi = 0;
float pressureVolts = 0;
int targetPressure;
char serialInput[16];
bool toSetPressure = false;

SoftwareSerial ble(rx, tx);

// functie pentru a transforma valoarea de pe pinul analogic in psi
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

// ciclaza valva la 100 milisecunde
void valveCycle(int valvePin) {
  openValve(valvePin);
  delay(100); //valve open time
  closeValve(valvePin);
}

// initializeaza valva si servoul
void pinsLow() {
  digitalWrite(exhaustPin, LOW);
  servoIntake.write(0);
  delay(10);
 }

int wholePart(float number) {
  int wholeNum;
  wholeNum = number;
  return wholeNum;
}

// controlul servoului, se misca 100 de grade
void pressureIn(Servo servo){
  
  for(int pos = 0; pos <= 100; pos++){
    servo.write(pos);
    delay(10);
  }
}

// functia pentru ajustarea presiunii, lasa daca e prea mare, introduce daca e prea mica
void pressureAdjust(int intakePin, int exhaustPin) {
  readPressure();
  if(wholePart(currentPressurePsi) >= targetPressure)
     valveCycle(exhaustPin);//let pressure out
  else
    {
      pressureIn(servoIntake); // let pressure in
      servoIntake.write(0);
      delay(20);
      toSetPressure = false; // failsafe for servo
    }

  if(wholePart(currentPressurePsi) == targetPressure)
    {
      toSetPressure = false;
      Serial.println("Pressure Adjusted");
    }
}

// initializeaza presiunea tinta cu valoarea actuala, just for peace of mind
void initializeTargetPressure() {
  pressureValue = analogRead(pressurePin);
  currentPressurePsi = analogToPsi(pressureValue);
  targetPressure = currentPressurePsi;
}

// procesarea comenzilor de la bluetooth
void commandProcessing(char command[]) {   
  Serial.println(command);
  Serial.println(strcmp(command, "c")); // comanda c returneaza presiunea curenta
  if(strcmp(command, "c") == 0){
    Serial.print('.');
    ble.print("current ");
    ble.println(currentPressurePsi);
  }
  else if (strstr(command, "setPressure")) { // comanda setPressure <numar> schimba presiunea tinta si incepe a merge spre ea
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
  servoIntake.attach(servoPin);
  ble.begin(9600);
  ble.println("Connected to Cytis");
  Serial.print("Welcome to Cytis\n");
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  pinMode(exhaustPin, OUTPUT);
  pinsLow();
  initializeTargetPressure();
}

void loop(){
  int letter = 0;
  readPressure();
  if(ble.available() > 0){ // citirea comenzilor de la bluetooth
    while(ble.available() > 0){
      serialInput[letter] = ble.read();
      letter++;
    }
    serialInput[letter]='\0';
    commandProcessing(serialInput);
  }
  if (toSetPressure) { // actioneaza schimbarea presiunii doar imediat dupa o comanda setPressure
    pressureAdjust(servoPin, exhaustPin);
    delay(20);
    servoIntake.write(0);
  }
  pressureDebugDisplay();
  
  delay(500);
}
