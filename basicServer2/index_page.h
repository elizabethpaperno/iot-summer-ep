const char index_ESP[] PROGMEM= { R"delimiter(
  <html>
  <head>
    <title>
      ESP8266 Server  
    </title>
    <style>
      html { 
          background: url("https://c0.wallpaperflare.com/preview/729/634/463/abstract-backdrop-background-bright.jpg") no-repeat center center fixed; 
          -webkit-background-size: cover;
          -moz-background-size: cover;
          -o-background-size: cover;
          background-size: cover;
}
    </style>
  </head>
  <body>
    <h1> ESP8266 Server</h1>
    <br>
    <a href = "http://10.7.206.182/LED"> 1.LED </a>
    <br>
    <a href = "http://10.7.206.182/DHT"> 2.DHT </a>
  </body>
</html>)delimiter"};
