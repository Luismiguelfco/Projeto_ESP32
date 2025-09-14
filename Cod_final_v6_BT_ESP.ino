
/* Add IRremote.hpp ===> EEPROM.h ===> 01_Variables ===> 02_IR_Pin_Def ===> 03_EEPROM_Address ===> 04_Functions 

 *        switch (Buffer[4]){                           // Compara o Buffer [4]
 *        
 *           Buffer04_Relay     = 0x50;
 *           Buffer04_TV        = 0x51;
 *           Buffer04_AC        = 0x52;
 *           Buffer04_Radio     = 0x53;
 *           Buffer04_SD        = 0x54;
 *           Buffer04_Bluetooth = 0x55;
 *        
       
 */

//#include <Arduino.h>
#include <IRremote.hpp>
#include <DWIN.h>
#include <RDA5807.h> 
#include <Preferences.h>
#include "ESP_I2S.h"
//#include "BluetoothA2DPSink.h"

/*-------------- Carrega as paginas auxiliares ---------*/
#include "01_Variables.h"
//#include "03_EEPROM.h"
#include "02_IR_Pin_Def.h"
#include "04_Functions_Relay.h"
#include "05_Functions_Radio.h"
#include "06_Functions_SD.h"
#include "07_Gen_Functions.h"


      void setup() {
          setup_relay();
          setup_radio();
          setup_SD();
//          i2s.setPins(I2S_BCLK, I2S_LRC, I2S_DOUT);
//          if (!i2s.begin(I2S_MODE_STD, 44100, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO, I2S_STD_SLOT_BOTH)) {
//          Serial.println("Failed to initialize I2S!");
//          }
//          a2dp_sink.start("Bluetooth");
          
          IrSender.begin(IR_SEND_PIN);
          pinMode(config_button, INPUT);
          config_bt = digitalRead(config_button); 
              
          Serial.begin(115200);
          Serial.println("Iniciando");

          hmi.echoEnabled(false);
          hmi.hmiCallBack(onHMIEvent);
          hmi.setPage(1);
          
               }
 
        
        void loop() 
        {
          hmi.listen();
          if (Play) 
          {
           audio.loop();
           if (Play && !audio.isRunning()) 
            {  musicaAtual = (musicaAtual + 1) % musicas.size();
              play_music(pastas);
            }
          }
        }

    
