/* Author: Sanket Jain
 * Project: Environment Sensing and Monitoring
 * 
 * 
 * 
*/
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
#include <ESP8266WiFi.h>                                                                  //ESP8266 WiFi Library                                                               DECLARATIONS
#include <PubSubClient.h>                                                                 //MQTT Library (Download in Library Manager) 
#include <DHT.h>                                                                          //DHT 11 Sensor Library
#define DHTPIN 4                                                                          //DHT Sensor Data Input Pin
const int ledPin = 16;                                                                    //LED Pin for NodeMCU

const char* ssid = "YOUR_WIFI_SSID";                                                      //Your Wi-Fi SSID
const char* wifi_password = "YOUR_WIFI_PASSWORD";                                         //Your WiFi password
const char* mqtt_server = "MQTT_SERVER_ADDRESS";                                          //Address of your RaspberryPi (MQTT Server), if not Pi then whatever device you're using
const char* mqtt_topic = "SUB_TOPIC_NAME";                                                //Subscribing Topic
const char* mqttp_topic = "PUB_TOPIC_NAME";                                               //Publishing Topic
const char* mqtt_username = "YOUR_MQTT_USERNAME";                                         //Username of MQTT service
const char* mqtt_password = "YOUR_MQTT_PASSWORD";                                         //Password of MQTT service
const char* clientID = "NODE_NAME";                                                        //Name of your Node

DHT dht(DHTPIN, DHT11);                                                                   //Create DHT class object
WiFiClient wifiClient;                                                                    //Create Wifi Class object    
PubSubClient client(mqtt_server, 1883, wifiClient);                                       //Create MQTT class object
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
void ReceivedMessage(char* topic, byte* payload, unsigned int length) {                   //Callback function                                                               CALLBACK FUNCTION
  String msg;
  char* mesg;
  for(int i = 0; i<length; i++){
    Serial.print(char(payload[i]));                                                       //Convert single byte to character and print
    msg += (char)payload[i];                                                              //Add character to string
  }
  Serial.println();                                                                       //Print new line

  if(msg=="Initialize"){
    ledBlink(5);
  }
  if(msg=="On"){                                                                          //Trigger message condition loop
    //NOTE: In our project, all group members had one Pi and one Node only. 
    //If you're using one server and multiple nodes, you can change the trigger message
    //(coming from the server) for different nodes. 
    float h = dht.readHumidity();                                                         //Read humidity from sensor
    float t = dht.readTemperature();                                                      //Read temperature from sensor in Celsius
    float f = dht.readTemperature(true);                                                  //Read temperature from sensor in Fahrenheit (isFahrenheit = true)
    
    Serial.println(t);                                                                    //Print celsius temperature value
    
    if (isnan(h) || isnan(t) || isnan(f)) {                                               //if garbage values
      Serial.println(F("Failed to read from DHT sensor!"));         
      client.publish(mqttp_topic, "Sensor Failure");                                       //send Sensor Failure message to the server
      ledBlink(1);
      delay(3700);
    }
    client.publish(mqttp_topic, (String(t)+':'+String(h)).c_str());                       //sending sensor data to the server after formatting
    ledBlink(1);   
    delay(3700);
  }

  else if(msg=="Off"){                                                                    //if server code is off
    //NOTE: This is more of a broadcast message here. If you want to shut down particular
    //nodes, you can make different Off trigger messages also for different nodes.
  }
}
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
bool Connect() {                                                                          //funcntion to connect to MQTT server                                              CONNECT FUNCTION
  if (client.connect(clientID, mqtt_username, mqtt_password)) {                           //MQTT class object function to check if connected to server or not
      client.subscribe(mqtt_topic);                                                      //subscribe to a topic if connected
      return true;
    }
    else {
      return false;
  }
}
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
void setup() {                                                                            //                                                                                   SETUP FUNCTION
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, wifi_password);                                                        //Wifi Class object method, to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {                                                 //Wait until the connection has been confirmed before continuing
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  client.setCallback(ReceivedMessage);                                                     //Pass the callback function as parameter to this method, this is to call that function whenever message is received
  if (client.connect(clientID, mqtt_username, mqtt_password)) {                            //Connect to MQTT Broker
    Serial.println("Connected to MQTT Broker!");                                          
    client.subscribe(mqtt_topic);                                                          //Subscribe to MQTT topic
    ledBlink(3);
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

  dht.begin();                                                                             //Initialise DHT data reading
}
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
void loop() {                                                                              //                                                                                   MAIN LOOP
  if (!client.connected()) {                                                               //If client is not connected, connect again
    Connect();
  }
  client.loop();                                                                           //Class method to keep looking for messages
} 
/*__________________________________________________________________________________________________________________________________________________________________________________________*/
void ledBlink(int count){                                                                  //Function to blink LED light                                                   LED BLINK FUNCTION
  for(int i=0; i<count; i++){
    digitalWrite(ledPin, LOW);
    delay(300);
    digitalWrite(ledPin, HIGH);
    delay(300);
  }
}
