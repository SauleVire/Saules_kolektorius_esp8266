//
//  HTML PAGE
//

const char PAGE_AdminMainPage[] PROGMEM = R"=====(
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="smartphone">
  <div class="content">
<center><strong>Valdiklio konfigūravimas</center>
<hr>
<div align="center"><a href="general.html" style="width:252px" class="btn btn--m btn--blue" >Bendroji konfigūracija</a></div>
<div align="center"><a href="config.html" style="width:252px" class="btn btn--m btn--blue" >Tinklo konfigūracija</a></div>
<div align="center"><a href="info.html"   style="width:252px"  class="btn btn--m btn--blue" >Tinklo informacija</a></div>
<div align="center"><a href="kolektorius.html" style="width:252px"  class="btn btn--m btn--blue" >Kolektoriaus parametrai</a></div>
<div align="center"><a href="emoncms.html" style="width:252px"  class="btn btn--m btn--blue" >Emoncms parametrai</a></div>
<div align="center"><a href="/rastids18b20.html" style="width:252px"  class="btn btn--m btn--blue" >DS18B20 parametrai</a></div>
<div align="center"><a href="ntp.html"   style="width:252px"  class="btn btn--m btn--blue" >NTP nustatymai</a></div>
<div align="center"><a href="/"   style="width:250px"  class="btn btn--m btn--blue" >Noriu namo!</a></div>

</div></div>
<script>
window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				// Do something after load...
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>

)=====";
