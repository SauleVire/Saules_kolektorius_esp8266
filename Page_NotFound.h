

//
//  HTML PAGE
//

const char PAGE_NotFound[] PROGMEM = R"=====(
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="smartphone">
  <div class="content">
<center><a href="admin.html" class="myButton" ><</a>
<span class="textas"> Tokio tinklapio čia nėra! </span>
<a href="/" class="myButton" >></a>

<hr>
<a href="admin.html" style="width:150px" class="myButton">Valdiklio konfigūravimas</a><br>
<a href="/"style="width1250px"  class="myButton" >Valdiklio būsena</a><br>
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
