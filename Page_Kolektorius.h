
const char PAGE_KolektoriausKonfiguracija[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<div class="smartphone">
  <div class="content">
<a href="admin.html"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Kolektoriaus nustatymai</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Įjungimo skirtumas (°C) :</td><td><input type="text" id="skirtumason" name="skirtumason" size="3" min="1" max="30" maxlength="2" value=""></td></tr>
<tr><td align="right">Išjungimo skirtumas (°C) :</td><td><input type="text" id="skirtumasoff" name="skirtumasoff" min="1" max="30" size="3" maxlength="2" value=""></td></tr>
<tr><td align="right">Laiko intervalas (s) :</td><td><input type="text" id="intervalas" name="intervalas" min="1" max="600" size="3" maxlength="3" value=""></td></tr>
<tr><td align="right">Apsauga nuo užšalimo :</td><td><input type="checkbox" id="apsauga" name="apsauga"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Įrašyti"></td></tr>

</table><br><br>
</form>
</div></div>
<script>
  

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/kolektoriusvalues");
    });
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


void send_KolektoriausKonfiguracija_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    config.apsauga = false;
    String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "skirtumason") config.skirtumason = server.arg(i).toInt(); 
      if (server.argName(i) == "skirtumasoff") config.skirtumasoff =  server.arg(i).toInt(); 
      if (server.argName(i) == "intervalas") config.intervalas =  server.arg(i).toInt(); 
      if (server.argName(i) == "apsauga") config.apsauga = true; 
    }
    WriteConfig();
    firstStart = true;
  }
  server.send ( 200, "text/html", PAGE_KolektoriausKonfiguracija ); 
  Serial.println(__FUNCTION__); 
  
}

void send_KolektoriausKonfiguracija_values_html()
{  
  String values ="";
  values += "skirtumason|" + (String) config.skirtumason + "|input\n";
  values += "skirtumasoff|" +  (String) config.skirtumasoff + "|input\n";
  values += "intervalas|" +  (String) config.intervalas + "|input\n";
  values += "apsauga|" +  (String) (config.apsauga ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  Serial.print("apsauga : ");Serial.println(config.apsauga); 
  Serial.print("intervalas : ");Serial.println(config.intervalas); 
  Serial.print("skirtumason : ");Serial.println(config.skirtumason); 
  Serial.print("skirtumasoff : ");Serial.println(config.skirtumasoff); 
  
}
