//------------------------------------------------------------------------------------
#include <ESP8266WiFi.h>
//------------------------------------------------------------------------------------
// Defining I/O Pins
//------------------------------------------------------------------------------------
#define       LED0      2                                                                         // WIFI Module LED
#define       LED1      D5                                                     // Connectivity with Client #1
#define       LED2      D8                                                       // Connectivity with Client #2
#define       BUTTON    D2                                               // Connectivity Reinitiate Button

#define       MOT1      D0
#define       MOT12     D1
#define       MOT2      D3
#define       MOT21     D5
//------------------------------------------------------------------------------------
// BUTTON Variables
//------------------------------------------------------------------------------------
const String  nodeIdentifier = "node2";
//------------------------------------------------------------------------------------
// Authentication Variables
//------------------------------------------------------------------------------------
char*         TKDssid;
char*         TKDpassword;
IPAddress     TKDServer(192, 168, 4, 1);
WiFiClient    TKDClient;
//=================================================
// defines pins numbers
#define       trigPin   D6                                                                        // WIFI Module LED
#define       echoPin   D7
// defines variables
long duration;
int distance;
int j = 3;
int k = 1;
int z = 1;

void setup ()
{
  // Setting The Serial Port ----------------------------------------------
  Serial.begin(115200);                                                              // Computer Communication

  digitalWrite(MOT1, LOW);
  digitalWrite(MOT12, LOW);
  digitalWrite(MOT2, LOW);
  digitalWrite(MOT21, LOW);

  pinMode(MOT1, OUTPUT);
  pinMode(MOT12, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(MOT21, OUTPUT);
  pinMode(trigPin, OUTPUT);                                              // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                                                // Sets the echoPin as an Input
  // Setting The Mode Of Pins ---------------------------------------------
  pinMode(LED0, OUTPUT);                                                  // WIFI OnBoard LED Light
  pinMode(LED1, OUTPUT);                                  // Indicator For Client #1 Connectivity
  pinMode(LED2, OUTPUT);                                  // Indicator For Client #2 Connectivity
  pinMode(BUTTON, INPUT_PULLUP);                                        // Initiate Connectivity
  digitalWrite(LED0, !LOW);                                                            // Turn WiFi LED Off

  // Print Message Of I/O Setting Progress --------------------------------
  Serial.println("\nI/O Pins Modes Set .... Done");

  // Starting To Connect --------------------------------------------------
  WiFi.mode(WIFI_STA);                                              // To Avoid Broadcasting An SSID
  WiFi.begin("TAKEONE");                              // The SSID That We Want To Connect To

  // Printing Message For User That Connetion Is On Process ---------------
  Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

  // WiFi Connectivity ----------------------------------------------------
  // Checking For Connection
  CheckConnectivity();
}
//==============================================================
void loop()
{
  sendToServer("bot 1");
}

//To Check Connectivity of ESP8266wifi module:
void CheckConnectivity()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(LED0, !HIGH);
      delay(250);
      digitalWrite(LED0, !LOW);
      delay(250);
      Serial.print(".");
    }
    Serial.println("");
  }

  // Stop Blinking To Indicate Connected ----------------------------------
  digitalWrite(LED0, !HIGH);
  Serial.println("!-- Client Device Connected --!");

  // Printing IP Address --------------------------------------------------
  Serial.println("Connected To      : " + String(WiFi.SSID()));
  Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
  Serial.print  ("Server IP Address : ");
  Serial.println(TKDServer);
  Serial.print  ("Device IP Address : ");
  Serial.println(WiFi.localIP());

  // Conecting The Device As A Client -------------------------------------
  TKDRequest();
}
void TKDRequest()
{
  // First Make Sure You Got Disconnected
  TKDClient.stop();

  // If Sucessfully Connected Send Connection Message
  if (TKDClient.connect(TKDServer, 9001))
  {
    Serial.println    ("<" + nodeIdentifier + "-CONNECTED>");
    TKDClient.println ("<" + nodeIdentifier + "-CONNECTED>");
  }
}

Sending to Server:
void sendToServer(String str)
{
  TKDClient.println(str);
  //Read From server
  if (TKDClient.available() != 0)
  {
    String serverResponce = TKDClient.readStringUntil('\r');
    int ult = serverResponce.toInt();

    Serial.println(k);
    Serial.println(serverResponce);
    if (ult > 20)
    {
      k++;
    }
    if (ult > 20 && k == 8)
    {
      z = 2;
      Serial.println("done");
      digitalWrite(MOT1, HIGH);
      digitalWrite(MOT2, HIGH);
    }
    if (j > 1)
    {
      if (serverResponce == "stop" && z == 2)
      {
        digitalWrite(MOT1, LOW);
        digitalWrite(MOT2, LOW);
        digitalWrite(MOT12, HIGH);
        digitalWrite(MOT21, HIGH);
        j = 1;
        delay(7500);
        digitalWrite(MOT12, LOW);
        digitalWrite(MOT21, LOW);
      }
    }
  }
  TKDClient.flush();
  delay(2500);
}

//Program for Server

//Connectivity to WESP8266wifi module
//-- Libraries Included --------------------------------------------------------------
#include <ESP8266WiFi.h>
//------------------------------------------------------------------------------------
// Define I/O Pins
#define       LED0      2                                                 // WIFI Module LED
#define       LED1      D5                                                // Connectivity With Client #1
#define       LED2      D8                                                // Connectivity With Client #2
#define       BUTTON    D2                                               // Connectivity ReInitiate Button
//------------------------------------------------------------------------------------
// Authentication Variables
char*       TKDssid;                                                      // SERVER WIFI NAME
char*       TKDpassword;                                                 // SERVER PASSWORD
//------------------------------------------------------------------------------------
#define     MAXSC     4                                        // MAXIMUM NUMBER OF CLIENTS
WiFiServer  TKDServer(9001);                                  // THE SERVER AND THE PORT NUMBER
WiFiClient  TKDClient[MAXSC];                                 // THE SERVER CLIENTS
//==============================================================
String Message;
// boolean led1State = LOW;
// defines pins numbers
#define       trigPin   D6                                                  // WIFI Module LED
#define       echoPin   D7
#define       trigPin1   D0                                                 // WIFI Module LED
#define       echoPin1   D1

// defines variables
long duration;
int distance;
long duration1;
int dist1;
int j = 1;
int k = 1;
int e = 1;
void setup()
{
  // Setting The Serial Port
  Serial.begin(9600);                                                  // Computer Communication
  SetWifi("TAKEONE", "");
  pinMode(trigPin, OUTPUT);                                            // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                                              // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT);                                          // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);                                            // Sets the echoPin as an Input
  // Setting The Mode Of Pins
  pinMode(LED0, OUTPUT);                                                // WIFI OnBoard LED Light
  pinMode(LED1, OUTPUT);                                // Indicator For Client #1 Connectivity
  pinMode(LED2, OUTPUT);                                // Indicator For Client #2 Connectivity
  pinMode(BUTTON, INPUT_PULLUP);                                      // Initiate Connectivity

  // Print Message Of I/O Setting Progress
  Serial.println();
  Serial.println("I/O Pins Modes Set .... Done");
  // Setting Up A Wifi Access Point

}


void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  dist1 = duration1 * 0.034 / 2;
  IsClients(distance, dist1);
}

//Connectivity to Multiple Clients:
void IsClients(int dist, int sj)
{
  if (TKDServer.hasClient())
  {
    for (int i = 0; i < MAXSC; i++)
    {
      //find free/disconnected spot
      if (!TKDClient[i] || !TKDClient[i].connected())
      {
        if (TKDClient[i]) TKDClient[i].stop();
        TKDClient[i] = TKDServer.available();
        Serial.print("New Client : "); Serial.print(String(i + 1) + " - ");
        continue;
      }
    }
    // no free / disconnected spot so reject
    digitalWrite(LED1, HIGH);
    WiFiClient TKDClient = TKDServer.available();
    TKDClient.stop();
  }

  //check clients for data ------------------------------------------------------
  for (int i = 0; i < MAXSC; i++)
  {
    if (TKDClient[i] && TKDClient[i].connected())
    {
      if (TKDClient[i].available())
      {
        // If Any Data Was Available, Read It
        // Read From Client
        String clientRead = TKDClient[i].readStringUntil('\r');
        Serial.println(clientRead);
        Serial.println(i);

        if (dist < 40 || k == 2)
        {
          k = 2;
          TKDClient[i].println("stop");
          Serial.print("stop");
          TKDClient[i].flush();

        }

        if (clientRead == "on" && k == 1)
        {
          j++;

        }
        if (j > 1 && k == 1)
        {

          TKDClient[i].println(String(sj));
          TKDClient[i].flush();

        }
        if (j == 1)
        {
          TKDClient[i].println("start");
          TKDClient[i].flush();
        }
      }
    }
  }
}

//Set Wifi:
void SetWifi(char* Name, char* Password)
{
  // Stop Any Previous WIFI
  WiFi.disconnect();

  // Setting The Wifi Mode
  WiFi.mode(WIFI_AP_STA);
  Serial.println("WIFI Mode : AccessPoint Station");

  // Setting The Access Point
  TKDssid      = Name;
  TKDpassword  = Password;

  // Starting The Access Point
  WiFi.softAP(TKDssid, TKDpassword);
  Serial.println("WIFI < " + String(TKDssid) + " > ... Started");

  // Wait For Few Seconds
  delay(1000);

  // Getting Server IP
  IPAddress IP = WiFi.softAPIP();

  // Printing The Server IP Address
  Serial.print("AccessPoint IP : ");
  Serial.println(IP);

  // Starting Server
  TKDServer.begin();
  Serial.println("Server Started");
}
