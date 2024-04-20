
const char PAGE_Style_css[] PROGMEM = R"=====(
body { color: #000000; font-family: avenir, helvetica, arial, sans-serif; } 
hr {    background-color: #eee;    border: 0 none;   color: #eee;    height: 1px; } 
.btn, .btn:link, .btn:visited {  
	border-radius: 0.3em;  
	border-style: solid;  
	border-width: 1px;  
color: #111;  
display: inline-block;  
	font-family: avenir, helvetica, arial, sans-serif;  
/*  letter-spacing: 0.15em;  */
	margin-bottom: 0.5em;  
padding: 1em 0.75em;  
	text-decoration: none;  
	text-transform: uppercase;  
	-webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;  
transition: color 0.4s, background-color 0.4s, border 0.4s; 
} 
.btn:hover, .btn:focus {
color: #7FDBFF;  
border: 1px solid #7FDBFF;  
	-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
}
	.btn:active {  
color: #0074D9;  
border: 1px solid #0074D9;  
		-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
	} 
	.btn--s 
	{  
		font-size: 12px; 
	}
	.btn--m { 
		font-size: 12px; 
	}
	.btn--l {  
		font-size: 14px;  border-radius: 0.25em !important; 
	} 
	.btn--full, .btn--full:link {
		border-radius: 0.25em; 
display: block;  
			margin-left: auto; 
			margin-right: auto; 
			text-align: center; 
width: 100%; 
	} 
	.btn--blue:link, .btn--blue:visited {
color: #fff;  
		background-color: #0074D9; 
	}
	.btn--blue:hover, .btn--blue:focus {
color: #fff !important;  
		background-color: #0063aa;  
		border-color: #0063aa; 
	}
	.btn--blue:active {
color: #fff; 
		background-color: #001F3F;  border-color: #001F3F; 
	}
	@media screen and (min-width: 32em) {
		.btn--full {  
			max-width: 16em !important; } 
	}
 /* The device with borders */
.smartphone {
  position: relative;
  width: 300px;
  height: 480px;
  margin: auto;
  border: 12px green solid;
  border-top-width: 60px;
  border-bottom-width: 60px;
  border-radius: 36px;
}

/* The horizontal line on the top of the device */
.smartphone:before {
  content: '';
  display: block;
  width: 60px;
  height: 5px;
  position: absolute;
  top: -30px;
  left: 50%;
  transform: translate(-50%, -50%);
  background: #333;
  border-radius: 10px;
}

/* The circle on the bottom of the device */
.smartphone:after {
  content: '';
  display: block;
  width: 35px;
  height: 35px;
  position: absolute;
  left: 50%;
  bottom: -65px;
  transform: translate(-50%, -50%);
  background: #333;
  border-radius: 50%;
}

/* The screen (or content) of the device */
.smartphone .content {
  width: 300px;
  height: 480px;
  background: white;
}
.myButton {
  -moz-box-shadow: 0px 1px 0px 0px #fff6af;
  -webkit-box-shadow: 0px 1px 0px 0px #fff6af;
  box-shadow: 0px 1px 0px 0px #fff6af;
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffec64), color-stop(1, #ffab23));
  background:-moz-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-webkit-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-o-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-ms-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:linear-gradient(to bottom, #ffec64 5%, #ffab23 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffec64', endColorstr='#ffab23',GradientType=0);
  background-color:#ffec64;
  -moz-border-radius:12px;
  -webkit-border-radius:12px;
  border-radius:12px;
  border:2px solid #ffaa22;
  display:inline-block;
  cursor:pointer;
  color:#333333;
  font-family:Arial;
  font-size:12px;
  font-weight:bold;
  padding:0px 24px;
  text-decoration:none;
  text-shadow:0px 1px 0px #ffee66;
}
.myButton:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffab23), color-stop(1, #ffec64));
  background:-moz-linear-gradient(top, #ffab23 5%, #ffec64 100%);
  background:-webkit-linear-gradient(top, #ffab23 5%, #ffec64 100%);
  background:-o-linear-gradient(top, #ffab23 5%, #ffec64 100%);
  background:-ms-linear-gradient(top, #ffab23 5%, #ffec64 100%);
  background:linear-gradient(to bottom, #ffab23 5%, #ffec64 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffab23', endColorstr='#ffec64',GradientType=0);
  background-color:#ffab23;
}
.myButton:active {
  position:relative;
  top:1px;
}
.textas {font-size: 12px;font-family:Arial; font-weight:bold;}
input[type=file]::file-selector-button {
  -moz-box-shadow: 0px 1px 0px 0px #fff6af;
  -webkit-box-shadow: 0px 1px 0px 0px #fff6af;
  box-shadow: 0px 1px 0px 0px #fff6af;
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffec64), color-stop(1, #ffab23));
  background:-moz-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-webkit-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-o-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:-ms-linear-gradient(top, #ffec64 5%, #ffab23 100%);
  background:linear-gradient(to bottom, #ffec64 5%, #ffab23 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffec64', endColorstr='#ffab23',GradientType=0);
  background-color:#ffec64;
  -moz-border-radius:12px;
  -webkit-border-radius:12px;
  border-radius:12px;
  border:2px solid #ffaa22;
  display:inline-block;
  cursor:pointer;
  color:#333333;
  font-family:Arial;
  font-size:12px;
  font-weight:bold;
  padding:0px 24px;
  text-decoration:none;
  text-shadow:0px 1px 0px #ffee66;
}
table {border-collapse: collapse;width: 100%;font-size: 12px;font-family:Arial;font-weight:bold;}
)=====";
 
