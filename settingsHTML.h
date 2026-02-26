#ifndef SETTINGSHTML_H
#define SETTINGSHTML_H

char *settingsHTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; padding: 1em; }
    input { width: 100%; padding: 0.5em; margin: 0.5em 0; }
    button { padding: 0.6em; width: 100%; }
  </style>
</head>
<body>
  <h2>Ham Clock Setup</h2>
  <form method="POST" action="/save">
    <input name="ssid" placeholder="WiFi SSID">
    <input name="password" type="password" placeholder="password">
    <input name="openweatherkey" placeholder="OpenWeather API Key">
    <input name="openweatherlatitude" placeholder="OpenWeather Latitude">
    <input name="openweatherlogitude" placeholder="OpenWeather Longitude">
    <button type="submit">Save</button>
  </form>
</body>
</html>
)rawliteral";

char *settingsDoneHTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; padding: 1em; }
    input { width: 100%; padding: 0.5em; margin: 0.5em 0; }
    button { padding: 0.6em; width: 100%; }
  </style>
</head>
<body>
  <h2>Entry complete</h2>
  <B>AP Shutting down.</B>
</body>
</html>
)rawliteral";
#endif
