// Tifa Test 23/04/2015
#define SSID        "tifa"
#define password    "01005381961"
#include <ESP8266.h>
#include <SoftwareSerial.h>
//pin 7 Rx Pin 8 TX
SoftwareSerial myserial(7,8);
ESP8266 wifi(myserial);


void setup(void)
{
    // set baudrate to match module baud rate
   Serial.begin(9600);
   pinMode(7, INPUT);
   pinMode(8, OUTPUT);
    myserial.begin(9600);
    if(wifi.kick()){
    Serial.println("started");
    }else{
      Serial.println("error starting");
    }
      wifi.enableMUX();
    Serial.print("setup begin\n");
   // Serial.print(getVersion());
    // set operation to AP mode
     wifi.setOprToStationSoftAP();
     // intialise the ap with ssid and pw
     if(wifi.setSoftAPParam(SSID,password,6,3))
     {
         Serial.println("it is set param ok");
     }     
    //start tcp server server with port 8090
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
    }
    //connection time out 
    if (wifi.setTCPServerTimeout(1000)) { 
        Serial.print("set tcp server timout 1000 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
    Serial.println("Local IP:" +wifi.getLocalIP());
    

}

void loop(void)
{
uint8_t buffer[128] = {0};
uint8_t mode[1];//new part
mode[1]=0;
    uint8_t mux_id; 
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.println("]");
       /* 
        if(wifi.send(mux_id, buffer, len)) {
            Serial.print("send back ok\r\n");
        } else {
            Serial.print("send back err\r\n");
        }
        */
        
        //sending command to client to change sleep time mode is a declared buffer of size 1
       // len= length 
//        if(wifi.send(mux_id,mode,1)) {
//            Serial.print("change mode ok\r\n");
//        } else {
//            Serial.print("change mode err\r\n");
//        }
//        int tmp = mode[0];
//        if(tmp==0){
//          mode[0]=1;
//        }else{
//          mode[0]=0;
//        }
//        Serial.println(mode[0]);
//        Serial.print("Status:[");
//        Serial.print(wifi.getIPStatus().c_str());
//        Serial.println("]");
//    }
//    
}



