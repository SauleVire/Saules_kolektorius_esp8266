/* 
  ESP_WebConfig 
  Latest version: 1.1.3  - 2015-07-20
  Changed the loading of the Javascript and CCS Files, so that they will successively loaded and that only one request goes to the ESP.
  -----------------------------------------------------------------------------------------------
   */
#define Diagnostika 1 // Naudojama tik testavimui
#define ACCESS_POINT_NAME  "SauleVire_Ap"        
#define ACCESS_POINT_PASSWORD  "" 
#define AdminTimeOut 300  // Defines the Time in Seconds, when the Admin-Mode will be disabled

//#if defined(ESP8266)
#include <ESP8266WiFi.h>          
//#else
//#include <WiFi.h>          
//#endif
#include <NtpClientLib.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Ticker.h>
//#include <EEPROM.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>
#include <ESP_EEPROM.h>

#include "helpers.h"
#include "global.h"
#include "ds18b20.h"

/*
Include the HTML, STYLE and Script "Pages"
*/
#include "Page_Root.h"
#include "Page_Admin.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_NTPsettings.h"
#include "Page_Information.h"
//#include "Page_General.h"
#include "PAGE_NetworkConfiguration.h"
#include "Page_NotFound.h"
#include "Page_Kolektorius.h"
#include "Page_Emoncms.h"
#include "Page_Index.h"
#include "Page_DS18B20.h"
#include "Page_RastiDS18B20.h"

//SimpleTimer timer;
const char* host = "SauleVire1";


void setup ( void ) 
{
	EEPROM.begin(512);
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, LOW);
#ifdef Diagnostika
	Serial.begin(115200);
	Serial.println("Čia SauleVire.lt pradžia\n");
#endif
	if (!ReadConfig())
	{
		// DEFAULT CONFIG
		config.ssid = "SauleVire"; //belaidžio tinklo pavadinimas
		config.password = "SauleVire.lt"; //belaidžio tinklo slaptažodis
		config.dhcp = true;
    config.IP[0] = 192;config.IP[1] = 168;config.IP[2] = 2;config.IP[3] = 113;
    config.DNS[0] = 192;config.DNS[1] = 168;config.DNS[2] = 2;config.DNS[3] = 1;
		config.Netmask[0] = 255;config.Netmask[1] = 255;config.Netmask[2] = 255;config.Netmask[3] = 0;
		config.Gateway[0] = 192;config.Gateway[1] = 168;config.Gateway[2] = 2;config.Gateway[3] = 1;
		config.ntpServerName = "lt.pool.ntp.org";
		config.Update_Time_Via_NTP_Every =  30;
		config.timezone = +2;
		config.daylight = true;
		config.DeviceName = "SauleVire2";
		config.AutoTurnOff = false;
		config.AutoTurnOn = false;
		config.TurnOffHour = 0;
		config.TurnOffMinute = 0;
		config.TurnOnHour = 0;
		config.TurnOnMinute = 0;
/* ********** kintamieji saulės kolektoriui ******************* */
    config.k_skirtumas = 4;
    config.k_uzsalimas = true; // 1-įjungta, 0- išjungta , SK apsauga nuo šalčio, pašildymas
    config.k_nuorinimas = false; //  SK siurblio rankiniam valdymui (nuorinimas)
    config.k_intervalas = 5; // Numatytas laikas saulės kolektoriaus temperatūros matavimui 10s.

    config.reiksme1 = "a";
    config.reiksme2 = "b";
    config.reiksme3 = "c";
    config.katalogas = "d";
    config.emoncmsOn = false;
/* ********** kintamieji Boileriui ******************* */
    config.b_ON_T = 45; // temperatūra boilerio siurbliui įjungti
    config.b_OFF_T = 65; // temperatūra boilerio siurbliui įšjungti
    config.Bo_Rankinis_ijungimas = false; // Žymė rankiniam AT siurblio valdymui
    config.Bo_Termostatas_ON = false; // Žymė rankiniam termostato įjungimui
    config.Bo_Termostato_busena = false; // Žymė termostato busenai
/* ********** kintamieji Akumuliacinei talpai ******************* */
    config.at_ON_T = 90; // temperatūra akumuliacines talpos siurbliui įjungti
    config.at_OFF_T = 89; // temperatūra akumuliacines talpos siurbliui įšjungti
    config.At_Rankinis_ijungimas = 0; // Žymė rankiniam AT siurblio valdymui
/* ********** PID nustatymai ************************************ */    
    config.Kp = 25;
    config.Ki = 1.5;
    config.Kd = 4;
    config.WindowSize = 160;
		WriteConfig();
#ifdef Diagnostika    
		Serial.println("General config applied");
#endif   
	}
	
	
	if (AdminEnabled)
	{ 
    // AdminModeTicker.attach(0.3, tick);
		WiFi.mode(WIFI_AP_STA);
		WiFi.softAP( ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);
    Serial.print("SauleVire AP IP addresas: "); Serial.println(WiFi.softAPIP());
	}
	else
	{
		WiFi.mode(WIFI_STA);
    Serial.print("Valdiklio IP addresas:");Serial.println(WiFi.localIP());
	}

	ConfigureWifi();
	

	server.on ( "/", processIndex  );
	server.on ( "/admin/filldynamicdata", filldynamicdata );
	server.on ( "/favicon.ico",   []() { 
#ifdef Diagnostika	  
	  Serial.println("favicon.ico"); 
#endif   
	  server.send ( 200, "text/html", "" );   }  );
	server.on ( "/admin.html", []() {
#ifdef Diagnostika   
	  Serial.println("admin.html"); 
#endif 
	  server.send ( 200, "text/html", PAGE_AdminMainPage );   }  );
	server.on ( "/config.html", send_network_configuration_html );
  server.on ( "/info.html", []() { 
#ifdef Diagnostika   
  Serial.println("info.html"); 
#endif  
  server.send ( 200, "text/html", PAGE_Information );   }  );
	server.on ( "/ntp.html", send_NTP_configuration_html  );
//	server.on ( "/general.html", send_general_html  );
  server.on ( "/example.html", []() {
#ifdef Diagnostika    
    Serial.println("example.html"); 
#endif
    server.send ( 200, "text/html", PAGE_EXAMPLE );  } );
  server.on ( "/kolektorius.html", send_KolektoriausKonfiguracija_html ); 
  server.on ( "/emoncms.html", send_Emoncms_html ); 
  server.on ( "/ds18b20.html", Page_DS18B20 ); 
  server.on ( "/rastids18b20.html", send_RastiDS18B20_html );
  server.on("/naujinimas.html", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
//      server.send(200, "text/html", naujinimas);
    });

    server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        WiFiUDP::stopAll();
        Serial.printf("Update: %s\n", upload.filename.c_str());
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if (!Update.begin(maxSketchSpace)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      yield();
    });

    
  server.on ( "/style.css", []() { 
#ifdef Diagnostika
    Serial.println("style.css"); 
#endif
    server.send ( 200, "text/plain", PAGE_Style_css );  } );
	server.on ( "/microajax.js", []() { 
#ifdef Diagnostika
	  Serial.println("microajax.js"); 
#endif
	  server.send ( 200, "text/plain", PAGE_microajax_js );  } );
	server.on ( "/admin/values", send_network_configuration_values_html );
	server.on ( "/admin/connectionstate", send_connection_state_values_html );
	server.on ( "/admin/infovalues", send_information_values_html );
  server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
  server.on ( "/admin/kolektoriusvalues", send_KolektoriausKonfiguracija_values_html );
  server.on ( "/admin/emoncmsvalues", send_Emoncms_values_html );
  server.on ( "/admin/rastids18b20values", send_RastiDS18B20_values_html );
//	server.on ( "/admin/generalvalues", send_general_configuration_values_html);
//	server.on ( "/admin/devicename", send_devicename_value_html);
  
	server.onNotFound ( []() { 
#ifdef Diagnostika
	  Serial.println("Page Not Found"); 
#endif
	  server.send ( 200, "text/html", PAGE_NotFound );   
	  }  );
	httpUpdater.setup(&server);
  server.begin();

  MDNS.begin(host);
//  MDNS.addService("http", "tcp", 80);
#ifdef Diagnostika
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
#endif

	tkSecond.attach(1,Second_Tick);
	UDPNTPClient.begin(2390);  // Port for NTP receivetick

//  Setup DS18b20 temperature sensor

  SetupDS18B20();
Setpoint = Boileris + config.k_skirtumas;
  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, config.WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
//  timer.setInterval(15000L, KolektoriusT);

  pinMode(RELAYPIN,OUTPUT);

}

 
void loop ( void ) 
{
//  digitalWrite(2, HIGH);
	if (AdminEnabled) 
	{
		if (AdminTimeOutCounter > AdminTimeOut) 
		{
			 AdminEnabled = false;
       // AdminModeTicker.detach();
			 Serial.println("\n\nAdmin Mode disabled!\n\n");
       WiFi.mode(WIFI_STA);
       Serial.println(WiFi.localIP());

		 }
  }
	if (config.Update_Time_Via_NTP_Every  > 0 ) 
	{
		if (cNTP_Update > 5 && firstStart)
		{
      NTPRefresh();
			cNTP_Update =0;
			firstStart = false;
		}
		else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
		{	
		  NTPRefresh();
			cNTP_Update =0;
		}
	}
	if(DateTime.minute != Minute_Old)
	{	 
	  Minute_Old = DateTime.minute;
		 if (config.AutoTurnOn)
		 { 
		  if (DateTime.hour == config.TurnOnHour && DateTime.minute == config.TurnOnMinute)
			{ 
			  Serial.println("SwitchON"); Laikmatis = true;
			  }
		 }
		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOff)
		 { 
		  if (DateTime.hour == config.TurnOffHour && DateTime.minute == config.TurnOffMinute)
			{
			  Serial.println("SwitchOff"); Laikmatis = false;
			  }
		 }
	}
	server.handleClient();
///////////// *   START Your Code here    * //////////////////////
/****************************************************************/


// Taimeris nustato laiko intervalus temperatūrų matavimui
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();

// tikrinama ar matavimo intervalas ne mažesnis negu 3 sekundės.
  if (config.k_intervalas < 3 ) config.k_intervalas = 3;
// tikrinama ar jau laikas matuoti temperatūrą
  if ((unsigned long)(currentMillis - previousMillis) >= config.k_intervalas * 1000)
  { // įsimenamas paskutinio matavimo laikas
    previousMillis = currentMillis;

    TemteraturosMatavimas();
// Jei įjungtas nuorinimo režimas arba apsauga nuo užšalimo ir kolektoriaus temperatūra artėja prie 0, įjungiamas siurblys
    if (config.k_nuorinimas == 1 or ((Kolektorius < 0.68) & (config.k_uzsalimas == 1)))
          { digitalWrite(RELAYPIN, HIGH); relayState = "ON(užšalimas)";
       Serial.print("\nSiurblio rele įjungta ON (Nuorinimas, užšalimas)\n");
       } else {Siurblys();
//Jei laikas sutampa su laiku, kai kolektoriaus šiluma niekinė, siurblys išjungiamas
//        if (DateTime.hour == config.TurnOffHour or DateTime.hour == config.TurnOffHour +1 )
//          { digitalWrite(RELAYPIN, LOW); relayState = "OFF(laikas)";
//       Serial.print("\nSiurblio rele įjungta OFF (nurodytas išjungimo laikas)\n");
//       } else {Siurblys();}
       }
    
}
/* ****************************** emoncms ****************************** */
// tikrinama ar siuntimo intervalas ne mažesnis negu 5 sekundės.
if (config.intervalasEmon < 5 ) config.k_intervalas = 5;
//ar aktyvuotas duomenų siuntimas į emoncms ir jau galima siųsti duomenis
    if ((config.emoncmsOn  == 1) & ((unsigned long)(currentMillis1 - previousMillis1) >= config.intervalasEmon * 1000)) 
    {
      // įsimenamas paskutinio matavimo laikas
      previousMillis1 = currentMillis1;
      emoncms();
    }
#ifdef Diagnostika
// tikrinama ar jau laikas matuoti temperatūrą
  if (millis() - previousMillis2 >= 10000)
  { // įsimenamas paskutinio matavimo laikas
    previousMillis2 = millis();
    Serial.print("\nAdminTimeOutCounter- ");Serial.print(AdminTimeOutCounter);
    Serial.print("\nemoncmsOn - "); Serial.print(config.emoncmsOn);
    Serial.print(", k_uzsalimas - "); Serial.print(config.k_uzsalimas);
    Serial.print("\nK- "); Serial.print(Kolektorius);
    Serial.print(", B- "); Serial.print(Boileris);
    Serial.print(", O- "); Serial.print(Oras);
    Serial.printf("\nFreeMem: %d \nDabar- %d:%d:%d %d.%d.%d \n",ESP.getFreeHeap(), DateTime.year, DateTime.month, DateTime.day, DateTime.hour, DateTime.minute, DateTime.second);
  }
#endif
//  if (WiFi.mode(WIFI_STA))
//    machineIOs.SetLeds(noChange, noChange, (((millis() / 125) & 7) == 0) ? On : Off); // 1 Hz blink with 12.5% duty cycle
//  else
//    machineIOs.SetLeds(noChange, noChange, (((millis() / 125) & 7) != 0) ? On : Off); // 1 Hz blink with 87.5% duty cycle
//  machine.ModulateSound(((millis() / 63) & 7) == 0); // 2 Hz blink with 12.5% duty cycle (1.984... Hz)
/****************************************************************/

  MDNS.update();
//  timer.run();
///////////// *    Your Code here END   * //////////////////////
	
	if (Refresh)  
	{	Refresh = false;
//		Serial.println("Refreshing...");
//		Serial.printf("FreeMem:%d %d:%d:%d %d.%d.%d \n",ESP.getFreeHeap() , DateTime.hour,DateTime.minute, DateTime.second, DateTime.year, DateTime.month, DateTime.day);
	}
}
