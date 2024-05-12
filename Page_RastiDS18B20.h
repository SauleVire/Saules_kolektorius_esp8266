//
//  HTML PAGE
//
const char Page_RastiDS18B20[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" type="text/css" href="/style.css">
<div class="smartphone">
  <div class="content">
<center><a href="admin.html"  class="myButton"><</a><span class="textas"> DS18B20 nustatymai </span>
<a href="ntp.html"  class="myButton">></a>

<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Rasta</td><td align="center">Priskirta</td></tr>
<tr><td align="right"><span id="t0"></span> - t0 </td><td><input type="text" id="Sid" name="Sid" size="2" maxlength="2" value=""> Šiltnamis</td></tr>
<tr><td align="right"><span id="t1"></span> - t1 </td><td><input type="text" id="Rid" name="Rid" size="2" maxlength="2" value=""> Rusys</td></tr>
<tr><td align="right"><span id="t2"></span> - t2 </td><td><input type="text" id="Oid" name="Oid" size="2" maxlength="2" value=""> Oras</td></tr>
<tr><td align="right"><span id="t3"></span> - t3 </td><td><input type="text" id="Kid" name="Kid" size="2" maxlength="2" value=""> Kolektorius</td></tr>
<tr><td align="right"><span id="t4"></span> - t4 </td><td><input type="text" id="Bid" name="Bid" size="2" maxlength="2" value=""> Boileris</td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="myButton" value="Įrašyti"></td></tr>
</table><br><br>
</form>

</div></div>
<script>
window.onload = function ()
{ load("microajax.js","js", function() 
    { setValues("/admin/rastids18b20values");
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


void send_RastiDS18B20_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    String temp = "";


    //------------------------------------------------------
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "Sid") config.Sid = server.arg(i).toInt();
      if (server.argName(i) == "Rid") config.Rid = server.arg(i).toInt();
      if (server.argName(i) == "Oid") config.Oid = server.arg(i).toInt();
      if (server.argName(i) == "Kid") config.Kid = server.arg(i).toInt(); 
      if (server.argName(i) == "Bid") config.Bid = server.arg(i).toInt(); 
    }
    //------------------------------------------------------
    WriteConfig();   
    firstStart = true;
  }
  server.send ( 200, "text/html", Page_RastiDS18B20 ); 
  Serial.println(__FUNCTION__); 
}

void send_RastiDS18B20_values_html()
{ 
  String values ="";
  values += "Sid|" + (String) config.Sid + "|input\n";
  values += "Rid|" + (String) config.Rid + "|input\n";
  values += "Oid|" + (String) config.Oid + "|input\n";
  values += "Kid|" + (String) config.Kid + "|input\n";
  values += "Bid|" + (String) config.Bid + "|input\n";
      //------------------------------------------------------

  for(int i=0;i<numberOfDevices;i++){
    tempDev[i] = DS18B20.getTempC( devAddr[i] );
    values += "t" + (String)i +"|" + (String) tempDev[i] + "|div\n";
  }
    DS18B20.requestTemperatures(); //Initiate the temperature measurement

  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
//  Serial.print("reiksme1: ");Serial.print(config.reiksme1); 
}
