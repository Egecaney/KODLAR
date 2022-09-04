#include <VarSpeedServo.h>
#include <NewPing.h>
#include <Stepper.h>

#define YPinNumber 36            // ServoY'nin Dijital Pin Numarası
#define SonarTrigPinNumber 24    // Ultrasonik Sensör'ün TRIG Pin Numarası
#define SonarEchoPinNumber 22    // Ultrasonik Sensör'ün ECHO Pin Numarası
#define SonarMaxDistance 200     // Ultrasonik Sensör'ün Maksimum Uzaklığı (cm cinsinden)
#define DirectionPin 3
#define StepPin 4    
#define StepMotorSpeed 4
#define LaserPin 42

VarSpeedServo ServoY;                                  // Y Ekseni için Servo
Stepper StepMotor = Stepper(200,DirectionPin,StepPin);
NewPing Sonar(SonarTrigPinNumber,SonarEchoPinNumber,SonarMaxDistance);

int PositionY = 130;                                    // ServoY'nin Pozisyonu
int PositionofSTEPMotor = 50;                           // Step Motor'un Pozisyonu Radar Ekranı için bilinmeli.
int StepFlag = 0;
int SonarDistance = 0;

char CommandFromPython = ' ';              // PYTHON'dan Gelecek Komut

void ServoYMovement(char RegionY){
      if(RegionY == 'D'){                  // Kamerayı AŞAĞI indirmek için.
        PositionY += 1;
        ServoY.write(PositionY,255,false);
      }
      else if(RegionY == 'U'){             // Kamerayı YUKARI kaldırmak için.
        PositionY -=1;
        ServoY.write(PositionY,255,false);
      }
}

void StepXMovement(char RegionX){
  if(RegionX == 'L'){
    StepMotor.step(StepMotorSpeed);
    PositionofSTEPMotor += 1;
  }
  else if(RegionX == 'R'){
    StepMotor.step(-StepMotorSpeed);
    PositionofSTEPMotor -= 1;
  }
}

void StepTurningAlways(void){
  if(!StepFlag){
    StepMotor.step(StepMotorSpeed);
    PositionofSTEPMotor += 1;
    delay(25);
    if(PositionofSTEPMotor == 100){
      StepFlag = 1;
    }
  }
  else if(StepFlag){
    StepMotor.step(-StepMotorSpeed);
    PositionofSTEPMotor -= 1;
    delay(25);
    if(PositionofSTEPMotor == 0){
      StepFlag = 0;
    }
  }
}

void ReceiveData(void){
  SonarDistance = Sonar.ping_cm();
  if(SonarDistance != 0){
    Serial.print(PositionofSTEPMotor);
    Serial.print(",");
    Serial.print(SonarDistance);
    Serial.print(".");
    delay(20);
  }
}

void setup(){
    ServoY.attach(YPinNumber,400,2600);   // ServoY'yi seçilen dijital pinine bağlanır.
    ServoY.write(PositionY,255,true);     // ServoY'yi başlangıç konumuna getiriyoruz.
    StepMotor.setSpeed(250);              // Step Motor'ın Hızı
    pinMode(SonarTrigPinNumber,OUTPUT);
    pinMode(SonarEchoPinNumber,INPUT);    
    pinMode(LaserPin,OUTPUT);             // Laser Pin'ini OUTPUT olarak tanıtıyoruz.
    Serial.begin(9600);                 // Ardiuno - PYTHON Baud Rate
    Serial.setTimeout(.1);                // Ardiuno - PYTHON Timeout
}

void loop(){
     if (Serial.available()>0){
      CommandFromPython = Serial.read();

      if(CommandFromPython == 'S'){   // Cisim DURMUŞSA
        digitalWrite(LaserPin,HIGH);
        ReceiveData(); 
      }
      if(CommandFromPython == 'D' || CommandFromPython == 'U'){
        ServoYMovement(CommandFromPython);
        digitalWrite(LaserPin,HIGH);
        ReceiveData();
      }
      if(CommandFromPython == 'L' || CommandFromPython == 'R'){
        StepXMovement(CommandFromPython);
        digitalWrite(LaserPin,HIGH);
        ReceiveData(); 
      }
      if(CommandFromPython == 'N'){  // Cisim YOKSA                 
        StepTurningAlways();
        digitalWrite(LaserPin,LOW);
        Serial.print(PositionofSTEPMotor);
        Serial.print(",");
        Serial.print(0);
        Serial.print(".");
      }
  }
  }
