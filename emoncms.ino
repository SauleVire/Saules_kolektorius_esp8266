


void emoncms(){

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(config.emoncmsSrv, httpPort)) {
    Serial.println("connection failed");
    return;
  }

//String url = "/emoncms/input/post.json?node=" + String(config.katalogas) + "&json={"+ String(config.reiksme1)+":"+String(Kolektorius)+"," + String(config.reiksme2)+ ":"+String(Boileris)+","+ String(config.reiksme3)+":"+String(Oras)+"}&apikey="+String(config.apikey);
String url = "";
 url += "/emoncms/input/post.json?node=";
 url += String(config.katalogas);
 url += "&json={"+ String(config.reiksme0)+":"+String(Kolektorius)+",";
 url += String(config.reiksme1)+ ":"+String(Boileris)+",";
 url += String(config.reiksme2)+":"+String(Oras)+",";
 url += String(config.reiksme3)+":"+String(Siltnamis)+",";
 url += String(config.reiksme4)+":"+String(Rusys);
 url += "}&apikey="+String(config.apikey);

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(config.emoncmsSrv) + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 750) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  
}
