/* https://github.com/schreibfaul1/ESP32-audioI2S/wiki */

#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"

// Definições dos pinos usados
#define SD_CS       5
#define SPI_MOSI    23
#define SPI_SCK     18
#define SPI_MISO    19

#define I2S_DOUT    25
#define I2S_LRC     26
#define I2S_BCLK    27


std::vector<String> musicas;
int musicaAtual = 0;
bool tocando = false;
bool Play = false;      // Já existe
bool isPaused = false;  // Novo controle de pausa

Audio audio;

    void setup_SD() {
    pinMode(SD_CS, OUTPUT);      
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);
    
    if (!SD.begin(SD_CS)) {
    Serial.println("Falha ao inicializar o cartão SD!");
    //while (true);
    }
    Serial.println("Cartão SD inicializado.");

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(10); // Volume de 0 até 21
    //audio.connecttoFS(SD,"/1.mp3");
    }
    
    
    // Função para tocar todas as músicas .mp3 da pasta
    void play_music(const char* pasta) 
      {
        // Se for uma nova pasta, recarrega músicas
        static String ultimaPasta = "";
        if (String(pasta) != ultimaPasta) {
          ultimaPasta = pasta;
          File dir = SD.open(pasta);
          if (!dir || !dir.isDirectory()) {
            Serial.println("Falha ao abrir diretório!");
            return;
          }
          Serial.println(pasta);
          File entry;
          musicas.clear();
          while ((entry = dir.openNextFile())) {
            if (!entry.isDirectory()) {
              String fileName = entry.name();
              if (fileName.endsWith(".mp3")) {
                musicas.push_back(fileName);
              }
            }
            entry.close();
          }
          dir.close();
        }
      
        if (musicas.empty()) {
          Serial.println("Nenhuma música encontrada!");
          return;
        }
      
        // Garante índice válido
        musicaAtual = musicaAtual % musicas.size();
      
        // Inicia reprodução
        String atual = musicas[musicaAtual];
        Serial.print("Tocando: ");
        Serial.println(atual);
        audio.connecttoFS(SD, atual.c_str());

   }



   void tocarMusicaAtual() {
  if (musicas.empty()) return;

  String nome = musicas[musicaAtual];
  Serial.print("Tocando: ");
  Serial.println(nome);
  audio.connecttoFS(SD, nome.c_str());
  tocando = true;
}
