

//
//  HTML PAGE
//
const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<div class="smartphone">
  <div class="content">
<center><a href="admin.html"  class="myButton"><</a><span class="textas"> Tinklo konfigūracija </span>
<a href="info.html"  class="myButton">></a>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" style="width:300px" >
<tr><td align="right">SSID:</td><td><input type="text" id="ssid" name="ssid" maxlength="15" value=""></td></tr>
<tr><td align="right">Slaptažodis :</td><td><input type="text" id="password" name="password" value=""></td></tr>
<tr><td align="right">DHCP :</td><td><input type="checkbox" id="dhcp" name="dhcp"></td></tr>
<tr><td align="right">Tinklo adresas :</td><td><input type="text" id="ip_0" name="ip_0" size="1">.<input type="text" id="ip_1" name="ip_1" size="1">.<input type="text" id="ip_2" name="ip_2" size="1">.<input type="text" id="ip_3" name="ip_3" value="" size="1"></td></tr>
<tr><td align="right">DNS adresas :</td><td><input type="text" id="dns_0" name="dns_0" size="1">.<input type="text" id="dns_1" name="dns_1" size="1">.<input type="text" id="dns_2" name="dns_2" size="1">.<input type="text" id="dns_3" name="dns_3" value="" size="1"></td></tr>
<tr><td align="right">Tinklo kaukė :</td><td><input type="text" id="nm_0" name="nm_0" size="1">.<input type="text" id="nm_1" name="nm_1" size="1">.<input type="text" id="nm_2" name="nm_2" size="1">.<input type="text" id="nm_3" name="nm_3" size="1"></td></tr>
<tr><td align="right">Tinklų sietuvas :</td><td><input type="text" id="gw_0" name="gw_0" size="1">.<input type="text" id="gw_1" name="gw_1" size="1">.<input type="text" id="gw_2" name="gw_2" size="1">.<input type="text" id="gw_3" name="gw_3" size="1"></td></tr>
<tr><td colspan="2" align="center">
<input type="submit" style="width:150px" class="myButton" value="Įrašyti"></td></tr>

</table>
</form></center>

<span class="textas">Ryšio būsena:&nbsp;&nbsp;<span id="connectionstate">N/A<br>

Tinklai:</span><br>
<table border="0"  cellspacing="3" style="width:300px" >
<tr><td><div id="networks">Nuskaitymas...</div></td></tr>
<tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="myButton">Įkelti iš naujo</a></td></tr>
</table>

</div></div>
<script>

function GetState()
{
  setValues("/admin/connectionstate");
}
function selssid(value)
{
  document.getElementById("ssid").value = value; 
}


window.onload = function ()
{  load("style.css","css", function() 
  {    load("microajax.js","js", function() 
    {          setValues("/admin/values");
          setTimeout(GetState,3000);
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}




</script>


)=====";

const char PAGE_WaitAndReload[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=info.html">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

Palaukite....<br>įrašomi nustatymai ir paleidžiama iš naujo.
)=====";


//
//  SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
// 

void send_network_configuration_html()
{
  
  if (server.args() > 0 )  // Save Settings
  {
    String temp = "";
    config.dhcp = false;
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "ssid") config.ssid =   urldecode(server.arg(i));
      if (server.argName(i) == "password") config.password =    urldecode(server.arg(i)); 
      if (server.argName(i) == "ip_0") if (checkRange(server.arg(i)))   config.IP[0] =  server.arg(i).toInt();
      if (server.argName(i) == "ip_1") if (checkRange(server.arg(i)))   config.IP[1] =  server.arg(i).toInt();
      if (server.argName(i) == "ip_2") if (checkRange(server.arg(i)))   config.IP[2] =  server.arg(i).toInt();
      if (server.argName(i) == "ip_3") if (checkRange(server.arg(i)))   config.IP[3] =  server.arg(i).toInt();
      if (server.argName(i) == "dns_0") if (checkRange(server.arg(i)))   config.DNS[0] =  server.arg(i).toInt();
      if (server.argName(i) == "dns_1") if (checkRange(server.arg(i)))   config.DNS[1] =  server.arg(i).toInt();
      if (server.argName(i) == "dns_2") if (checkRange(server.arg(i)))   config.DNS[2] =  server.arg(i).toInt();
      if (server.argName(i) == "dns_3") if (checkRange(server.arg(i)))   config.DNS[3] =  server.arg(i).toInt();
      if (server.argName(i) == "nm_0") if (checkRange(server.arg(i)))   config.Netmask[0] =  server.arg(i).toInt();
      if (server.argName(i) == "nm_1") if (checkRange(server.arg(i)))   config.Netmask[1] =  server.arg(i).toInt();
      if (server.argName(i) == "nm_2") if (checkRange(server.arg(i)))   config.Netmask[2] =  server.arg(i).toInt();
      if (server.argName(i) == "nm_3") if (checkRange(server.arg(i)))   config.Netmask[3] =  server.arg(i).toInt();
      if (server.argName(i) == "gw_0") if (checkRange(server.arg(i)))   config.Gateway[0] =  server.arg(i).toInt();
      if (server.argName(i) == "gw_1") if (checkRange(server.arg(i)))   config.Gateway[1] =  server.arg(i).toInt();
      if (server.argName(i) == "gw_2") if (checkRange(server.arg(i)))   config.Gateway[2] =  server.arg(i).toInt();
      if (server.argName(i) == "gw_3") if (checkRange(server.arg(i)))   config.Gateway[3] =  server.arg(i).toInt();
      if (server.argName(i) == "dhcp") config.dhcp = true;
    }
     server.send ( 200, "text/html", PAGE_WaitAndReload );
    WriteConfig();
    ConfigureWifi();
    AdminTimeOutCounter=0;
    
  }
  else
  {
    server.send ( 200, "text/html", PAGE_NetworkConfiguration ); 
  }
  Serial.println(__FUNCTION__); 
}



//
//   FILL THE PAGE WITH VALUES
//

void send_network_configuration_values_html()
{

  String values ="";

values += "ssid|" + (String) config.ssid + "|input\n";
values += "password|" +  (String) config.password + "|input\n";
  values += "ip_0|" +  (String) config.IP[0] + "|input\n";
  values += "ip_1|" +  (String) config.IP[1] + "|input\n";
  values += "ip_2|" +  (String) config.IP[2] + "|input\n";
  values += "ip_3|" +  (String) config.IP[3] + "|input\n";
values += "dns_0|" +  (String) config.DNS[0] + "|input\n";
values += "dns_1|" +  (String) config.DNS[1] + "|input\n";
values += "dns_2|" +  (String) config.DNS[2] + "|input\n";
values += "dns_3|" +  (String) config.DNS[3] + "|input\n";
  values += "nm_0|" +  (String) config.Netmask[0] + "|input\n";
  values += "nm_1|" +  (String) config.Netmask[1] + "|input\n";
  values += "nm_2|" +  (String) config.Netmask[2] + "|input\n";
  values += "nm_3|" +  (String) config.Netmask[3] + "|input\n";
values += "gw_0|" +  (String) config.Gateway[0] + "|input\n";
values += "gw_1|" +  (String) config.Gateway[1] + "|input\n";
values += "gw_2|" +  (String) config.Gateway[2] + "|input\n";
values += "gw_3|" +  (String) config.Gateway[3] + "|input\n";
  values += "dhcp|" +  (String) (config.dhcp ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 
  
}


//
//   FILL THE PAGE WITH NETWORKSTATE & NETWORKS
//

void send_connection_state_values_html()
{

  String state = "N/A";
  String Networks = "";
  if (WiFi.status() == 0) state = "Idle";
  else if (WiFi.status() == 1) state = "NĖRA JOKIŲ TINKLŲ";
  else if (WiFi.status() == 2) state = "NUSKAITYMAS BAIGTAS";
  else if (WiFi.status() == 3) state = "PRISIJUNGTA";
  else if (WiFi.status() == 4) state = "NEPAVYKO PRISIJUNGTI";
  else if (WiFi.status() == 5) state = "NUTRŪKO RYŠIS";
  else if (WiFi.status() == 6) state = "ATSIJUNGTA";



   int n = WiFi.scanNetworks();
 
   if (n == 0)
   {
     Networks = "<font color='#FF0000'>Tinklų nerasta!</font>";
   }
  else
    {

    Networks = "Rasti tinklai: " +String(n) + "<br>";
    Networks += "<table border='0' cellspacing='0' cellpadding='3'>";
    Networks += "<tr bgcolor='#DDDDDD' ><td><strong>Pavadinimas</strong></td><td><strong>Signalas</strong></td><td><strong>Enc</strong></td><tr>";
    for (int i = 0; i < n; ++i)
    {
      int quality=0;
      if(WiFi.RSSI(i) <= -100)
      {
          quality = 0;
      }
      else if(WiFi.RSSI(i) >= -50)
      {
          quality = 100;
      }
      else
      {
        quality = 2 * (WiFi.RSSI(i) + 100);
      }


      Networks += "<tr><td><a href='javascript:selssid(\""  +  String(WiFi.SSID(i))  + "\")'>"  +  String(WiFi.SSID(i))  + "</a></td><td>" +  String(quality) + "%</td><td>" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")  + "</td></tr>";
    }
    Networks += "</table>";
  }
   
  String values ="";
  values += "connectionstate|" +  state + "|div\n";
  values += "networks|" +  Networks + "|div\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 
  
}
