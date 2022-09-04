#include <VarSpeedServo.h>
#include <NewPing.h>
#include <Stepper.h>

#define YPinNumber 36            // ServoY'nin Dijital Pin Numarası
#define SonarTrigPinNumber 24    // Ultrasonik Sensör'ün TRIG Pin Numarası
#define SonarEchoPinNumber 22    // Ultrasonik Sensör'ün ECHO Pin Numarası
#define SonarMaxDistance 150     // Ultrasonik Sensör'ün Maksimum Uzaklığı (cm cinsinden)
#define DirectionPin 3
#define StepPin 4    
#define StepMotorSpeed 2
#define LaserPin 42

VarSpeedServo ServoY;                                  // Y Ekseni için Servo
Stepper StepMotor = Stepper(200,DirectionPin,StepPin);

int PositionY = 90;                                    // ServoY'nin Pozisyonu
int PositionofSTEPMotor = 0;                           // Step Motor'un Pozisyonu Radar Ekranı için bilinmeli.
float SonarDistanceinMeter = 0;                                 // Ultrasonik Sensör'ün Pozisyonu Radar Ekranı için bilinmeli.

char CommandFromPython = ' ';              // PYTHON'dan Gelecek Komut

void ServoYMovement(char RegionY){
      if(RegionY == 'D'){                  // Kamerayı AŞAĞI indirmek için.
        PositionY += 2;
        ServoY.write(PositionY,255,false);
      }
      else if(RegionY == 'U'){             // Kamerayı YUKARI kaldırmak için.
        PositionY -=2;
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
void FindSonarDistance(void){
  long int Time;
  float Distance;
  digitalWrite(SonarTrigPinNumber,LOW);
  delayMicroseconds(2);
  digitalWrite(SonarTrigPinNumber,HIGH);
  delayMicroseconds(10);
  digitalWrite(SonarTrigPinNumber,LOW);
  Time = pulseIn(SonarEchoPinNumber,HIGH);
  Distance = (Time*0.034)/2 ;
  if(Distance>0 && Distance < SonarMaxDistance){
    SonarDistanceinMeter = Distance/100;
  }
}
void StepTurningAlways(void){
  StepMotor.step(StepMotorSpeed);
  PositionofSTEPMotor += 1;
}

void ReceiveData(void){
  float SendData;
  if(PositionofSTEPMotor < 0){
    PositionofSTEPMotor += 200;
  }
  if(PositionofSTEPMotor > 200){
     PositionofSTEPMotor -= 200;
  }
  SendData = PositionofSTEPMotor*10 + SonarDistanceinMeter;
  Serial.println(SendData,1);
  SendData = 0;
}

void setup(){
    ServoY.attach(YPinNumber,400,2600);   // ServoY'yi seçilen dijital pinine bağlanır.
    ServoY.write(PositionY,255,true);     // ServoY'yi başlangıç konumuna getiriyoruz.
    StepMotor.setSpeed(250);              // Step Motor'ın Hızı
    //pinMode(SonarTrigPinNumber,OUTPUT);
    //pinMode(SonarEchoPinNumber,INPUT);    
    pinMode(LaserPin,OUTPUT);             // Laser Pin'ini OUTPUT olarak tanıtıyoruz.
    Serial.begin(115200);                 // Ardiuno - PYTHON Baud Rate
    Serial.setTimeout(.1);                // Ardiuno - PYTHON Timeout
    }

void loop(){
     if (Serial.available()>0){
      CommandFromPython = Serial.read();

      if(CommandFromPython == 'S'){   // Cisim DURMUŞSA
      //  FindSonarDistance();
        digitalWrite(LaserPin,LOW);
        //ReceiveData(); 
      }
      if(CommandFromPython == 'D' || CommandFromPython == 'U'){
        //ServoYMovement(CommandFromPython);
        //FindSonarDistance();
        digitalWrite(LaserPin,HIGH);
        //ReceiveData();
      }
      if(CommandFromPython == 'L' || CommandFromPython == 'R'){
        StepXMovement(CommandFromPython);
        //FindSonarDistance();
        digitalWrite(LaserPin,LOW);
        //ReceiveData(); 
      }
      if(CommandFromPython == 'N'){  // Cisim YOKSA                 
        //StepTurningAlways();
        //SonarDistanceinMeter = 2;
        digitalWrite(LaserPin,LOW); 
      }
  }
  }
