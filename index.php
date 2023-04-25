<?php require 'database.php'; ?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>ED</title>
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/shoelace-css/1.0.0-beta16/shoelace.css">
    
    <style>
      html {
          font-family: Arial;
          display: inline-block;
          margin: 0px auto;
          text-align: center;
      }
      
      h1 { font-size: 2.0rem; color:#2980b9;}
      h2 { font-size: 1.25rem; color:#2980b9;}
      
      .buttonON {
        display: inline-block;
        font-weight: bold;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #4CAF50;
        border: none;
        border-radius: 15px;
        box-shadow: 0 5px #999;
      }
      .buttonON:hover {background-color: #3e8e41}
      .buttonON:active {
        background-color: #3e8e41;
        box-shadow: 0 1px #666;
        transform: translateY(4px);
      }
        
      .buttonOFF {
        display: inline-block;
        font-weight: bold;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #e74c3c;
        border: none;
        border-radius: 15px;
        box-shadow: 0 5px #999;
      }
      .buttonOFF:hover {background-color: #c0392b}
      .buttonOFF:active {
        background-color: #c0392b;
        box-shadow: 0 1px #666;
        transform: translateY(4px);
      }
    </style>
  </head>
  <body><br>
    <h2>HOME SECURITY CONTROL PANEL</h2>
    <div class="col-md-12">
    <img src="{{ url_for('video_feed') }}">
    </div>
    <br><br><br>
    <form action="{{ url_for('update') }}" method="post" id="LED-1_ON">
      <input type="hidden" name="Stat" value="1"/>    
      <input type="hidden" name="table" value="light"/>    
    </form>
    <form action="{{ url_for('update') }}" method="post" id="LED-1_OFF">
      <input type="hidden" name="Stat" value="0"/>
      <input type="hidden" name="table" value="light"/>  
    </form>
    <form action="{{ url_for('update') }}" method="post" id="ALARM_ON">
      <input type="hidden" name="Stat" value="1"/>    
      <input type="hidden" name="table" value="alarm"/>    
    </form>
    <form action="{{ url_for('update') }}" method="post" id="ALARM_OFF">
      <input type="hidden" name="Stat" value="0"/>
      <input type="hidden" name="table" value="alarm"/>  
    </form>
    <form action="{{ url_for('update') }}" method="post" id="Fire_ON">
      <input type="hidden" name="Stat" value="1"/>    
      <input type="hidden" name="table" value="fire"/>    
    </form>
    <form action="{{ url_for('update') }}" method="post" id="Fire_OFF">
      <input type="hidden" name="Stat" value="0"/>
      <input type="hidden" name="table" value="fire"/>  
    </form>
    <form action="{{ url_for('update') }}" method="post" id="SOME_HOME">
      <input type="hidden" name="Stat" value="1"/>
      <input type="hidden" name="table" value="home"/>  
    </form>
    <form action="{{ url_for('update') }}" method="post" id="NO_HOME">
      <input type="hidden" name="Stat" value="0"/>    
      <input type="hidden" name="table" value="home"/>    
    </form>
    <br><br>
    <button class="buttonON" type="submit" form="LED-1_ON" >LIGHT ON</button>
    <button class="buttonOFF" type="submit" form="LED-1_OFF" >LIGHT OFF</button>  
    <br><br>
    <button class="buttonON" type="submit" form="ALARM_ON" >ALARM ON</button>
    <button class="buttonOFF" type="submit" form="ALARM_OFF" >ALARM OFF</button>  
    <br><br>
    <button class="buttonON" type="submit" form="Fire_ON" >Fire Extinguisher ON</button>
    <button class="buttonOFF" type="submit" form="Fire_OFF" >Fire Extinguisher OFF</button>  
    <br><br>
    <button class="buttonON" type="submit" form="SOME_HOME" >Some-one home</button>
    <button class="buttonOFF" type="submit" form="NO_HOME" >No-one home</button>  
    <br><br>
    </script>
  </body>
</html>