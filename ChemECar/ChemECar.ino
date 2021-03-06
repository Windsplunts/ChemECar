// ChemE Car Sketch
// Runs in a standby loop waiting for a serial connection. Once recieved, 
// goes into a transmission and measurement loop. 

int measurement;
long rotaryTicks;
boolean constantLoop;
long timeRunning = 0;
long timeStart = 0;
long distancePassed = 0;


void rotaryInterrupt(){
  rotaryTicks++;
}

void timerStart(){
  if( (millis() - timeStart) > 400){
    constantLoop = !constantLoop;
    timeStart = millis();
    distancePassed = rotaryTicks;
  }

}
    
void timerStop(){
    constantLoop = false;
    // Not sure what to do here yet
    
}

void sendMeasurement(){
  if((millis() - timeStart) > 100){
      Serial1.print(millis() - timeStart);
      Serial1.print(',');
      Serial1.print(rotaryTicks);
      Serial1.print(',');
      Serial1.print(distancePassed);
      Serial1.print(',');
      Serial1.print('\n');
  }
}


void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Stuff");
  attachInterrupt(1, timerStart, CHANGE);
}

void loop(){
  if(Serial1.available() > 0){
    char recieved = Serial1.read();
    switch(recieved){
      
      case 'G':
      // Fall through
      case 'g':
        constantLoop = true;
        attachInterrupt(0, rotaryInterrupt, CHANGE);
        Serial.println("Attached Interrupt");
        break;
      
      case 'S':
      // Fall through
      case 's':
        constantLoop = false;
        Serial.println("Detached Interrupt");
        detachInterrupt(0);
        break;
    }
  }
  
  
  // Measurement Loop
  if(constantLoop){
    sendMeasurement();
  }
}


