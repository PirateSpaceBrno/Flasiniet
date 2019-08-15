#include <SoftwareSerial.h>
#include <Entropy.h>

#define ARDUINO_RX 9//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 10//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0} ;

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_SET_VOLUME 0X06
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01
#define CMD_PLAY_WITHFOLDER 0X0F


int flasinetMusic[5] = {0X0101,0X0102,0X0103,0X0104,0X0105};
int mafiaMusic[14] = {0X0201,0X0202,0X0203,0X0204,0X0205,0X0206,0X0207,0X0208,0X0209,0X0210,0X0211,0X0212,0X0213,0X0214};
int teknoMusic[3] = {0X0301,0X0302,0X0303};


void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  Entropy.initialize();
  
  delay(500); //Wait chip initialization is complete
  sendCommand(CMD_SEL_DEV, DEV_TF); //select the TF card 
  sendCommand(CMD_SET_VOLUME, 0X1E); // set volume to 30
  
  Entropy.random(); //increase entropy
  delay(50); //wait for 50ms
  int song = mafiaMusic[Entropy.random(1,14)];
  sendCommand(CMD_PLAY_WITHFOLDER, song);
}
void loop() {
  
}

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]) ;
  }
} 
