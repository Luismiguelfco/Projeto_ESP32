
       
     bool isBuffer4Processed = false;       
     String endereco;



 /*========================Faz a leitura da Serial da tela===============================*/
            
//       void buffer_check (uint16_t buffer4, uint16_t buffer5)
//        {
//
//        }

      void onHMIEvent(String address,int lastByte,String message,String response)
        {  
          Serial.println("[ A : " + address + " | R : "+response+ " ]"); 
          buffer04_value = strtol((address.substring(0, 2)).c_str(), NULL, 16); // Converte para uint16_t a partir da string em hexadecimal
          buffer05_value = strtol((address.substring(2, 4)).c_str(), NULL, 16); // Converte para uint16_t a partir da string em hexadecimal
          buffer08_value = lastByte; 
          //Serial.println(buffer04_value,HEX);
          //Serial.println(buffer05_value,HEX);

          
          for (int i = 0; i <= arraySize_bt_tela; i++) /* Incrementa i enquanto não chegar no tamanho maximo do array */ 
          {                                                                                              
           if (buffer05_value == array_bt_tela[i])/* Buffer [5] 0x5A 0x00 0x00 0x00 0x51 [0x00]  */  
            {                
              switch (buffer04_value) 
              {     
/*-----------------Funções Relay---------------------*/                         
                case Buffer04_Relay:
                relay_on ();
                break;
                
/*-----------------Funções TV-------------------------*/   
                case Buffer04_TV:
                if (config_bt == HIGH)
                {
                  IrSender.sendNECRaw(array_bt_tela[i],IR_SEND_PIN);
                }               
                else
                { 
                  endereco = "out_tv_bt" + String(i);
                  uint32_t bt_value = ler_botao();
                  preferences.begin("flash_memory", false); // false = leitura e escrita
                  preferences.putUInt(endereco.c_str(), bt_value);
                  preferences.end();
                }
                
                break ;                                                     /* Envia a posição do botão no array e o endereço da EEPROM */
                
/*-----------------Funções AC-------------------------*/                 
                case Buffer04_AC:
                if (config_bt == HIGH)
                {
                  IrSender.sendNECRaw(array_bt_controle_AC [i],IR_SEND_PIN);
                }               
                else
                { 
                  endereco = "out_ac_bt" + String(i);
                  uint32_t bt_value = ler_botao();
                  preferences.begin("flash_memory", false); // false = leitura e escrita
                  preferences.putUInt(endereco.c_str(), bt_value);
                  preferences.end();
                }
                break ;                                                        /* Envia o valor do botão do controle e o endereço da EEPROM */           
                
/*-----------------Funções Radio----------------------*/  
               
                case Buffer04_Radio:
                radio_actions(buffer05_value);
                break ;              
                
/*-----------------Funções SD------------------------*/ 
                           
                case Buffer04_SD: 
//                a2dp_sink.end();          // Finaliza Bluetooth A2DP                                            
                radio.setVolume(0);
                radio.setMute(1);                                    
                switch (buffer05_value) 
                { 
                  case bt1_t1 :   //00
                  musicaAtual = (musicaAtual - 1 + musicas.size()) % musicas.size();
                  play_music (pastas);
                  break;
                  
                  case bt2_t1:  // Play / Pause
                    Play = !Play;
                
                    if (Play) {
                      if (isPaused) {
                        Serial.println("Resumindo...");
                        audio.pauseResume();  // Retoma
                        isPaused = false;
                      } else {
                        Serial.println("Play");
                        play_music(pastas);   // Começa do início
                      }
                    } else {
                      if (audio.isRunning()) {
                        Serial.println("Pausando...");
                        audio.pauseResume();  // Pausa
                        isPaused = true;
                      }
                    }
                  break;
                  
                  case bt3_t1 :   //02  Proxima
                  musicaAtual = (musicaAtual + 1) % musicas.size();
                  play_music (pastas);
                  break;
                  
                  case bt4_t1 :   //03  Vol +
                  vol_sd ++;
                  audio.setVolume(vol_sd);
                  break;

                  case bt5_t1 :   //04  Vol -
                  vol_sd --;
                  audio.setVolume(vol_sd);
                  break;
                       
                  case bt6_t1 :
                  pastas = "/Rock_Internacional";  // Caminho da pasta no SD
                  Play = 1;
                  play_music (pastas);
                  break;
                  
                  case bt7_t1 :
                  pastas = "/Rock_Nacional";  // Caminho da pasta no SD
                  Play = 1;
                  play_music (pastas);
                  break;
                  
                  case bt8_t1:
                  pastas = "/Sertanejo";  // Caminho da pasta no SD
                  Play = 1;
                  play_music (pastas);
                  break;
                  
                  case bt9_t1:
                  pastas = "/Forro";  // Caminho da pasta no SD
                  Play = 1;
                  play_music (pastas);
                  break;

                  case bt10_t1:
                  pastas = "/Forro";  // Caminho da pasta no SD
                  Play = 1;
                  play_music (pastas);
                  break;

                  case bt11_t1:
                  pastas = "/Forro";  // Caminho da pasta no SD
                   Play = 1 ;
                  play_music (pastas);
                  break;
                 }
               break;    //(buffer05_value)  


               
/*---------------Funções Bluetooth----------------*/                                  
//              case Buffer04_Bluetooth:
//                //audio.end();             // Desliga áudio SD
//                a2dp_sink.start("Bluetooth");
//                radio.setMute(1);
//                String command;
//                switch (buffer05_value)
//                {
//                  case bt1_t1 :
//                  a2dp_sink.play();
//                  break;
//                  
//                  case bt2_t1 :
//                  a2dp_sink.previous();
//                  break;
//                  
//                  case bt3_t1:
//                  a2dp_sink.next();
//                  break;
//                  
//                  case bt4_t1:
//                  break; //(buffer05_value)
//                } 
//              break;    //Buffer04_Bluetooth:
              
              }           //(buffer04_value)                           
            break;
           }           //if (buffer5 == array_bt_tela[i])   
          isBuffer4Processed = true;
         }  //for  
        }   //loop
