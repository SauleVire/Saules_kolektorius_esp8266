#ifndef PAGE_INFOMATION_H
#define PAGE_INFOMATION_H


//
//   The HTML PAGE
//
const char PAGE_Information[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="microajax.js"></script> 
<div class="smartphone">
  <div class="content">
<center><a href="admin.html"  class="myButton"><</a><span class="textas"> Tinklo informacija </span>
<a href="kolektorius.html"  class="myButton">></a>
<hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:300px" >
<tr><td align="right">SSID :</td><td><span id="x_ssid"></span></td></tr>
<tr><td align="right">Tinklo adresas :</td><td><span id="x_ip"></span></td></tr>
<tr><td align="right">Dns adresas :</td><td><span id="x_dns"></span></td></tr>
<tr><td align="right">Tinklo kaukė :</td><td><span id="x_netmask"></span></td></tr>
<tr><td align="right">Tinklų sietuvas :</td><td><span id="x_gateway"></span></td></tr>
<tr><td align="right">Mac :</td><td><span id="x_mac"></span></td></tr>
<tr><td colspan="2"><hr></span></td></tr>
<tr><td align="right">Programos versija :</td><td><span id="x_fw"></span></td></tr>

<tr><td colspan="2"><hr></span></td></tr>
<tr><td align="right">NTP Laikas :</td><td><span id="x_ntp"></span></td></tr>


<tr><td colspan="2" align="center"><a href="javascript:GetState()" class="myButton">Įkelti iš naujo</a></td></tr>
</table>
</div></div></center>
<script>

function GetState()
{  setValues("/admin/infovalues");
}

window.onload = function ()
{  load("style.css","css", function() 
  {    load("microajax.js","js", function() 
    {        GetState();
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;


//
// FILL WITH INFOMATION
// 

void send_information_values_html ()
{

  String values ="";

  values += "x_ssid|" + (String)WiFi.SSID() +  "|div\n";
  values += "x_ip|" +  (String) WiFi.localIP()[0] + "." +  (String) WiFi.localIP()[1] + "." +  (String) WiFi.localIP()[2] + "." + (String) WiFi.localIP()[3] +  "|div\n";
  values += "x_dns|" +  (String) WiFi.dnsIP()[0] + "." +  (String) WiFi.dnsIP()[1] + "." +  (String) WiFi.dnsIP()[2] + "." + (String) WiFi.dnsIP()[3] +  "|div\n";
  values += "x_gateway|" +  (String) WiFi.gatewayIP()[0] + "." +  (String) WiFi.gatewayIP()[1] + "." +  (String) WiFi.gatewayIP()[2] + "." + (String) WiFi.gatewayIP()[3] +  "|div\n";
  values += "x_netmask|" +  (String) WiFi.subnetMask()[0] + "." +  (String) WiFi.subnetMask()[1] + "." +  (String) WiFi.subnetMask()[2] + "." + (String) WiFi.subnetMask()[3] +  "|div\n";
  values += "x_mac|" + GetMacAddress() +  "|div\n";
  values += "x_fw|" + FIRMWARE_VERSION +  "|div\n";
  values += "x_ntp|" + (String)   DateTime.year + "." + (String)  DateTime.month + "." + (String)  DateTime.day +  " " +  (String) DateTime.hour + ":" + (String) + DateTime.minute +  ":" + (String)  DateTime.second + " |div\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 

}


#endif
