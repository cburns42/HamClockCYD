#ifndef WEATHERJSON_H
#define WEATHERJSON_H

char *testJSON = R"rawliteral(
{
  "coord": {
    "lon": -71.9189,
    "lat": 43.1228
  },
  "weather": [
    {
      "id": 803,
      "main": "Clouds",
      "description": "broken clouds",
      "icon": "04d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 11.77,
    "feels_like": -0.09,
    "temp_min": 10.65,
    "temp_max": 13.19,
    "pressure": 1014,
    "humidity": 74,
    "sea_level": 1014,
    "grnd_level": 972
  },
  "visibility": 10000,
  "wind": {
    "speed": 8.37,
    "deg": 264,
    "gust": 14.61
  },
  "clouds": {
    "all": 78
  },
  "dt": 1769532650,
  "sys": {
    "type": 2,
    "id": 2016469,
    "country": "US",
    "sunrise": 1769515680,
    "sunset": 1769550758
  },
  "timezone": -18000,
  "id": 7257618,
  "name": "Hillsborough",
  "cod": 200
}
)rawliteral";
#endif