

/*-------------- Pinout ------------------------------ */

#define relay1 14      //Relé 1
#define relay2 13      //Relé 2
#define relay3 12     //Relé 3
#define relay4 15      //Relé 4
#define relay5 2      //Relé 5
#define relay6 4      //Relé 6

/*------------ Variavés de controle dos réles ---------------*/


const bool relayState = 0;                                 // 1 - Relé High, 0 - Relé Low
const byte relays_num = 6;                            // Numero de relés
byte relays[relays_num] = {relay1,relay2,relay3,relay4,relay5,relay6};   // Pinos dos relés


/*===============Função que seta os relés como output===================*/

        void setup_relay (){    /* Função para setar relés como output */
         pinMode(relay1, OUTPUT);
         pinMode(relay2, OUTPUT);
         pinMode(relay3, OUTPUT);
         pinMode(relay4, OUTPUT);
         pinMode(relay5, OUTPUT);
         pinMode(relay6, OUTPUT);

         digitalWrite(relay1, LOW); 
         digitalWrite(relay2, LOW);
         digitalWrite(relay3, LOW);
         digitalWrite(relay4, LOW);
         digitalWrite(relay5, LOW);
         digitalWrite(relay6, LOW);

        }


/*===============Função que aciona os relés===================*/
        void relay_on() {
         for (byte i = 0; i < relays_num; i++) {
            bool relayState = bitRead(buffer08_value, i);
            digitalWrite(relays[i], relayState);
          }
        }
