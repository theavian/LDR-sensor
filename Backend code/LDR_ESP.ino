#include <WiFi.h>
#include <PubSubClient.h>

char clientId[50];

WiFiClient espClient;
PubSubClient client(espClient);
static char strDetection[10] = {0};


int value = 0; //
void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin("Wokwi-GUEST", "");
  client.setServer("broker.emqx.io", 1883);
  Serial.begin(9600);

}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println(" connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop()
{

  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
  value = digitalRead(4);
  Serial.println(value);
  sprintf(strDetection, "%d", value);
  client.publish("topicName/detection", strDetection);

}

