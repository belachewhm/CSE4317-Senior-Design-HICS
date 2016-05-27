
// initiate the sate
int ledPin=13;
int off=LOW;
int on=HIGH;
int val[32];
int command;
char inByte;
boolean state[54];
float sensor[26];
int i;
void setup() {
  // set baudrate
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
 
  for(int i=22; i<=38; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);
    val[i]=i;
  }
  
}

// main loop
void loop() {
  // read signal on analog input :
  
  
  int rainSensorValue = analogRead(A0);
  int tempSensorValue = analogRead(A1);
  int soilSensorValue1 = analogRead(A2);
  int soilSensorValue2 = analogRead(A3);
  int soilSensorValue3 = analogRead(A4);
  // convert signal int to value:
  float soil_voltage1 = 5.0 - soilSensorValue1 * (5.0 / 1023.0);
  float soil_voltage2 = 5.0 - soilSensorValue2 * (5.0 / 1023.0);
  float soil_voltage3 = 5.0 - soilSensorValue3 * (5.0 / 1023.0);
  float temperature = 32+(9/5)*100.0*tempSensorValue* (5.0 / 1024.0);
  float rain_voltage = 5.0 - rainSensorValue* (5.0 / 1023.0);;
  
  sensor[0]=rain_voltage;
  sensor[1]=temperature;
  sensor[2]=soil_voltage1;
  sensor[3]=soil_voltage2;
  sensor[4]=soil_voltage3;
  
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();

    command=int(inByte);
        
    if ((command>21)&&(command!=83)){

     int pin;
     pin =command-48+22;
      digitalWrite(pin, (state[pin]) ? HIGH : LOW);
      state[pin] = !state[pin];
     delay(100);
     // Serial.print(command);
     //sendSensorValue();
     }
     if (command==83){
       sendSensorValue();
     }
     if (command==88){
       turnoffallValves();
     }
    Serial.flush();  
    }
    
}

void parseCommand(String com){

}

void turnoffallValves(){
   for(int i=22; i<=38; i++)
  {
   
    digitalWrite(i,HIGH);
    val[i]=i;
  }
}
void sendSensorValue(){
 
  
  for (int i=0;i<25;i++){
    Serial.print(sensor[i]);
    Serial.print(":");
  }
    Serial.print(sensor[25]);
}
