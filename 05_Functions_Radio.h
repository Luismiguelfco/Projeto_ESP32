
RDA5807 radio;    //Cria o objeto "radio"


/*To do: 
 * 
 *Desabilitar outros dispostivos quando entrar no radio e vice e versa
 *Salvar Radio favorita na memoria flash
  */

 
 uint8_t   estacoes = 1;                                                                            //Posição das estações favoritas no array radio_fav (0,1,2,etc...)
 uint16_t  radio_fav [] = {8730, 10800, 10030, 10040, 10050, 10060, 10070, 10080, 10090, 10090};   //Estações favoritas 
 bool      flag_on = 0; //Flag para habilitar ou desabilitar o radio no botao on off




  /*=============Faz a configuração inicial do radio =======================*/  

          
           void setup_radio() {
            Wire.begin(21,22);
            radio.setup(); // Starts the receiver with default parameters
            radio.setFrequency(8730); // Tunes in 103.9 MHz  - Switch to your local favorite station
            radio.setVolume(6);
            radio.setMute(1);
          }                   
                             
  /*=============Mostra as informações do radio via serial =======================*/  
  
          void showStatus()
          {
//          char aux[80];
//          sprintf(aux, "\nYou are tuned on %u MHz | RSSI: %3.3u dbUv | Vol: %2.2u | Muted: %s\n", radio.getFrequency(), radio.getRssi(), radio.getVolume(), (radio.isMuted()) ? "Yes" : "No" );
//          Serial.print(aux);
           }


  /*=============Executa as ações do radio conforme botões pressionados na tela =======================*/
                                        
         void radio_actions (uint16_t bt_radio){ 

              //radio_actions (array_bt_controle_radio[i]); 
              switch (bt_radio){
              
              case bt1_t1:
              Serial.println("previous radio");
              if (estacoes > 0) estacoes = estacoes - 1;
              else  estacoes =  0;
              radio.setFrequency(radio_fav [estacoes]);
              showStatus();
              break;
              
              case bt2_t1:
              radio.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showStatus);
              Serial.println("Seek down");                               
              //                    Serial.println("next radio");
              //                    if (estacoes < 9) {estacoes = estacoes + 1;}
              //                    else {estacoes = 9;}
              //                    radio.setFrequency(radio_fav [estacoes]);
              //                    radio.setMute(0);
              //                    showStatus();
              break;
              
              case bt3_t1:
              flag_on = !flag_on;
              if (flag_on == 0) 
              {
              radio.setMute(1);
              //radio.powerDown();
              }
              else{
              radio.setMute(0);
              //radio.powerUp();
              }
              showStatus();
              break;
              
              case bt4_t1:
              radio.setVolumeUp();
              Serial.println("Vol +");
              showStatus();
              break;
              
              case bt5_t1:
              radio.setVolumeDown();
              Serial.println("Vol -");
              showStatus();
              break;
              
              case bt6_t1:
              radio.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN, showStatus);
              Serial.println("Seek down");                                 
              break;
              
              case bt7_t1:
              radio.seek(RDA_SEEK_WRAP, RDA_SEEK_UP, showStatus);
              Serial.println("Seek up");
              break; 
              
              case bt8_t1:
              radio_fav [estacoes]= radio.getFrequency() ; 
              break;
              }

        }

        
