
const char PAGE_Emoncms[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" type="text/css" href="/style.css">
<div class="smartphone">
  <div class="content">
<center><a href="admin.html" class="myButton" ><</a>
<span class="textas"> Emoncms nustatymai </span>
<a href="rastids18b20.html" class="myButton" >></a>

<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Serveris :</td><td><input type="text" id="emoncmsSrv" name="emoncmsSrv" size="15" maxlength="15" value=""></td></tr>
<tr><td align="right">Raktas :</td><td><input type="text" id="apikey" name="apikey" size="15" maxlength="32" value=""></td></tr>
<tr><td align="right">Reikšmė 1 :</td><td><input type="text" id="reiksme1" name="reiksme1" size="5" maxlength="6" value=""></td></tr>
<tr><td align="right">Reikšmė 2 :</td><td><input type="text" id="reiksme2" name="reiksme2" size="5" maxlength="6" value=""></td></tr>
<tr><td align="right">Reikšmė 3 :</td><td><input type="text" id="reiksme3" name="reiksme3" size="5" maxlength="6" value=""></td></tr>
<tr><td align="right">Reikšmė 4 :</td><td><input type="text" id="reiksme4" name="reiksme4" size="5" maxlength="6" value=""></td></tr>
<tr><td align="right">Katalogas :</td><td><input type="text" id="katalogas" name="katalogas" size="5" maxlength="6" value=""></td></tr>
<tr><td align="right">Intervalas (s) :</td><td><input type="text" id="intervalasEmon" name="intervalasEmon" min="10" max="600" size="3" maxlength="3" value=""></td></tr>
<tr><td align="right">Aktyvinti emoncms :</td><td><input type="checkbox" id="emoncmsOn" name="emoncmsOn"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="myButton" value="Įrašyti"></td></tr>

</table><br><br>
</form>
<a href="https://saulevire.lt/emoncms9/dashboard/view/testas?apikey=read">sukaupti duomenys</a>
</div></div></center>
<script>
  

window.onload = function ()
{
    load("microajax.js","js", function() 
    {
        setValues("/admin/emoncmsvalues");
    });
}
function load(e,t,n)
{if("js"==t){
  var a=document.createElement("script");
a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()}
,document.getElementsByTagName("head")[0].appendChild(a)
}
else if("css"==t){
  var a=document.createElement("link");
a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()
}
,document.getElementsByTagName("head")[0].appendChild(a)}
}



</script>
)=====";


void send_Emoncms_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    config.emoncmsOn = false;
    String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "emoncmsSrv") config.emoncmsSrv = urldecode( server.arg(i)); 
      if (server.argName(i) == "apikey") config.apikey = urldecode( server.arg(i)); 
      if (server.argName(i) == "reiksme1") config.reiksme1 = urldecode( server.arg(i)); 
      if (server.argName(i) == "reiksme2") config.reiksme2 = urldecode( server.arg(i)); 
      if (server.argName(i) == "reiksme3") config.reiksme3 = urldecode( server.arg(i)); 
//      if (server.argName(i) == "reiksme4") config.reiksme4 = urldecode( server.arg(i)); 
      if (server.argName(i) == "katalogas") config.katalogas = urldecode( server.arg(i)); 
      if (server.argName(i) == "intervalasEmon") config.intervalasEmon =  server.arg(i).toInt(); 
      if (server.argName(i) == "emoncmsOn") config.emoncmsOn = true; 
    }
    WriteConfig();   
    firstStart = true;
  }
  server.send ( 200, "text/html", PAGE_Emoncms ); 
  Serial.println(__FUNCTION__); 
  
}

void send_Emoncms_values_html()
{  
  String values ="";
  values += "emoncmsSrv|" + (String) config.emoncmsSrv + "|input\n";
  values += "apikey|" + (String) config.apikey + "|input\n";
  values += "reiksme1|" + (String) config.reiksme1 + "|input\n";
  values += "reiksme2|" +  (String) config.reiksme2 + "|input\n";
  values += "reiksme3|" +  (String) config.reiksme3 + "|input\n";
//  values += "reiksme4|" +  (String) config.reiksme4 + "|input\n";
  values += "katalogas|" +  (String) config.katalogas + "|input\n";
  values += "intervalasEmon|" +  (String) config.intervalasEmon + "|input\n";
  values += "emoncmsOn|" +  (String) (config.emoncmsOn ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  Serial.print("reiksme1 : ");Serial.println(config.reiksme1); 
  Serial.print("reiksme2 : ");Serial.println(config.reiksme2); 
  Serial.print("reiksme3 : ");Serial.println(config.reiksme3); 
//  Serial.print("reiksme4 : ");Serial.println(config.reiksme4); 
  Serial.print("katalogas : ");Serial.println(config.katalogas); 
  Serial.print("intervalasEmon : ");Serial.println(config.intervalasEmon); 
  Serial.print("emoncmsOn : ");Serial.println(config.emoncmsOn); 
  
}
