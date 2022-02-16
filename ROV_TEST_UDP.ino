#include <Ethernet.h>
#include <EthernetUdp.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192,168,1,177);
IPAddress ipc(192,168,1,70);
unsigned int localPort = 8888;      // local port to listen on
uint8_t gripp=3;
uint8_t gripm=5;
uint8_t backp=14;
uint8_t backm=15;
uint8_t frontp=16;
uint8_t frontm=17;
 char jbuff[4];
void int2buff(int convint);
void test_all();
void movr1();
void movr2();
void movl1();
void movl2();
void swf();
void swb();
void swff();
void swfb();
void swfr();
void swfl();
void swbf();
void swbb();
void swbr();
void swbl();
void upf();
void dwnf();
void movf();
void movb();
void movr();
void movl();
void sp();
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged";        // a string to send back
uint8_t lv,fg;
// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  pinMode(gripp,OUTPUT);
  pinMode(gripm,OUTPUT);
  pinMode(backp,OUTPUT);
  pinMode(backm,OUTPUT);
  pinMode(frontp,OUTPUT);
  pinMode(frontm,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);

  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(frontm);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(gripm);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(frontpfrontp);  // ESPfrontp2 with Adafruit Featherwing Ethernet




  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
   
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
 
  }

  // start UDP
  Udp.begin(localPort);
}

void loop() {

 int packetSize = Udp.parsePacket();
  if (packetSize) {
    IPAddress remote = Udp.remoteIP();
    for (int i=0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < frontp) {
        Serial.print(".");
      }
    }
   // Serial.print(", port ");
   // Serial.println(Udp.remotePort());

   // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
   // Serial.println("Contents:");
   // Serial.println(packetBuffer);
   String buff=String(packetBuffer);

   if (buff.substring(0,1)=="W"){
      swf();
   }
     if (buff.substring(0,1)=="S"){
      swb();
   }
      if (buff.substring(0,1)=="O"){
      swff();
   }
         if (buff.substring(0,1)==";"){
      swfr();
   }
         if (buff.substring(0,1)=="K"){
      swfl();
   }
         if (buff.substring(0,1)=="L"){
      swfb();
   }
     if (buff.substring(0,1)=="M"){
      swbf();
   }
        if (buff.substring(0,1)=="/"){
      swbb();
   }
        if (buff.substring(0,1)==","){
      swbl();
   }
        if (buff.substring(0,1)=="."){
      swbr();
   }
      if (buff.substring(0,1)=="D"){
      movr();
   }
         if (buff.substring(0,1)=="T"){
      movl1();
   }
           if (buff.substring(0,1)=="J"){
      movl2();
   }
            if (buff.substring(0,1)=="U"){
      movr1();
   }
           if (buff.substring(0,1)=="G"){
      movr2();
   }
      if (buff.substring(0,1)=="A"){
      movl();
   }
         if (buff.substring(0,1)=="Q"){
      movf();
   }
      if (buff.substring(0,1)=="E"){
      movb();
   }
      if (buff.substring(0,1)=="V"){
      upf();
   }
      if (buff.substring(0,1)=="C"){
      dwnf();
   }
        if (buff.substring(0,1)=="Z"){
      sp();
   }
   if(buff.substring(1,2)=="o"){
analogWrite(gripp,100);
analogWrite(gripm,0);
   }
      if(buff.substring(1,2)=="c"){
analogWrite(gripp,0);
analogWrite(gripm,0);
   }
      if(buff.substring(1,2)=="n"){
analogWrite(gripm,100);
analogWrite(gripp,0);
   }

            if(buff.substring(2,3)=="2"){
 if(lv!=2){
                   digitalWrite(frontp,LOW);
    digitalWrite(backp,LOW);   
                     digitalWrite(frontm,LOW);
    digitalWrite(backm,LOW);  }
lv=2;
   }
            if(buff.substring(2,3)=="1"){
  
                  digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
lv=1;
   }
               if(buff.substring(2,3)=="0"){

   digitalWrite(frontm,HIGH);
    digitalWrite(backm,HIGH);
lv=0;
   }

       Udp.beginPacket(ipc, 97);
    Udp.write(packetBuffer);
    Udp.endPacket();

  }

}



void sp(){
digitalWrite(backp,LOW);
digitalWrite(backm,LOW);
digitalWrite(frontp,LOW);
digitalWrite(frontm,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(6,LOW);
digitalWrite(9,LOW);
}
void test_all(){
   for (int i=0;i<19;i++){
    sp();
     digitalWrite(i,HIGH);
     delay(500);
  }
}
 void swb(){
 
    sp();
     digitalWrite(frontp,HIGH);
    digitalWrite(backm,HIGH);
  }
   void swf(){
 
    sp();
    digitalWrite(frontm,HIGH);
    digitalWrite(backp,HIGH);
  }
     void swff(){
 
    sp();
    digitalWrite(frontm,HIGH);
    digitalWrite(backp,HIGH);
      digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  }
       void swfb(){
 
    sp();
    digitalWrite(frontm,HIGH);
    digitalWrite(backp,HIGH);
      digitalWrite(7,HIGH);
  digitalWrite(9,HIGH);
  }
         void swfr(){
 
    sp();
    digitalWrite(frontm,HIGH);
    digitalWrite(backp,HIGH);
      digitalWrite(6,HIGH);
  digitalWrite(9,HIGH);
  }
           void swfl(){
 
    sp();
    digitalWrite(frontm,HIGH);
    digitalWrite(backp,HIGH);
      digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  }
       void swbf(){
 
    sp();
    digitalWrite(frontp,HIGH);
    digitalWrite(backm,HIGH);
      digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  }
       void swbb(){
 
    sp();
       digitalWrite(frontp,HIGH);
    digitalWrite(backm,HIGH);
      digitalWrite(7,HIGH);
  digitalWrite(9,HIGH);
  }
         void swbr(){
 
    sp();
    digitalWrite(frontp,HIGH);
    digitalWrite(backm,HIGH);
      digitalWrite(6,HIGH);
  digitalWrite(9,HIGH);
  }
           void swbl(){
 
    sp();
    digitalWrite(frontp,HIGH);
    digitalWrite(backm,HIGH);
      digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  }
void upf(){
 
    sp();
     digitalWrite(frontm,HIGH);
    digitalWrite(backm,HIGH);
  }
   void dwnf(){
 
    sp();
    digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
  }
   void movl(){
 
    sp();
    if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

    digitalWrite(8,HIGH);
     digitalWrite(7,HIGH);
  }
     void movl1(){
 
    sp();
    if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

    digitalWrite(8,HIGH);
    // digitalWrite(7,HIGH);
  }
       void movl2(){
 
    sp();
    if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

    //digitalWrite(8,HIGH);
    digitalWrite(7,HIGH);
  }
     void movr(){
    sp();
        if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

   digitalWrite(6,HIGH);
     digitalWrite(9,HIGH);

  }
       void movr1(){
    sp();
        if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }
      digitalWrite(6,HIGH);
     //digitalWrite(9,HIGH);
       }
           void movr2(){
    sp();
        if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

   //digitalWrite(6,HIGH);
     digitalWrite(9,HIGH);

  }
  
   void movf(){
 
    sp();
   if (lv==1){
    digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }

  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  }
     void movb(){
 
    sp();
        if (lv==1){
     digitalWrite(frontp,HIGH);
    digitalWrite(backp,HIGH);
    }
 
  digitalWrite(7,HIGH);
     digitalWrite(9,HIGH);
  }





void int2buff(int convint){
  int x=convint;
 
    jbuff[0]=(x/1000);
    jbuff[1]=((x-jbuff[0]*1000)/100);
    jbuff[2]=((x-jbuff[0]*1000-jbuff[1]*100)/10);
    jbuff[frontp]=(x-jbuff[0]*1000-jbuff[1]*100-jbuff[2]*10);
    for(int i=0;i<4;i++)
    jbuff[i]+=48;

}
