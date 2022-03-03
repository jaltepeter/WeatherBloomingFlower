#define ARDUINOJSON_USE_LONG_LONG 1
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "SSID";         // SSID Name
const char *password = "PASSWORD"; // SSID Password

const String key = "APIKEY"; // API Key for api.openweathermap.org

const double lat = 44.46049654778244;
const double lon = -110.82813058441761;

const double refreshDelay = 0.5; // in minutes

const String endpoint = "https://api.openweathermap.org/data/2.5/weather";

WiFiClientSecure wifiClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

struct weatherData
{
  double temp;
  unsigned long sunrise;
  unsigned long sunset;
};

typedef struct weatherData WeatherData;

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println('\n');

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection Established");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

  unsigned long time = getCurrentEpochTime();

  WeatherData weather = getCurrentWeatherData();

  Serial.println('\n');
  Serial.print("Current Time Is: ");
  Serial.println(time);
  Serial.print("Current Temp Is: ");
  Serial.println(weather.temp);
  Serial.print("Current Sun Is: ");
  Serial.println(isSunUp(weather, time) ? "Up" : "Down");

  setColor(weather.temp);

  setPetals(isSunUp(weather, time));

  delay(refreshDelay * 60 * 1000);
}

void setColor(double temp)
{
  // TODO: Set Color according to temp
}

void setPetals(bool open)
{
  // TODO: Set petals accordingly
}

bool isSunUp(WeatherData weather, unsigned long epochTime)
{
  return (epochTime > weather.sunrise && epochTime < weather.sunset);
}

unsigned long getCurrentEpochTime()
{
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}

WeatherData getCurrentWeatherData()
{

  WeatherData w;

  if (WiFi.status() == WL_CONNECTED)
  {

    HTTPClient http;

    wifiClient.setInsecure();

    String url = endpoint + "?lat=" + lat + "&lon=" + lon + "&units=imperial&appid=" + key;

    http.begin(wifiClient, url);
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      JSONVar weather = JSON.parse(http.getString());

      if (JSON.typeof(weather) == "undefined")
      {
        Serial.println("Parsing temperature input failed!");
        return w;
      }

      w.temp = weather["main"]["temp"];
      w.sunrise = (long)weather["sys"]["sunrise"];
      w.sunset = (long)weather["sys"]["sunset"];
    }

    else
    {
      Serial.println("Error on HTTP request to get temperature");
    }

    http.end(); // Free the resources
  }

  return w;
}
