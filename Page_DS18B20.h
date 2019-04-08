
//------------------------------------------
void Page_DS18B20(){
  String message = "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  message += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";
  message += "<link rel=\"stylesheet\" type=\"text/css\" href=\"/style.css\">\n";
  message += "<div class=\"smartphone\">\n";
  message += "<div class=\"content\">\n";
  message += "<center><a href=\"admin.html\"  class=\"btn btn--s\"><</a>\n";
  message += "<strong>ds18b20 nustatymai</strong>\n";
  message += "<a href=\"ntp.html\"  class=\"btn btn--s\">></a></center><hr>\n";
  message += "Rasta jutiklių: ";
  message += numberOfDevices;
  message += "<br>\n";
  char temperatureString[6];
  message += "<table border=\"1\">\n";
  message += "<tr><td>Jutiklio adresas</td><td>Temperatūra</td></tr>\n";
  for(int i=0;i<numberOfDevices;i++){
//    dtostrf(tempDev[i], 2, 2, temperatureString);
    float tempC = DS18B20.getTempC( devAddr[i] );
    Serial.print( "Sending temperature: " );
    Serial.println( tempC );

    message += "<tr><td>\n";
    message += GetAddressToString( devAddr[i] );
    message += "</td><td>\n";
    message += tempC;
    message += "</td></tr>\n";
  }
  message += "</table>\n";

  server.send(200, "text/html", message );
}
