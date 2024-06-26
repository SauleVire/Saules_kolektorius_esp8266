//
//  HTML PAGE
//

const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<div class="smartphone">
  <div class="content">

<center><a href="admin.html" class="myButton" ><</a>
<span class="textas"> Bendroji konfigūracija </span>
<a href="config.html" class="myButton" >></a>
<hr>
<span class="textas">
<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr>
	<td align="right">Valdiklio pavadinimas</td>
	<td><input type="text" id="devicename" name="devicename" value="" size="9"></td>
</tr>

<tr>
	<td align="left" colspan="2"><hr></td>
</tr>
<tr>
	<td align="right"> Aktyvinti įjungimą:</td>
	<td><input type="checkbox" id="tonenabled" name="tonenabled"></td>
</tr>

<tr>
	<td align="right"> Laikas:</td>
	<td><input type="text" id="tonhour" name="tonhour" size="2" value="00">:<input type="text" id="tonminute" name="tonminute" size="2" value="00"></td>
</tr>
	<td align="right"> Aktyvinti išjungimą:</td>
	<td><input type="checkbox" id="toffenabled" name="toffenabled"></td>
</tr>
<tr>
	<td align="right"> Laikas:</td>
	<td><input type="text" id="toffhour" name="toffhour" size="2" value="00">:<input type="text" id="toffminute" name="toffminute" size="2" value="00"></td>
</tr>

<tr>
	<td align="right"> Aktyvinti termostatą:</td>
	<td><input type="checkbox" id="termostatas" name="termostatas"></td>
</tr>

<tr>
	<td align="right">Įjungimo t (°C):</td>
	<td><input type="text" id="t_ijungimo" name="t_ijungimo" size="3" maxlength="4" value=""></td>
</tr>
<tr>
	<td align="right">Išjungimo t (°C):</td>
	<td><input type="text" id="t_isjungimo" name="t_isjungimo" size="3" maxlength="4" value=""></td>
</tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="myButton" value="Įrašyti"></td></tr>
</table>
</form>
</span>
</div></div></center>
<script>


window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				setValues("/admin/generalvalues");
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";


// Functions for this Page
void send_devicename_value_html()
{
		
	String values ="";
	values += "devicename|" + (String) config.DeviceName + "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}

void send_general_html()
{
	
	if (server.args() > 0 )  // Save Settings
	{
		config.AutoTurnOn = false;
		config.AutoTurnOff = false;
		config.termostatas = false;
		String temp = "";
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "devicename") config.DeviceName = urldecode(server.arg(i)); 
			if (server.argName(i) == "tonenabled") config.AutoTurnOn = true; 
			if (server.argName(i) == "toffenabled") config.AutoTurnOff = true; 
			if (server.argName(i) == "tonhour") config.TurnOnHour =  server.arg(i).toInt(); 
			if (server.argName(i) == "tonminute") config.TurnOnMinute =  server.arg(i).toInt(); 
			if (server.argName(i) == "toffhour") config.TurnOffHour =  server.arg(i).toInt(); 
			if (server.argName(i) == "toffminute") config.TurnOffMinute =  server.arg(i).toInt(); 
      if (server.argName(i) == "termostatas") config.termostatas = true; 
      if (server.argName(i) == "t_ijungimo") config.t_ijungimo = server.arg(i).toFloat();
      if (server.argName(i) == "t_isjungimo") config.t_isjungimo = server.arg(i).toFloat();      
		}
		WriteConfig();
		firstStart = true;
	}
	server.send ( 200, "text/html", PAGE_AdminGeneralSettings ); 
	Serial.println(__FUNCTION__); 
	
	
}

void send_general_configuration_values_html()
{
	String values ="";
	values += "devicename|" +  (String)  config.DeviceName +  "|input\n";
	values += "tonhour|" +  (String)  config.TurnOnHour +  "|input\n";
	values += "tonminute|" +   (String) config.TurnOnMinute +  "|input\n";
	values += "toffhour|" +  (String)  config.TurnOffHour +  "|input\n";
	values += "toffminute|" +   (String)  config.TurnOffMinute +  "|input\n";
	values += "toffenabled|" +  (String) (config.AutoTurnOff ? "checked" : "") + "|chk\n";
	values += "tonenabled|" +  (String) (config.AutoTurnOn ? "checked" : "") + "|chk\n";
	values += "termostatas|" +  (String) (config.termostatas ? "checked" : "") + "|chk\n";
  values += "t_ijungimo|" +  (String) config.t_ijungimo + "|input\n";
  values += "t_isjungimo|" +  (String) config.t_isjungimo + "|input\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
}
