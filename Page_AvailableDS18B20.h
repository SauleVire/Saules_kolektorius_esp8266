
//------------------------------------------
void Page_AvailableDS18B20(){
  String message = "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  message += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";
  message += "<link rel=\"stylesheet\" type=\"text/css\" href=\"/style.css\">\n";
  message += "<div class=\"smartphone\">\n";
  message += "<div class=\"content\">\n";
  message += "<center><a href=\"admin.html\"  class=\"myButton\"><</a>\n";
  message += "<strong>ds18b20 jutikliai</strong>\n";
  message += "<a href=\"setds18b20.html\"  class=\"myButton\">></a></center><hr>\n";
  message += "<center>Rasta jutiklių: " + (String)numberOfDevices + "<br>\n";
  message += "<table border=\"1\">\n";
  message += "<tr><td>Jutiklio adresas</td><td>Temperatūra</td><td>Nr.</td></tr>\n";

  for(int i=0;i<numberOfDevices;i++){
    float tempC = DS18B20.getTempC( devAddr[i] );
    Serial.print( "Sending temperature: " );
    Serial.println( tempC );
    message += "<tr><td>" + GetAddressToString( devAddr[i] ) + "</td>";
    message += "<td>" + (String)tempC + "</td>";
    message += "<td>" + (String)i + "</td></tr>\n";
  }
  message += "</table>\n";

  server.send(200, "text/html", message );
}
