/* 
  ESP_WebConfig 

  Copyright (c) 2015 John Lassen. All rights reserved.
  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Latest version: 1.1.3  - 2015-07-20
  Changed the loading of the Javascript and CCS Files, so that they will successively loaded and that only one request goes to the ESP.

  -----------------------------------------------------------------------------------------------
  History

  Version: 1.1.2  - 2015-07-17
  Added URLDECODE for some input-fields (SSID, PASSWORD...)

  Version  1.1.1 - 2015-07-12
  First initial version to the public
 
  */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Ticker.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "helpers.h"
#include "global.h"
#include "ds18b20.h"
#include <SimpleTimer.h>
/*
Include the HTML, STYLE and Script "Pages"
*/
#include "Page_Root.h"
#include "Page_Admin.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_NTPsettings.h"
#include "Page_Information.h"
#include "Page_General.h"
#include "PAGE_NetworkConfiguration.h"
#include "Page_NotFound.h"
#include "Page_Kolektorius.h"
#include "Page_Emoncms.h"
#include "Page_Index.h"
#include "Page_DS18B20.h"


#define ACCESS_POINT_NAME  "SauleVire_AP"				
#define ACCESS_POINT_PASSWORD  "" 
#define AdminTimeOut 100  // Defines the Time in Seconds, when the Admin-Mode will be disabled
SimpleTimer timer;
const char* host = "SauleVire";


void setup ( void ) {
	EEPROM.begin(512);
	Serial.begin(115200);
	Serial.println("Čia SauleVire.lt pradžia\n");
	if (!ReadConfig())
	{
		// DEFAULT CONFIG
		config.ssid = "SauleVire  "; //belaidžio tinklo pavadinimas
		config.password = "SauleVire"; //slaptažodis
		config.dhcp = true;
		config.IP[0] = 192;config.IP[1] = 168;config.IP[2] = 1;config.IP[3] = 165;
		config.Netmask[0] = 255;config.Netmask[1] = 255;config.Netmask[2] = 255;config.Netmask[3] = 0;
		config.Gateway[0] = 192;config.Gateway[1] = 168;config.Gateway[2] = 1;config.Gateway[3] = 1;
		config.ntpServerName = "lt.pool.ntp.org";
		config.Update_Time_Via_NTP_Every =  30;
		config.timezone = +2;
		config.daylight = true;
		config.DeviceName = "SauleVire.lt";
		config.AutoTurnOff = false;
		config.AutoTurnOn = false;
		config.TurnOffHour = 0;
		config.TurnOffMinute = 0;
		config.TurnOnHour = 0;
		config.TurnOnMinute = 0;
    config.skirtumason = 12;
    config.skirtumasoff = 7;
    config.intervalas = 10000;
    config.apsauga = true;
    config.reiksme1 = "a";
    config.reiksme2 = "b";
    config.reiksme3 = "c";
    config.katalogas = "d";
    config.emoncmsOn = true;
    
		WriteConfig();
		Serial.println("General config applied");
	}
	
	
	if (AdminEnabled)
	{
		WiFi.mode(WIFI_AP_STA);
		WiFi.softAP( ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);
	}
	else
	{
		WiFi.mode(WIFI_STA);
	}

	ConfigureWifi();
	

	server.on ( "/", processIndex  );
	server.on ( "/admin/filldynamicdata", filldynamicdata );
	server.on ( "/favicon.ico",   []() { Serial.println("favicon.ico"); server.send ( 200, "text/html", "" );   }  );
	server.on ( "/admin.html", []() { Serial.println("admin.html"); server.send ( 200, "text/html", PAGE_AdminMainPage );   }  );
	server.on ( "/config.html", send_network_configuration_html );
	server.on ( "/info.html", []() { Serial.println("info.html"); server.send ( 200, "text/html", PAGE_Information );   }  );
	server.on ( "/ntp.html", send_NTP_configuration_html  );
	server.on ( "/general.html", send_general_html  );
  server.on ( "/example.html", []() {Serial.println("example.html"); server.send ( 200, "text/html", PAGE_EXAMPLE );  } );
  server.on ( "/kolektorius.html", send_KolektoriausKonfiguracija_html ); 
  server.on ( "/emoncms.html", send_Emoncms_html ); 
  server.on ( "/ds18b20.html", Page_DS18B20 ); 
  server.on ( "/style.css", []() { Serial.println("style.css"); server.send ( 200, "text/plain", PAGE_Style_css );  } );
	server.on ( "/microajax.js", []() { Serial.println("microajax.js"); server.send ( 200, "text/plain", PAGE_microajax_js );  } );
	server.on ( "/admin/values", send_network_configuration_values_html );
	server.on ( "/admin/connectionstate", send_connection_state_values_html );
	server.on ( "/admin/infovalues", send_information_values_html );
  server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
  server.on ( "/admin/kolektoriusvalues", send_KolektoriausKonfiguracija_values_html );
  server.on ( "/admin/emoncmsvalues", send_Emoncms_values_html );
	server.on ( "/admin/generalvalues", send_general_configuration_values_html);
	server.on ( "/admin/devicename",     send_devicename_value_html);

	server.onNotFound ( []() { 
	  Serial.println("Page Not Found"); 
	  server.send ( 200, "text/html", PAGE_NotFound );   
	  }  );
	server.begin();

  MDNS.begin(host);
  httpUpdater.setup(&server);
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);


	tkSecond.attach(1,Second_Tick);
	UDPNTPClient.begin(2390);  // Port for NTP receive

//  Setup DS18b20 temperature sensor

  SetupDS18B20();
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);

}

 
void loop ( void ) {
//  digitalWrite(2, HIGH);
	if (AdminEnabled) {
		if (AdminTimeOutCounter > AdminTimeOut) {
			 AdminEnabled = false;
			 Serial.println("\n\nAdmin Mode disabled!\n\n");
        WiFi.reconnect();
        WiFi.mode(WIFI_STA);
      ConfigureWifi();
		             }	}
	if (config.Update_Time_Via_NTP_Every  > 0 ) {
		if (cNTP_Update > 5 && firstStart)
		{	NTPRefresh();
			cNTP_Update =0;
			firstStart = false;
		}
		else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
		{	NTPRefresh();
			cNTP_Update =0;
		}
	}
	if(DateTime.minute != Minute_Old)
	{	 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOn)
		 { if (DateTime.hour == config.TurnOnHour && DateTime.minute == config.TurnOnMinute)
			 { Serial.println("SwitchON"); }
		 }
		 Minute_Old = DateTime.minute;
		 if (config.AutoTurnOff)
		 { if (DateTime.hour == config.TurnOffHour && DateTime.minute == config.TurnOffMinute)
			 {Serial.println("SwitchOff"); }
		 }
	}
	server.handleClient();
///////////// *   START Your Code here    * //////////////////////
/****************************************************************/
  // Taimeris nustato laiko intervalus temperatūrų matavimui
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();

  // tikrinama ar jau laikas matuoti temperatūrą
  if ((unsigned long)(currentMillis - previousMillis) >= config.intervalas * 1000)
  {// digitalWrite(2, LOW);
    // įsimenamas paskutinio matavimo laikas
    previousMillis = currentMillis;

    TemteraturosMatavimas();
    Siurblys();
    long t = millis();Apsauga( t );
//    Serial.print("AdminTimeOutCounter - "); Serial.println(AdminTimeOutCounter);
    Serial.print("\nemoncmsOn - "); Serial.print(config.emoncmsOn);
    Serial.print(", apsauga - "); Serial.print(config.apsauga);
    Serial.print("\nK- "); Serial.print(Kolektorius);
    Serial.print(", B- "); Serial.print(Boileris);
    Serial.print(", O- "); Serial.print(Oras);
    Serial.printf("\nFreeMem: %d \nDabar- %d:%d:%d %d.%d.%d \n",ESP.getFreeHeap(), DateTime.year, DateTime.month, DateTime.day, DateTime.hour, DateTime.minute, DateTime.second);
}

    //ar aktyvuotas duomenų siuntimas į emoncms ir jau galima siųsti duomenis
    if ((config.emoncmsOn  == 1) & ((unsigned long)(currentMillis1 - previousMillis1) >= config.intervalasEmon * 1000)) 
    {
      // įsimenamas paskutinio matavimo laikas
      previousMillis1 = currentMillis1;
      emoncms();
    }



//  if (WiFi.mode(WIFI_STA))
//    machineIOs.SetLeds(noChange, noChange, (((millis() / 125) & 7) == 0) ? On : Off); // 1 Hz blink with 12.5% duty cycle
//  else
//    machineIOs.SetLeds(noChange, noChange, (((millis() / 125) & 7) != 0) ? On : Off); // 1 Hz blink with 87.5% duty cycle
//  machine.ModulateSound(((millis() / 63) & 7) == 0); // 2 Hz blink with 12.5% duty cycle (1.984... Hz)
/****************************************************************/
///////////// *    Your Code here END   * //////////////////////

  MDNS.update();
	
	if (Refresh)  
	{	Refresh = false;
//		Serial.println("Refreshing...");
//		Serial.printf("FreeMem:%d %d:%d:%d %d.%d.%d \n",ESP.getFreeHeap() , DateTime.hour,DateTime.minute, DateTime.second, DateTime.year, DateTime.month, DateTime.day);
	}
}
