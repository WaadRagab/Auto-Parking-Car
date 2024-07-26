const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Control Car via Web</title>
<meta name="viewport" content="width=device-width, initial-scale=0.7, maximum-scale=1, user-scalable=no">
<style type="text/css">
body { text-align: center; font-size: 24px;}
button { text-align: center; font-size: 24px;}
#container {
    margin-right: auto;
    margin-left: auto;
  width: 400px; 
    height: 400px;
    position: relative;
    margin-bottom: 10px;
}
div[class^='button'] { position: absolute; }
.button_up, .button_down { width:214px; height:104px;}
.button_left, .button_right { width:104px; height:214px;}
.button_stop { width:178px; height:178px;}
.button_up {
    background: url('https://esp32io.com/images/tutorial/up_inactive.png') no-repeat; 
  background-size: contain; 
    left: 200px;
    top: 0px;
  transform: translateX(-50%);
}

.button_down {
    background: url('https://esp32io.com/images/tutorial/down_inactive.png') no-repeat; 
  background-size: contain; 
    left:200px;
    bottom: 0px;
  transform: translateX(-50%);
}

.button_right {
    background: url('https://esp32io.com/images/tutorial/right_inactive.png') no-repeat;
  background-size: contain;   
    right: 0px;
    top: 200px;
  transform: translateY(-50%);
}

.button_left {
    background: url('https://esp32io.com/images/tutorial/left_inactive.png') no-repeat; 
  background-size: contain;
    left:0px;
    top: 200px;
  transform: translateY(-50%);
}

.button_stop {
  background: url('https://esp32io.com/images/tutorial/stop_inactive.png') no-repeat; 
  background-size: contain;
    left:200px;
    top: 200px;
  transform: translate(-50%, -50%);
}
</style>
<script>
var CMD_STOP     = 0;
var CMD_FORWARD  = 1;
var CMD_BACKWARD = 2;
var CMD_LEFT     = 4;
var CMD_RIGHT    = 8;
var img_name_lookup = {
  [CMD_STOP]:     "stop",
  [CMD_FORWARD]:  "up",
  [CMD_BACKWARD]: "down",
  [CMD_LEFT]:     "left",
  [CMD_RIGHT]:    "right"
}
var ws = null;

function init() 
{
  
  var container = document.querySelector("#container");
    container.addEventListener("touchstart", mouse_down);
    container.addEventListener("touchend", mouse_up);
    container.addEventListener("touchcancel", mouse_up);
    container.addEventListener("mousedown", mouse_down);
    container.addEventListener("mouseup", mouse_up);
    container.addEventListener("mouseout", mouse_up);    
}
function ws_onmessage(e_msg)
{
    e_msg = e_msg || window.event; // MessageEvent
 
    //alert("msg : " + e_msg.data);
}
function ws_onopen()
{
  document.getElementById("ws_state").innerHTML = "OPEN";
  document.getElementById("wc_conn").innerHTML = "Disconnect";
}
function ws_onclose()
{
  document.getElementById("ws_state").innerHTML = "CLOSED";
  document.getElementById("wc_conn").innerHTML = "Connect";
  console.log("socket was closed");
  ws.onopen = null;
  ws.onclose = null;
  ws.onmessage = null;
  ws = null;
}
function wc_onclick()
{
  if(ws == null)
  {
    ws = new WebSocket("ws://" + window.location.host + ":81");
    document.getElementById("ws_state").innerHTML = "CONNECTING";
    
    ws.onopen = ws_onopen;
    ws.onclose = ws_onclose;
    ws.onmessage = ws_onmessage; 
  }
  else
    ws.close();
}
function mouse_down(event) 
{
  if (event.target !== event.currentTarget) 
  {
    var id = event.target.id;
    send_command(id);
    event.target.style.backgroundImage = "url('https://esp32io.com/images/tutorial/" + img_name_lookup[id] + "_active.png')";
    }
    event.stopPropagation();    
    event.preventDefault();    
}

function mouse_up(event) 
{
  if (event.target !== event.currentTarget) 
  {
    var id = event.target.id;
    send_command(CMD_STOP);
    event.target.style.backgroundImage = "url('https://esp32io.com/images/tutorial/" + img_name_lookup[id] + "_inactive.png')";
    }
    event.stopPropagation();   
    event.preventDefault();    
}
function send_command(cmd) 
{   
  if(ws != null)
    if(ws.readyState == 1)
      ws.send(cmd + "\r\n");   
}

window.onload = init;
</script>
</head>
<body>
<h2>ESP32 - RC Car via Web</h2>
<div id="container">
  <div id="0" class="button_stop"></div>
    <div id="1" class="button_up"></div>
    <div id="2" class="button_down"></div>
    <div id="8" class="button_right"></div>
    <div id="4" class="button_left"></div>
</div>
<p>
WebSocket : <span id="ws_state" style="color:blue">closed</span><br>
</p>
<button id="wc_conn" type="button" onclick="wc_onclick();">Connect</button>
<br>
<br>
<div class="sponsor">Sponsored by <a href="https://amazon.com/diyables">DIYables</a></div>
</body>
</html>
)=====";