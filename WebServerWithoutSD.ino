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
      bool currentLineIsBlank = false;
      while(client.connected())
      {
        if(client.available())
        {
          ch=client.read();
          req[req_index++] = ch;
          Serial.print(ch);
        }
        if(ch=='\n' && currentLineIsBlank)
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
            client.print("</title>");
            client.println("<link  rel='shortcut icon' type='image/png' href=\"");
            client.println("data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAYABgAAD/2wBDAAIBAQIBAQICAgICAgICAwUDAwMDAwYEBAMFBwYHBwcGBwcICQsJCAgKCAcHCg0KCgsMDAwMBwkODw0MDgsMDAz/2wBDAQICAgMDAwYDAwYMCAcIDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAz/wAARCAAgACADASIAAhEBAxEB/8QAGAABAQADAAAAAAAAAAAAAAAACQgABgf/xAAsEAABAwMDBAAEBwAAAAAAAAABAgMEBQYRAAcSCAkTIRQVIjEWJjI5QXWy/8QAFgEBAQEAAAAAAAAAAAAAAAAABwgG/8QAJhEAAgEDAwMFAQEAAAAAAAAAAQIDBBEhBQYSABMxByJBUWFxof/aAAwDAQACEQMRAD8Aeq7xWDbkr5Cqmpq/EGN8wCzGJyMhfA8sFORkfYkHB+xknaPuAbjbw75fgGHbtkwao2/KYdlPSJS46DH5eQgABSs8DgHjn1nGrI0YPTVYcfczrvrVFlTq5S2pc+tYlUeqP02YwpK3SFIeZUlQ9j2kkpUPSgR61qtv00MtJVySRhmjQst7+bH/ADA6L99ajV02r6VBDO0Uc8oSTjY+3ktyAfmxPgi/30nyc8Ry/V/ONZocez/dG4HXdu5dFBvzeLeT4Kj0FFQjml3bKhOB4vobJJSTkYJ9H1nW2u9Y+7nbv7mEXaWtX9Xdztu6lVadEbTcZbkVBESeWkpeEhKQvzsrWoEZ8bobP0IKwWzWPcCNClQyEIx43wbH9H1/L9V1X+i1XDqVTotPVpJVQR90pZlDLYH2MQQWyMNx8+bAkLDo3OiT9yCd/YVv/T2kRu2hyLlt6TBi1apUN6QAEzoAZMhjCgTw8zbjfsApyUHAUcYOCJfvLt/2bsfGmXpBre9U2tNrUv8ALkht6qSXHVYXwDbAP1FRKiSE4JyQNI2h6jS0tNUpUtbuLxGCbYOT+Z/vUn7023qmq6ppsmmxB+xIHN2C3ytlF/nHkgDIz5savZb3+qXTtu/c1Wp1stXQalSI1KLCqu3T1odekpDITzQryFSwEkDHFOVH0k6s7bHtg7kdRHXsd/N8lW7brEKoxalS7Uo85c9xtURKBEbef4pQENqbbcUU8vKvn9LaTx1wftz9KN6Wzv3T5G6uzN4WfTGXIr8CdbtvpQ2mY3IbWlMv24r4fAOSlOR7JKR70w2j2h0mhNDDErs5VmY3BUXxxwcm2T+knyALVrv71D3FT7q1Ctjgip1qIY4ldJFmfiAe5Z1YopY8VNluoRSCGLE//9k=");
            client.println("\">");
            client.print("</head> <body>b</body></html>");
            delay(5);
            client.stop();
            delay(5);
          }
        }
        if(ch=='\n')
        {
          currentLineIsBlank = true;
        }
        else if(ch=='\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
  }
delay(5000);
}
