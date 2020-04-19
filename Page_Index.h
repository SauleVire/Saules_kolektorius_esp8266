#ifndef PAGE_EXAMPLE_H
#define PAGE_EXAMPLE_H
//
//   The EXAMPLE PAGE
//
const char PAGE_EXAMPLE[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<div class="smartphone">
  <div class="content">
<center><span class="textas">Saulės kolektoriaus valdiklis</span></center><hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:300px" >
<th colspan="2">
<a href="/admin.html" class="myButton">Valdiklio konfigūravimas</a>
<br>
<b>Dabartinė kolektoriaus būsena</b>
</th><tr><td>
<div align="right">Kolektorius :</div>
<div align="right">Boileris :</div>
<div align="right">Oras :</div>
<div align="right">Siurblio būsena :</div>
<div align="right">Laiko intervelas :</div>
<div align="right">Apsauga (0- išjungta):</div>
<div align="right">Nuorinimas (0- išjungta):</div>
</td><td> 
<div><span id="K_t"></span>&deg; C</div>
<div><span id="B_t"></span>&deg; C</div>
<div><span id="O_t"></span>&deg; C</div> 
<div><span id="rele"></span></div> 
<div><span id="laikas"></span> (s)</div> 
<div><span id="apsauga"></span></div> 
<div><span id="nuorinimas"></span></div> 
</td></tr>
<th colspan=2><a href="/"  class="myButton">Atnaujinti</a></th>
</table>
<hr>
<span class="textas">Dabar: <span id="data"></span><br>
Valdiklis veikia <span id="veikimoLaikas"></span><br>
<a href=https://saulevire.lt>SauleVire.lt</a> 2020 </br>
Mikroprograma: v<span id="versija"></span></span>
</div>
</div>
  
   <script>                
		window.onload = function ()
		{	load("style.css","css", function() 
			{	load("microajax.js","js", function() 
				{	setValues("/admin/filldynamicdata");  //-- this function calls the function on the ESP      
				});
			});
		}
		function load(e,t,n){
		  if("js"==t){var a=document.createElement("script");
		a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}
		else if("css"==t){var a=document.createElement("link");
		a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
   </script>

)=====";
#endif


void filldynamicdata()
{ 

            String timeStr = NTP.getUptimeString();
            timeStr.replace("days","d.");
  String values ="";
  values += "K_t|" + (String)Kolektorius +  "|div\n";
  values += "B_t|" + (String)Boileris +  "|div\n";
  values += "O_t|" + (String)Oras +  "|div\n";
  values += "rele|" + (String)relayState +  "|div\n";
  values += "laikas|" + (String) config.k_intervalas  +  "|div\n";
  values += "apsauga|" + (String)config.k_uzsalimas +  "|div\n";
  values += "nuorinimas|" + (String)config.k_nuorinimas +  "|div\n";
  values += "data|" + (String)DateTime.year + "." + (String)DateTime.month + "." + (String)DateTime.day + " " + (String)DateTime.hour + ":" + (String)DateTime.minute + ":" + (String)DateTime.second + " |div\n";
  values += "versija|" + (String)FIRMWARE_VERSION + " |div\n";
  values += "veikimoLaikas|" + (String)timeStr + " |div\n";
  server.send ( 200, "text/plain", values); 
  Serial.println(__FUNCTION__); 
}

void processIndex()
{        
    if (server.args() > 0 )  // Are there any POST/GET Fields ? 
    {
       for ( uint8_t i = 0; i < server.args(); i++ ) {  // Iterate through the fields
            if (server.argName(i) == "firstname") 
            {
                 // Your processing for the transmitted form-variable 
                 String fName = server.arg(i);
            }
        }
    }
    server.send ( 200, "text/html", PAGE_EXAMPLE  ); 
}
