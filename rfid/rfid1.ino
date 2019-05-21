//Programa : Leitor RFID

//DEFINES
#define DEBUG

// Bibliotecas
#include <SPI.h>
#include <MFRC522.h>

//GLOBALS
//Numero de leitura de RFIDs
const byte numReaders = 3;
//Pino slave de cada RFID
const byte ssPins[] = {2,3,4};
//Compartilham o mesmo Pino Reset
const byte resetPin = 8;
//Inicializa um array de MFRC522 instancias que representam cada leitor
MFRC522 mfrc522[numReaders];
//Sequência de tags para resolver o puzzle
const String correctIDs[] = {""};
//As tags IDs detectada atualmente
String currentIDs[numReaders];
//A saída para a resolução do puzzle
const byte lockPin = A0;


void setup() 
{
  #ifdef DEBUG
  //Inicializa canal de comunicações serial com o PC
  Serial.begin(9600);
  Serial.println(F("Comunicação Serial inicializado"));
  #endif

  //Setar a trava do puzzle
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);

  //Inicializa o SPI bus
  SPI.begin();

  for(uint8_t i=0; i<numReaders; i++){

    //Inicializa os leitores
    mfrc522[i].PCD_Init(ssPins[i], resetPin);

    //Informação de debug para a tela serial
    Serial.print(F("Leitor #"));
    Serial.print(i);
    Serial.print(F(" inicializado no pino "));
    Serial.print(String(ssPins[i]));
    Serial.print(F(". Força da antena: "));
    Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Version : "));
    mfrc522[i].PCD_DumpVersionToSerial();

    //Delay antes da ativação do próximo leitor
    delay(100);
    
  }

  Serial.println(F("--- End Setup ---"));
}

String dump_byte_array(byte *buffer, byte bufferSize) {

  String conteudo = "";
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    conteudo.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(buffer[i], HEX));
  }
  
  return conteudo;
}
 
void loop() 
{

  //Assumindo que o puzzle está resolvido
  boolean puzzleSolved = true;

  //Assumindo que as tags não mudaram desde a ultima leitura
  boolean changedValue = false;

  //loop através de cada leitor
  for(uint8_t i=0; i<numReaders;i++){

    //Inicialização do sensor
    mfrc522[i].PCD_Init();

    //String com a ID de cada sensor
    String readRFID = "";

    //Se o sensor detectar uma tag e libera a leitura
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()){
      //Extrai o ID da tag
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }

    //Se a leitura atual é o mesmo do último
    if(readRFID != currentIDs[i]){
      //set a flag para mostrar que o estado do puzzle mudou
      changedValue = true;
      //Atualiza os valores armazenados dos IDs
      currentIDs[i] = readRFID;

      //Se falhar na combinação de IDs
      if(currentIDs[i] != correctIDs[i]){
        //O puzzle está errado
        puzzleSolved = false;
      }

      //Halt PICC
      mfrc522[i].PICC_HaltA();
      //Parar encriptação do PCD
      mfrc522[i].PCD_StopCrypto1();
    }

    //Se a changedValue está setada, ao menos um sensor mudou
    if(changedValue){
      //Imprime para o serial o estado dos sensores
      Serial.print(F("Leitor #"));
      Serial.print(String(i));
      Serial.print(F(" no pino #"));
      Serial.print(String(ssPins[i]));
      Serial.print(F(". Flag detectada: "));
      Serial.print(currentIDs[i]);
    }
    Serial.println(F("---"));
    delay(1000);
  }
  
}
