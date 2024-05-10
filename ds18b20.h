//------------------------------------------
//Convert device id to String
String GetAddressToString(DeviceAddress deviceAddress){
  String str = "";
  for (uint8_t i = 0; i < 8; i++){
    if( deviceAddress[i] < 16 ) str += String(0, HEX);
    str += String(deviceAddress[i], HEX);
  }
  return str;
}

//Loop measuring the temperature
void TempLoop(long now){
  if( now - lastTemp > durationTemp ){ //Take a measurement at a fixed time (durationTemp = 5000ms, 5s)
    for(int i=0; i<numberOfDevices; i++){
      float tempC = DS18B20.getTempC( devAddr[i] ); //Measuring temperature in Celsius
      tempDev[i] = tempC; //Save the measured value to the array
    }
    DS18B20.setWaitForConversion(false); //No waiting for measurement
    DS18B20.requestTemperatures(); //Initiate the temperature measurement
    lastTemp = millis();  //Remember the last time measurement
  }
}
//Setting the temperature sensor
void SetupDS18B20(){
  DS18B20.begin();

  Serial.print("Parasite power is: "); 
  if( DS18B20.isParasitePowerMode() ){ 
    Serial.println("ON");
  }else{
    Serial.println("OFF");
  }
  
  numberOfDevices = DS18B20.getDeviceCount();
  Serial.print( "Device count: " );
  Serial.println( numberOfDevices );

  lastTemp = millis();
  DS18B20.requestTemperatures();

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if( DS18B20.getAddress(devAddr[i], i) ){
      //devAddr[i] = tempDeviceAddress;
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: " + GetAddressToString(devAddr[i]));
      Serial.println();
    }else{
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }

    //Get resolution of DS18b20
    Serial.print("Resolution: ");
    Serial.print(DS18B20.getResolution( devAddr[i] ));
    Serial.println();

    //Read temperature from DS18b20
    float tempC = DS18B20.getTempC( devAddr[i] );
    Serial.print("Temp C: ");
    Serial.println(tempC);
  }
}

// reads the temp and humidity from the DHT sensor and sets the global variables for both
void TemteraturosMatavimas() {
  Siltnamis = DS18B20.getTempC(devAddr[config.Sid]);
  Rusys = DS18B20.getTempC(devAddr[config.Rid]);
  Kolektorius = DS18B20.getTempC(devAddr[config.Kid]);
  Boileris = DS18B20.getTempC(devAddr[config.Bid]);
  Oras = DS18B20.getTempC(devAddr[config.Oid]);
//float OrasWU = DS18B20.getTempF(devAddr[config.Oid]);
  // Check if any reads failed and exit
  if (Kolektorius == -127 or Kolektorius == 85 or Kolektorius > 127 ) {
    Kolektorius = KolektoriusOld;
  #ifdef Diagnostika   
       Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  
  #endif 
         }
    else { KolektoriusOld = Kolektorius;}

  if (Boileris == -127 or Boileris == 85 or Boileris > 127 ) {
    Boileris = BoilerisOld;
  #ifdef Diagnostika   
       Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  
  #endif 
         }
    else { BoilerisOld = Boileris;}

  if (Oras == -127 or Oras == 85 or Oras > 127 ) {
    Oras = OrasOld;
  #ifdef Diagnostika   
       Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  
  #endif 
         }
    else { OrasOld = Oras;}
  DS18B20.requestTemperatures();
  
}
void Siurblys(){
  Input = Kolektorius;
  Setpoint = Boileris + config.k_skirtumas;
//   PID myPID(&Input, &Output, &Setpoint, config.Kp, config.Ki, config.Kd, DIRECT);   
//    myPID.SetOutputLimits(0, config.WindowSize);
     myPID.SetTunings(config.Kp, config.Ki, config.Kd); 
     myPID.Compute();  
       if (millis() - windowStartTime > WindowSize)
  {
    //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
#ifdef Diagnostika   
  Serial.print("\nInput: ");  Serial.print(Input);
  Serial.print("\nSetpoint: ");  Serial.print(Setpoint);
  Serial.print("\nOutput: ");  Serial.print(Output);
  Serial.print("\nconfig.Kp reikšmė: ");  Serial.print(config.Kp);
  Serial.print("\nwindowStartTime: ");  Serial.print(windowStartTime);
  Serial.print("\nmill-Wstart: ");  Serial.print((millis() - windowStartTime) / 1000);
  Serial.print("\nmilliseconds ("); Serial.print((Output * 100.0) / config.WindowSize, 0);  Serial.println("%)");
  #endif   
  if ((Output < (millis() - windowStartTime) / 1000) ) 
      { digitalWrite(RELAYPIN, HIGH); 
      relayState = "Įjungtas";
       Serial.print("\nSiurblio rele įjungta ON (Siurblio ciklas)\n");
      }
  else 
      { digitalWrite(RELAYPIN, LOW); 
      relayState = "Išjungtas";
      Serial.print("\nSiurblio rele išjungta OFF (Siurblio ciklas)\n");
      }
 
}

     
  // Tikrinama ar įjungta ir reikalinga k_uzsalimas nuo užšalimo
void k_uzsalimas(){
      if (((Kolektorius < 0.85) & (config.k_uzsalimas == 1)) or (config.k_nuorinimas == 1)) {
        digitalWrite(RELAYPIN, HIGH); 
        relayState = "Įjungtas";
        Serial.print("\nSiurblio rele įjungta ON (Apsaugos ciklas)\n");}

}
