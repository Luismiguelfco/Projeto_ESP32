/*--- Pagina para definir variaveis de botões de todos os dispositivos----*/
  
  
  #define DEBAG 1               // Debugging: 1 - on, 0 - off
  #define config_button 0    //Botão de config do admin
  
  //I2SClass i2s;
  //BluetoothA2DPSink a2dp_sink(i2s);
  
  DWIN hmi(Serial2, 16, 17, 115200);
  /* Variaveis do Buffer [4] */
  
  #define Buffer04_Relay      0x50
  #define Buffer04_TV         0x51
  #define Buffer04_SD         0x52
  #define Buffer04_Radio      0x53
  #define Buffer04_AC         0x54
  #define Buffer04_Bluetooth  0x55
  
 
  bool      config_bt;
  //bool      Play = 0;
  uint16_t  vol_sd = 10;
  uint32_t  leitura;                  /*------- Variavel que armazena leitura do led do controle-------*/
  uint16_t  buffer04_value;
  uint16_t  buffer05_value;
  uint8_t   buffer08_value;
  const char*      pastas = "";
  


  /* Valores gerais dos botões das telas Dwin - Envia da tela para o ESP (Input)Buffer [5] */
  #define bt1_t1    0x00   //Botão 1
  #define bt2_t1    0x01   //Botão 2
  #define bt3_t1    0x02   //Botão 3
  #define bt4_t1    0x03   //Botão 4
  #define bt5_t1    0x04
  #define bt6_t1    0x05
  #define bt7_t1    0x06
  #define bt8_t1    0x07
  #define bt9_t1    0x08
  #define bt10_t1   0x09
  #define bt11_t1   0x010
  #define bt12_t1   0x011
  #define bt13_t1   0x012
  #define bt14_t1   0x013
  #define bt15_t1   0x014
  #define bt16_t1   0x016


 

/*Valores do botão do controle da TV - Output(Envia do Esp para a IR TV*/
  uint32_t out_tv_bt1  = 0x0000FF00; // Botão Canal +
  uint32_t out_tv_bt2  = 0xF20DFF00; // Botão Canal -
  uint32_t out_tv_bt3  = 0xF10EFF00; // Botão On
  uint32_t out_tv_bt4  = 0xE718FF00; // Botão <
  uint32_t out_tv_bt5  = 0xEA15FF00; // Botão Sair
  uint32_t out_tv_bt6  = 0xEB14FF00; // Botão ^ (seta p/ cima)
  uint32_t out_tv_bt7  = 0xE916FF00; // Botão v (seta p/ baixo)
  uint32_t out_tv_bt8  = 0xE619FF00; // Botão OK
  uint32_t out_tv_bt9  = 0xE619FF00; // Botão Off
  uint32_t out_tv_bt10 = 0xE619FF00; // Botão >
  uint32_t out_tv_bt11 = 0xE619FF00; // Botão Voltar
  uint32_t out_tv_bt12 = 0xE619FF00; // Botão Smart
  uint32_t out_tv_bt13 = 0xE619FF00; // Botão Vol +
  uint32_t out_tv_bt14 = 0xE619FF00; // Botão Vol -


  

  /*Valores do botão do controle do AC - Output (Envia do ESP para o IR AC*/
  uint32_t out_ac_bt1  = 0x0000; // Botão On
  uint32_t out_ac_bt2  = 0xF20D; // Botão Off
  uint32_t out_ac_bt3  = 0xF10E; // Botão Temp +
  uint32_t out_ac_bt4  = 0xE718; // Botão Temp -
  uint32_t out_ac_bt5  = 0xEA15;
  uint32_t out_ac_bt6  = 0xEB14;
  uint32_t out_ac_bt7  = 0xE916;
  uint32_t out_ac_bt8  = 0xE619;
  uint32_t out_ac_bt9  = 0xE619;
  uint32_t out_ac_bt10 = 0xE619;
  uint32_t out_ac_bt11 = 0xE619;
  uint32_t out_ac_bt12 = 0xE619;
  uint32_t out_ac_bt13 = 0xE619;
  uint32_t out_ac_bt14 = 0xE619;



  /*--------Arrays do Buffer[5]---------------*/
   /* Array de Valores hexadecimais dos botões da tela no Buffer 5 -  Input*/
    uint16_t array_bt_tela[] ={
        bt1_t1,
        bt2_t1,
        bt3_t1,    
        bt4_t1,
        bt5_t1,
        bt6_t1,
        bt7_t1,
        bt8_t1,
        bt9_t1,
        bt10_t1,
        bt11_t1,
        bt12_t1,
        bt13_t1, 
        bt14_t1, 
        bt15_t1, 
        bt16_t1  };                                          
    
  uint32_t array_bt_controle_TV[] = {
        out_tv_bt1,     
        out_tv_bt2, 
        out_tv_bt3, 
        out_tv_bt4, 
        out_tv_bt5,
        out_tv_bt6,
        out_tv_bt7,
        out_tv_bt8,
        out_tv_bt9,
        out_tv_bt10,  
        }; // Array de Valores hexadecimais dos botões do controle da TV - Output
      
  uint32_t array_bt_controle_AC[] = { // Array de Valores hexadecimais dos botões do controle da AC - Output
        out_ac_bt1,     
        out_ac_bt2, 
        out_ac_bt3, 
        out_ac_bt4, 
        out_ac_bt5,
        out_tv_bt6,
        out_tv_bt7,
        out_tv_bt8,
        out_tv_bt9,
        out_tv_bt10,
        out_tv_bt11,  
        };                               
    
     
  
    int arraySize_bt_tela = sizeof(array_bt_tela) / sizeof(array_bt_tela[0]);   
