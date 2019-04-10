
#include <OneWire.h>
//
// 1-wire stuff
//

OneWire  ds(2);     // pin 7

byte i;
byte present = 0;
byte type_s;
byte data[12];
byte addr[4][8];     // enough room for 4 sensors
byte numFound;
byte addrSub;
float celsius, fahrenheit;

void setup() {
  Serial.begin(115200);
// Search for 1-wire devices

 numFound = 0;

 for(addrSub = 0; addrSub < 4; addrSub++){
   Serial.println(millis());
   if ( ds.search(addr[addrSub])) {
     Serial.println(millis());
     numFound++;
     Serial.print("Found: ");
     Serial.println(addrSub);
     Serial.print(" ROM =");
     for( i = 0; i < 8; i++) {
       Serial.write(' ');
       Serial.print(addr[addrSub][i], HEX);
     }
     if (OneWire::crc8(addr[addrSub], 7) != addr[addrSub][7]) {
       Serial.println("CRC is not valid!");
       return;
     }
     Serial.println();

   } else {
     Serial.println("No more found");
     break;
   }
 }
}

void loop() {
   dumpTemps();
   delay(10000);
}

void dumpTemps(){

 if(!numFound)
   return;
 ds.reset();
   
 ds.write(0xCC);             // Skip ROM
 ds.write(0x44, 0);          // start conversion, with parasite power off at the end
 
 delay(750);     // maybe 750ms is enough, maybe not

 
 for(addrSub = 0; addrSub < numFound; addrSub++) {

   // the first ROM byte indicates which chip
   Serial.print("\n  Sensor: ");
   Serial.println( addrSub );

   switch (addr[addrSub][0]) {
     case 0x10:
       Serial.println("  Chip = DS18S20");  // or old DS1820
       type_s = 1;
       break;

     case 0x28:
       Serial.println("  Chip = DS18B20");
       type_s = 0;
       break;

     case 0x22:
       Serial.println("  Chip = DS1822");
       type_s = 0;
       break;

     default:
       Serial.println("Device is not a DS18x20 family device.");
       return;
   }
   
  // we might do a ds.depower() here, but the reset will take care of it.
 
   present = ds.reset();          // Reset the bus

   ds.select(addr[addrSub]);      // do a match ROM

   ds.write(0xBE);                // Read Scratchpad

   Serial.print("  Data = ");
   Serial.print(present, HEX);

   Serial.print(" ");
   for ( i = 0; i < 9; i++) {           // we need 9 bytes
     data[i] = ds.read();
     Serial.print(data[i], HEX);
     Serial.print(" ");
   }
   
   Serial.print(" CRC=");
   Serial.print(OneWire::crc8(data, 8), HEX);
   Serial.println();

   // convert the data to actual temperature

   unsigned int raw = (data[1] << 8) | data[0];
   if (type_s) {
     raw = raw << 3; // 9 bit resolution default
     if (data[7] == 0x10) {
       // count remain gives full 12 bit resolution
       raw = (raw & 0xFFF0) + 12 - data[6];
     }
   } else {
     byte cfg = (data[4] & 0x60);
     if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
     else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
     else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
     // default is 12 bit resolution, 750 ms conversion time
   }

   celsius = (float)raw / 16.0;
   fahrenheit = celsius * 1.8 + 32.0;

   Serial.print("  Temperature = ");

   Serial.print(celsius);
   Serial.print(" Celsius, ");

   Serial.print(fahrenheit);
   Serial.println(" Fahrenheit");
 }
}
