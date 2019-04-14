


void emoncms(){

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(config.emoncmsSrv, httpPort)) {
    Serial.println("connection failed");
    return;
  }

String url = "/emoncms9/input/post.json?node=" + String(config.katalogas) + "&json={"+ String(config.reiksme1)+":"+String(Kolektorius)+"," + String(config.reiksme2)+ ":"+String(Boileris)+","+ String(config.reiksme3)+":"+String(Oras)+"}&apikey="+String(config.apikey);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(config.emoncmsSrv) + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000) {
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
