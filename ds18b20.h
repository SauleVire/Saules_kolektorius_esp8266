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
  Kolektorius = DS18B20.getTempC(kolektorius);
  Boileris = DS18B20.getTempC(boileris);
  Oras = DS18B20.getTempC(oras);
  // Check if any reads failed and exit
  if (Kolektorius == -127 or Kolektorius == 85 or Kolektorius > 127 ) {
    Kolektorius = KolektoriusOld;
    Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  }
    else { KolektoriusOld = Kolektorius;}

  if (Boileris == -127 or Boileris == 85 or Boileris > 127 ) {
    Boileris = BoilerisOld;
    Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  }
    else { BoilerisOld = Boileris;}

  if (Oras == -127 or Oras == 85 or Oras > 127 ) {
    Oras = OrasOld;
    Serial.println("Klaida! Ds18B20 rodmenys neteisingi");  }
    else { OrasOld = Oras;}
}
void Siurblys(){
  // Relė įjungiama arba išjungiama priklausomai nuo temperatūrų
  if (Kolektorius > Boileris + config.skirtumason)
      { digitalWrite(RELAYPIN, LOW); 
      relayState = "Įjungtas";
      Serial.print("\nSiurblio rele įjungta ON\n");
      }
  else if ((Kolektorius < Boileris + config.skirtumasoff) & (Kolektorius > 0.45))
      { digitalWrite(RELAYPIN, HIGH); 
      relayState = "Išjungtas";
      Serial.print("\nSiurblio rele įšungta OFF\n");
      }
DS18B20.requestTemperatures();
}



      
  // Tikrinama ar įjungta ir reikalinga apsauga nuo užšalimo
void Apsauga(long now){
  //Take a measurement at a fixed time (durationTemp = 5000ms, 5s)
  if( now - timer_freezing > REQUEST_freezing ){ 
      if ((Kolektorius < 0.33) & (config.apsauga == 1)) {
        digitalWrite(RELAYPIN, LOW); }
    timer_freezing = millis();  //Remember the last time measurement
  }
}

/////////////////////////////////////////////////
