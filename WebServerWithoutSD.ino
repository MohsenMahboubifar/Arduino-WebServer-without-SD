#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

#define IP IPAddress(192,168,0,129)
#define req_len 500

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte req[req_len];
int req_index = 0;

EthernetServer server(80);       // create a server at port 80

           // index into HTTP_req buffer
bool root = false;               // login indicator

byte StrContains(char *str, char *sfind)
{
    //byte len = strlen(str); 
    #define LEN strlen(str) 
    byte found = 0;
    byte index = 0;
      
    if (strlen(sfind) > LEN) return 0;
    while (index < LEN) 
    {
        if (str[index] == sfind[found]) 
        {
            found++;
            if (strlen(sfind) == found) return index;    
        }
        else found = 0;
        index++;
    }
    return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // for debugging    
    //if(!Ethernet.begin(mac))
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
      char ch;
      while(client.connected())
      {
        if(client.available())
        {
          ch=client.read();
          req[req_index++] = ch;
          Serial.print(ch);
        }
        if(ch=='\n')
        {
          if(StrContains(req, "GET /"))
          {
            Serial.println("Server is available!");
            Serial.println(millis());
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connnection: close");
            client.println();
            client.print("<html><head><title>IP : ");
            client.print(Ethernet.localIP());
            client.print("</title></head> <body>b</body></html>");
            delay(5);
            client.stop();
            delay(5);
          }
        }
      }
    }
  }
delay(5000);
}
