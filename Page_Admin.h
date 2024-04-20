//
//  HTML PAGE
//

const char PAGE_AdminMainPage[] PROGMEM = R"=====(
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="smartphone">
  <div class="content">

<center><a href="/" class="myButton" ><</a>
<span class="textas"> Valdiklio konfigūravimas </span>
<a href="general.html" class="myButton" >></a>  

<hr>
<div align="center"><a href="general.html" style="width:222px" class="myButton" >Bendroji konfigūracija</a></div>
<div align="center"><a href="config.html" style="width:222px" class="myButton" >Tinklo konfigūracija</a></div>
<div align="center"><a href="info.html"   style="width:222px"  class="myButton" >Tinklo informacija</a></div>
<div align="center"><a href="solarcollector.html" style="width:222px"  class="myButton" >Kolektoriaus parametrai</a></div>
<div align="center"><a href="emoncms.html" style="width:222px"  class="myButton" >Emoncms parametrai</a></div>
<div align="center"><a href="ds18b20.html" style="width:222px"  class="myButton" >Rasti DS18B20 jutikliai</a></div>
<div align="center"><a href="setds18b20.html" style="width:222px"  class="myButton" >DS18B20 parametrai</a></div>
<div align="center"><a href="ntp.html"   style="width:222px"  class="myButton" >NTP nustatymai</a></div>
<div align="center"><a href="naujinimas.html"   style="width:222px"  class="myButton" >Programos naujinimas</a></div>
<div align="center"><a href="/"   style="width:220px"  class="myButton" >Noriu namo!</a></div>

</div></div></center>
<script>
window.onload = function ()
{	load("style.css","css", function() 
	{		load("microajax.js","js", function() 
		{				// Do something after load...
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";
