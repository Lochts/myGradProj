
#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <EEPROM.h>
#include <ExtEEPROM.h>
#include <EEPROMAnything2.h>
#include <Wire.h>


const char* ssid = "123"; 
const char* password = "00000000";

const char* ssid2 = "JetSoft_1F"; 
const char* password2 = "0973808698";

const char* server    = "192.168.1.25"; //myserver 

SoftwareSerial ESP8266(3,4);
unsigned long previousMillis = 0;
const long interval = 2000;
int WiFi_Status = WL_IDLE_STATUS;


WiFiEspClient client;



void wifi_Setting(){
    ESP8266.begin(9600); 
    
    //初始化ESP模組
    WiFi.init(&ESP8266);

    Serial.print("進行WiFi設定!\r\n");
    do{
        Serial.println("WiFi 連接中 ...");
        WiFi_Status = WiFi.begin(ssid2, password2);
        delay(500); 
    } while (WiFi_Status != WL_CONNECTED);


    
    Serial.print("ＷiFi 連接成功!\r\n");
    Serial.print("IP 位址: ");       
    Serial.println(WiFi.localIP());
    Serial.print("SSID: ");     
    Serial.println(WiFi.SSID());
    Serial.println("WiFi 設定結束\r\n");


}
void setup(void) {
   // char somedata[] = "this is data from the eeprom"; 
    Wire.begin(); 

    Serial.begin(9600); 
   // i2c_eeprom_write_page(0x50, 0, (byte *)somedata, sizeof(somedata)); 

    delay(100); 

    Serial.println("Memory written");
    //設定序列埠傳輸速率(9600bps)
      

    //wifi設定
    wifi_Setting();

}
int datacounter = 0;
int addr=8; //first address
int goingdata;
int i;
String formattedDate;
void loop(void) {

    unsigned long currentMillis = millis();
    


    
    
    if (currentMillis - previousMillis >= interval) {
        EEPROM_readAnything(0,goingdata);
        Serial.print("goingdata: ");
        Serial.println(goingdata,DEC);
        addr = goingdata;
        
        previousMillis = currentMillis;
        // 讀取RSSI數值
        int rssi = WiFi.RSSI();
        
        Serial.print("RSSI: ");
        Serial.println(rssi,DEC);
           
        int rssidata;
        EEPROM_writeAnything(addr, rssi);
        addr +=8;
        datacounter++;
       /* i=0;
        if(goingdata/8 > 20)
        {
          i=goingdata/8-10;
        }
        else
        {
          i=1;
        }
        
        for(i;i<=goingdata/8;i++)
        {
          EEPROM_readAnything(i*8,rssidata);
          Serial.print("No.");
          Serial.print(i);
          Serial.print(" : ");
          Serial.print(rssidata);
          Serial.print("\n");
        }*/
        if(addr+8 > 250000)
        {
          EEPROM_writeAnything(0, 8);
        }
        else
        {
          EEPROM_writeAnything(0, addr);
        }
        
       
    }


    if(datacounter%10 == 0)
    {
        Serial.print("進行WiFi設定!\r\n");
        int ack = 0;
        do{
            ack++;
            Serial.println("WiFi 連接中 ...");
            WiFi_Status = WiFi.begin(ssid2, password2);
            delay(500); 
        } while ((WiFi_Status != WL_CONNECTED) &&  ack<2);
        
        Serial.print("ＷiFi 連接成功!\r\n");
        Serial.print("IP 位址: ");       
        Serial.println(WiFi.localIP());
        Serial.print("SSID: ");     
        Serial.println(WiFi.SSID());
        Serial.println("WiFi 設定結束\r\n");
        if (client.connect(server, 5678)) {
          
          Serial.println("Connected to server");
          
          char thedata[10][25];
          char rssi[10][10];
          char dot[2] = ".";
          char* endle = "\0";
          if(goingdata/8 > 20)
          {
            i=goingdata/8-10;
          }
          else
          {
            i=1;
          }   
          int rssidata;
          int j=0;
          for(i;i<=goingdata/8;i++)
          {
             EEPROM_readAnything(i*8,rssidata);
             itoa(rssidata,rssi[j],10);
             itoa(i,thedata[j],10);
             strcat(thedata[j],dot);
             
             strcat(thedata[j],rssi[j]);
             
             strcat(thedata[j],endle);
             j+=1;
            
                
            
          }
          for(i=0;i<10;i++)
          {
             delay(5);
             client.write(thedata[i]);
          }
          client.stop();
          // Make a HTTP request
        }
        delay(3000);

        Serial.print("進行WiFi設定!\r\n");
        do{
            Serial.println("WiFi 連接中 ...");
            WiFi_Status = WiFi.begin(ssid2, password2);
            delay(500); 
        } while (WiFi_Status != WL_CONNECTED);
        
        Serial.print("ＷiFi 連接成功!\r\n");
        Serial.print("IP 位址: ");       
        Serial.println(WiFi.localIP());
        Serial.print("SSID: ");     
        Serial.println(WiFi.SSID());
        Serial.println("WiFi 設定結束\r\n");
     
    }

    

}
