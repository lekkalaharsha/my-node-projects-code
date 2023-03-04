/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2022 mobizt
 *
 */

/** This example shows the RTDB data changed notification with external Client.
 * This example used ESP32 and WIZnet W5500 devices which SSLClient and EthernetLarge will be used as the external Client.
 *
 * Don't gorget to define this in FirebaseFS.h
 * #define FB_ENABLE_EXTERNAL_CLIENT
 */

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. install EthernetLarge library */
// https://github.com/OPEnSLab-OSU/EthernetLarge
// Include EthernetLarge.h
#include <EthernetLarge.h>

/* 2. Install SSLClient library */
// https://github.com/OPEnSLab-OSU/SSLClient
#include <SSLClient.h>

/* 3. Create Trus anchors for the server i.e. www.google.com */
// https://github.com/OPEnSLab-OSU/SSLClient/blob/master/TrustAnchors.md
// or generate using this site https://openslab-osu.github.io/bearssl-certificate-utility/
#include "trust_anchors.h"

// For NTP time client
#include "MB_NTP.h"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 4. Define the API Key */
#define API_KEY "API_KEY"

/* 5. Define the RTDB URL */
#define DATABASE_URL "URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 6. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "USER_EMAIL"
#define USER_PASSWORD "USER_PASSWORD"

/* 7. Defined the Ethernet module connection */
#define WIZNET_RESET_PIN 26 // Connect W5500 Reset pin to GPIO 26 of ESP32
#define WIZNET_CS_PIN 5     // Connect W5500 CS pin to GPIO 5 of ESP32
#define WIZNET_MISO_PIN 19  // Connect W5500 MISO pin to GPIO 19 of ESP32
#define WIZNET_MOSI_PIN 23  // Connect W5500 MOSI pin to GPIO 23 of ESP32
#define WIZNET_SCLK_PIN 18  // Connect W5500 SCLK pin to GPIO 18 of ESP32

/* 8. Define the analog GPIO pin to pull random bytes from, used in seeding the RNG for SSLClient */
const int analog_pin = 34; // ESP32 GPIO 34 (Analog pin)

/* 9. Define MAC */
uint8_t Eth_MAC[] = {0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01};

/* 10. Define IP (Optional) */
IPAddress Eth_IP(192, 168, 1, 104);

// Define Firebase Data object
FirebaseData stream;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int count = 0;

volatile bool dataChanged = false;

EthernetClient client;

EthernetClient client2;

const int analog_pin = 34; // ESP32 GPIO 34 (Analog pin)

SSLClient ssl_client(client, TAs, (size_t)TAs_NUM, analog_pin);

SSLClient ssl_client2(client2, TAs, (size_t)TAs_NUM, analog_pin);

// For NTP client
EthernetUDP udpClient;

MB_NTP ntpClient(&udpClient, "pool.ntp.org" /* NTP host */, 123 /* NTP port */, 0 /* timezone offset in seconds */);

uint32_t timestamp = 0;

void ResetEthernet()
{
  Serial.println("Resetting WIZnet W5500 Ethernet Board...  ");
  pinMode(WIZNET_RESET_PIN, OUTPUT);
  digitalWrite(WIZNET_RESET_PIN, HIGH);
  delay(200);
  digitalWrite(WIZNET_RESET_PIN, LOW);
  delay(50);
  digitalWrite(WIZNET_RESET_PIN, HIGH);
  delay(200);
}

void networkConnection()
{
  Ethernet.init(WIZNET_CS_PIN);

  ResetEthernet();

  Serial.println("Starting Ethernet connection...");
  Ethernet.begin(Eth_MAC);

  unsigned long to = millis();

  while (Ethernet.linkStatus() == LinkOFF || millis() - to < 2000)
  {
    delay(100);
  }

  if (Ethernet.linkStatus() == LinkON)
  {
    Serial.print("Connected with IP ");
    Serial.println(Ethernet.localIP());
  }
  else
  {
    Serial.println("Can't connected");
  }
}

// Define the callback function to handle server status acknowledgement
void networkStatusRequestCallback()
{
  // Set the network status
  fbdo.setNetworkStatus(Ethernet.linkStatus() == LinkON);
  stream.setNetworkStatus(Ethernet.linkStatus() == LinkON);
}

// Define the callback function to handle server connection
void tcpConnectionRequestCallback(const char *host, int port)
{

  // You may need to set the system timestamp to use for
  // auth token expiration checking.

  if (timestamp == 0)
  {
    timestamp = ntpClient.getTime(2000 /* wait 2000 ms */);

    if (timestamp > 0)
      Firebase.setSystemTime(timestamp);
  }

  Serial.print("Connecting to server via external Client... ");
  if (!ssl_client.connect(host, port))
  {
    Serial.println("failed.");
    return;
  }
  Serial.println("success.");
}

// Define the callback function to handle server connection
void tcpConnectionRequestCallback2(const char *host, int port)
{

  // You may need to set the system timestamp to use for
  // auth token expiration checking.

  if (timestamp == 0)
  {
    timestamp = ntpClient.getTime(2000 /* wait 2000 ms */);

    if (timestamp > 0)
      Firebase.setSystemTime(timestamp);
  }

  Serial.print("Connecting to server via external Client2... ");
  if (!ssl_client2.connect(host, port))
  {
    Serial.println("failed.");
    return;
  }
  Serial.println("success.");
}

void streamCallback(FirebaseStream data)
{
  Serial_Printf("sream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
                data.streamPath().c_str(),
                data.dataPath().c_str(),
                data.dataType().c_str(),
                data.eventType().c_str());
  printResult(data); // see addons/RTDBHelper.h
  Serial.println();

  // This is the size of stream payload received (current and max value)
  // Max payload size is the payload size under the stream path since the stream connected
  // and read once and will not update until stream reconnection takes place.
  // This max value will be zero as no payload received in case of ESP8266 which
  // BearSSL reserved Rx buffer size is less than the actual stream payload.
  Serial_Printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());

  // Due to limited of stack memory, do not perform any task that used large memory here especially starting connect to server.
  // Just set this flag and check it status later.
  dataChanged = true;
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

  if (!stream.httpConnected())
    Serial_Printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void setup()
{

  Serial.begin(115200);

  networkConnection();

  Serial_Printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  /* fbdo.setExternalClient and fbdo.setExternalClientCallbacks must be called before Firebase.begin */

  /* Assign the pointer to global defined external SSL Client object */
  fbdo.setExternalClient(&ssl_client);

  /* Assign the required callback functions */
  fbdo.setExternalClientCallbacks(tcpConnectionRequestCallback, networkConnection, networkStatusRequestCallback);

  /* Assign the pointer to global defined  external SSL Client object */
  stream.setExternalClient(&ssl_client2);

  /* Assign the required callback functions */
  stream.setExternalClientCallbacks(tcpConnectionRequestCallback2, networkConnection, networkStatusRequestCallback);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  Firebase.begin(&config, &auth);

  if (!Firebase.RTDB.beginStream(&stream, "/test/stream/data"))
    Serial_Printf("sream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);
}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    count++;
    FirebaseJson json;
    json.add("data", "hello");
    json.add("num", count);
    Serial_Printf("Set json... %s\n\n", Firebase.RTDB.setJSON(&fbdo, "/test/stream/data/json", &json) ? "ok" : fbdo.errorReason().c_str());
  }

  if (dataChanged)
  {
    dataChanged = false;
    // When stream data is available, do anything here...
  }
}
