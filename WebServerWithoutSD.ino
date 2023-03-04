#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#define IP IPAddress(192,168,0,129)

EthernetServer server(22336);       // create a server at port 80
File webFile;                    // handle to files on SD card
char HTTP_req[40] = {0}; // buffered HTTP request stored as null terminated string
byte req_index = 0;              // index into HTTP_req buffer
bool root = false;               // login indicator
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // for debugging    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4))         // 4 - SS pin
    {
        Serial.println("ERROR - SD card initialization failed!");
        return;               // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    if(!Ethernet.begin(mac))
    {
      Ethernet.begin(mac, IP);  // initialize Ethernet device => Ethernet.begin(mac, ip);
    }
    Serial.println(Ethernet.localIP());
    server.begin();           // start to listen for clients
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available();  // try to get client
  
  if(client)
  {
    Serial.println("Client is here");
    if(client.available())
    {
      Serial.println("Server is available!");
      
    }
  }
}
