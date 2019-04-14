#ifndef GLOBAL_H
#define GLOBAL_H

ESP8266WebServer server(80);									// The Webserver
ESP8266HTTPUpdateServer httpUpdater;
boolean firstStart = true;										// On firststart = true, NTP will try to get a valid time
int AdminTimeOutCounter = 0;									// Counter for Disabling the AdminMode
strDateTime DateTime;											// Global DateTime structure, will be refreshed every Second
WiFiUDP UDPNTPClient;											// NTP Client
unsigned long UnixTimestamp = 0;								// GLOBALTIME  ( Will be set by NTP)
boolean Refresh = false; // For Main Loop, to refresh things like GPIO / WS2812
int cNTP_Update = 0;											// Counter for Updating the time via NTP
Ticker tkSecond;												// Second - Timer for Updating Datetime Structure
boolean AdminEnabled = true;		// Enable Admin Mode for a given Time
byte Minute_Old = 100;				// Helpvariable for checking, when a new Minute comes up (for Auto Turn On / Off)

// Generally, you should use "unsigned long" for variables that hold time to handle rollover
unsigned long previousMillis = 0;        // will store last temp was read
unsigned long previousMillis1 = 0;       // will store last temp was read, emoncms write data
 long interval = 20000;              // interval at which to read sensor


struct strConfig {
	String ssid;
	String password;
  byte  IP[4];
  byte  DNS[4];
	byte  Netmask[4];
	byte  Gateway[4];
	boolean dhcp;
	String ntpServerName;
	long Update_Time_Via_NTP_Every;
	long timezone;
	boolean daylight;
	String DeviceName;
	boolean AutoTurnOff;
	boolean AutoTurnOn;
	byte TurnOffHour;
	byte TurnOffMinute;
	byte TurnOnHour;
	byte TurnOnMinute;
	byte LED_R;
	byte LED_G;
	byte LED_B;
 int skirtumason;
 int skirtumasoff;
 long intervalas;
 boolean apsauga;
  String emoncmsSrv;
  String apikey;
  String reiksme1;
  String reiksme2;
  String reiksme3;
  String katalogas;
  long intervalasEmon;
  boolean emoncmsOn;
  byte Kid;
  byte Bid;
  byte Oid;
}   config;

/*
**
********* temperatūros jutikliai ds18b20 **************
**
*/

//------------------------------------------
//DS18B20
#define ONE_WIRE_BUS D4 //Pin to which is attached a temperature sensor
#define ONE_WIRE_MAX_DEV 15 //The maximum number of devices

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
int numberOfDevices; //Number of temperature devices found
DeviceAddress devAddr[ONE_WIRE_MAX_DEV];  //An array device temperature sensors
float tempDev[ONE_WIRE_MAX_DEV]; //Saving the last measurement of temperature
float tempDevLast[ONE_WIRE_MAX_DEV]; //Previous temperature measurement
long lastTemp; //The last measurement
const int durationTemp = 5000; //The frequency of temperature measurement


//** Data wire is plugged into port D2 on the ESP8266
// #define ONE_WIRE_BUS D4
//** Setup a oneWire instance to communicate with any OneWire devices
// OneWire oneWire(ONE_WIRE_BUS);
//** Pass our oneWire reference to Dallas Temperature.
// DallasTemperature sensors(&oneWire);
float Kolektorius, Boileris, Oras;
float KolektoriusOld= 0;
float BoilerisOld= 0;
float OrasOld= 0;

#define REQUEST_freezing 5000   // 5000 millis= 5 sekundės
static long timer_freezing=0;   // apsaugos nuo užšalimo tikrinimo laikas


uint8_t kolektorius[8] = { 0x28, 0xd7, 0x3d, 0xdd, 0x03, 0x00, 0x00, 0x4f  };
DeviceAddress Kolektorius_Adr = { 0x28, 0xFF, 0x6C, 0x2E, 0x77, 0x04, 0x00, 0xB3 };// test adr
// 0x28, 0xd7, 0x3d, 0xdd, 0x03, 0x00, 0x00, 0x4f
uint8_t boileris[8] = { 0x28, 0x22, 0x08, 0xcc, 0x04, 0x00, 0x00, 0x4d  };
// 0x28, 0x22, 0x08, 0xcc, 0x04, 0x00, 0x00, 0x4d
uint8_t oras[8] = { 0x28, 0xaa, 0x48, 0x97, 0x03, 0x00, 0x00, 0xd9  };
// 0x28, 0xaa, 0x48, 0x97, 0x03, 0x00, 0x00, 0xd9  
#define RELAYPIN D7  // D4
String relayState = "OFF";


/*
**
** emoncms duomenų siuntimas
**
*/
// viskas konvigūruojama naršyklę!
//
//const char* emoncmshost = "xxx"; //Enter the EmonCMS Server address here
//const char* apikey = "xxx"; //Enter api key here

/*
**
** CONFIGURATION HANDLING
**
*/
void ConfigureWifi()
{
	Serial.println("Configuring Wifi");
	WiFi.begin (config.ssid.c_str(), config.password.c_str());
  WiFi.hostname("SauleVire");
	if (!config.dhcp)
	{
		WiFi.config(IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] ),  IPAddress(config.DNS[0],config.DNS[1],config.DNS[2],config.DNS[3] ),  IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] ) , IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] ));

  Serial.println("IP adresas: " + WiFi.localIP().toString()+ "\n");
  Serial.print("SSID'as: " + config.ssid+ "\n");
  Serial.print("Slaptažodis: " + config.password+ "\n\n");
	}
}

void WriteConfig()
{

	Serial.println("Writing Config");
	EEPROM.write(0,'C');
	EEPROM.write(1,'F');
	EEPROM.write(2,'G');

  EEPROM.write(11,config.Kid);
  EEPROM.write(12,config.Bid);
  EEPROM.write(13,config.Oid);
  EEPROM.write(14,config.emoncmsOn);
  EEPROM.write(15,config.apsauga);
  EEPROM.write(16,config.dhcp);
	EEPROM.write(17,config.daylight);
	
	EEPROMWritelong(18,config.Update_Time_Via_NTP_Every); // 4 Byte
	EEPROMWritelong(22,config.timezone);  // 4 Byte

	EEPROM.write(26,config.LED_R);
	EEPROM.write(27,config.LED_G);
	EEPROM.write(28,config.LED_B);

  EEPROM.write(32,config.IP[0]);
  EEPROM.write(33,config.IP[1]);
  EEPROM.write(34,config.IP[2]);
  EEPROM.write(35,config.IP[3]);

  EEPROM.write(36,config.DNS[0]);
  EEPROM.write(37,config.DNS[1]);
  EEPROM.write(33,config.DNS[2]);
  EEPROM.write(39,config.DNS[3]);

	EEPROM.write(40,config.Netmask[0]);
	EEPROM.write(41,config.Netmask[1]);
	EEPROM.write(42,config.Netmask[2]);
	EEPROM.write(43,config.Netmask[3]);

	EEPROM.write(44,config.Gateway[0]);
	EEPROM.write(44,config.Gateway[1]);
	EEPROM.write(46,config.Gateway[2]);
  EEPROM.write(47,config.Gateway[3]);
  EEPROM.write(48,config.intervalas); //4 bitai
  EEPROM.write(52,config.intervalasEmon); //4 bitai

	WriteStringToEEPROM(64,config.ssid);
	WriteStringToEEPROM(96,config.password);
	WriteStringToEEPROM(128,config.ntpServerName);

  EEPROM.write(298,config.skirtumason);
  EEPROM.write(299,config.skirtumasoff);
  EEPROM.write(300,config.AutoTurnOn);
	EEPROM.write(301,config.AutoTurnOff);
	EEPROM.write(302,config.TurnOnHour);
	EEPROM.write(303,config.TurnOnMinute);
	EEPROM.write(304,config.TurnOffHour);
	EEPROM.write(305,config.TurnOffMinute);
	WriteStringToEEPROM(306,config.DeviceName);

  WriteStringToEEPROM(321,config.reiksme1);
  WriteStringToEEPROM(328,config.reiksme2);
  WriteStringToEEPROM(335,config.reiksme3);
  WriteStringToEEPROM(342,config.katalogas);
  WriteStringToEEPROM(350,config.apikey);
  WriteStringToEEPROM(366,config.emoncmsSrv); //laisva nuo 388


	


	EEPROM.commit();
}
boolean ReadConfig()
{

	Serial.println("Reading Configuration");
	if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
	{
		Serial.println("Configurarion Found!");
    config.Kid =   EEPROM.read(11);
    config.Bid =   EEPROM.read(12);
    config.Oid =   EEPROM.read(13);
    config.emoncmsOn =   EEPROM.read(14);
    config.apsauga =   EEPROM.read(15);
		config.dhcp = 	EEPROM.read(16);

		config.daylight = EEPROM.read(17);
		config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
		config.timezone = EEPROMReadlong(22); // 4 Byte

		config.LED_R = EEPROM.read(26);
		config.LED_G = EEPROM.read(27);
		config.LED_B = EEPROM.read(28);

    config.IP[0] = EEPROM.read(32);
    config.IP[1] = EEPROM.read(33);
    config.IP[2] = EEPROM.read(34);
    config.IP[3] = EEPROM.read(35);
    config.DNS[0] = EEPROM.read(36);
    config.DNS[1] = EEPROM.read(37);
    config.DNS[2] = EEPROM.read(38);
    config.DNS[3] = EEPROM.read(39);
		config.Netmask[0] = EEPROM.read(40);
		config.Netmask[1] = EEPROM.read(41);
		config.Netmask[2] = EEPROM.read(42);
		config.Netmask[3] = EEPROM.read(43);
		config.Gateway[0] = EEPROM.read(44);
		config.Gateway[1] = EEPROM.read(45);
		config.Gateway[2] = EEPROM.read(46);
    config.Gateway[3] = EEPROM.read(47);
    config.intervalas = EEPROM.read(48);
    config.intervalasEmon = EEPROM.read(52);
    //laisva nuo 56 adreso
		config.ssid = ReadStringFromEEPROM(64);
		config.password = ReadStringFromEEPROM(96);
		config.ntpServerName = ReadStringFromEEPROM(128);
		
    config.skirtumason = EEPROM.read(298);
    config.skirtumasoff = EEPROM.read(299);
		config.AutoTurnOn = EEPROM.read(300);
		config.AutoTurnOff = EEPROM.read(301);
		config.TurnOnHour = EEPROM.read(302);
		config.TurnOnMinute = EEPROM.read(303);
		config.TurnOffHour = EEPROM.read(304);
		config.TurnOffMinute = EEPROM.read(305);
    config.DeviceName= ReadStringFromEEPROM(306);
    
    config.reiksme1= ReadStringFromEEPROM(321);
    config.reiksme2= ReadStringFromEEPROM(328);
    config.reiksme3= ReadStringFromEEPROM(335);
    config.katalogas= ReadStringFromEEPROM(342);
    config.apikey= ReadStringFromEEPROM(350);
    config.emoncmsSrv= ReadStringFromEEPROM(366);
		return true;
		
	}
	else
	{
		Serial.println("Configurarion NOT FOUND!!!!");
		return false;
	}
}
/*
**
**  NTP 
**
*/
//const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[ NTP_PACKET_SIZE]; 
void NTPRefresh()
{

	if (WiFi.status() == WL_CONNECTED)
	{
		IPAddress timeServerIP; 
		WiFi.hostByName(config.ntpServerName.c_str(), timeServerIP); 
		//sendNTPpacket(timeServerIP); // send an NTP packet to a time server


		Serial.println("sending NTP packet...");
		memset(packetBuffer, 0, NTP_PACKET_SIZE);
		packetBuffer[0] = 0b11100011;   // LI, Version, Mode
		packetBuffer[1] = 0;     // Stratum, or type of clock
		packetBuffer[2] = 6;     // Polling Interval
		packetBuffer[3] = 0xEC;  // Peer Clock Precision
		packetBuffer[12]  = 49;
		packetBuffer[13]  = 0x4E;
		packetBuffer[14]  = 49;
		packetBuffer[15]  = 52;
		UDPNTPClient.beginPacket(timeServerIP, 123); 
		UDPNTPClient.write(packetBuffer, NTP_PACKET_SIZE);
		UDPNTPClient.endPacket();


		delay(1000);
  
		int cb = UDPNTPClient.parsePacket();
		if (!cb) {
			Serial.println("NTP no packet yet");
		}
		else 
		{
			Serial.print("NTP packet received, length=");
			Serial.println(cb);
			UDPNTPClient.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
			unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
			unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
			unsigned long secsSince1900 = highWord << 16 | lowWord;
			const unsigned long seventyYears = 2208988800UL;
			unsigned long epoch = secsSince1900 - seventyYears;
			UnixTimestamp = epoch;
		}
	}
}

void Second_Tick()
{
	strDateTime tempDateTime;
	AdminTimeOutCounter++;
	cNTP_Update++;
	UnixTimestamp++;
	ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) , &tempDateTime);
	if (config.daylight) // Sommerzeit beachten
		if (summertime(tempDateTime.year,tempDateTime.month,tempDateTime.day,tempDateTime.hour,0))
		{
			ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) + 3600, &DateTime);
		}
		else
		{
			DateTime = tempDateTime;
		}
	else
	{
			DateTime = tempDateTime;
	}
	Refresh = true;
}
 

#endif
