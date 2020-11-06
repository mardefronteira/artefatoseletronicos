#include "MIDIUSB.h"

// variáveis para os botões
const int numBotoes = 5;
const int botoes [] = { 7,6,5,4,2 };
int estadoBotoes [numBotoes];
int ultimoEstadoBotoes [numBotoes];

// lista de notas a serem tocadas
const int notas [] = { 32,44,60,70,88 };

// variáveis para os potenciômetros
const int numPots = 2;
const int pots [] = { A9, A8 };
int estadoPots [numPots];
int ultimoEstadoPots [numPots];

// lista de parâmetros a serem controlados
const int controles [] = { 100, 111 }; // tanto faz, desde que sejam entre 0-120, e diferentes um do outro

// função para controlar parâmetros do software
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// função para ligar uma nota
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

// função para desligar uma nota
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  // definir modos dos pinos
  for ( int i = 0; i < numBotoes; i++ ) {
    pinMode( botoes[i], INPUT_PULLUP );
  }
  
  for ( int i = 0; i < numPots; i++ ) {
    pinMode( pots[i], INPUT );
  }
 
  // caso queira verificar os valores dos componentes, inicie a comunicação serial
  //  Serial.begin(9600);
}

void loop() {
    // atribuindo estados dos componentes às listas de estados
    for ( int i = 0; i < numBotoes; i++ ) {
     estadoBotoes[i] = digitalRead(botoes[i]);
    }
    for (int i = 0; i < numPots; i++ ) {
      // mapear potenciômentros para MIDI
      // para sensores analógicos é sempre bom checar qual é o valor mínimo e máximo dele
      estadoPots[i] = map(analogRead(pots[i]), 10, 1020, -1, 127); 
    }

    // verificando potenciômetros
    for ( int i = 0; i < numPots; i++ ) {
      
      // caso o estado tenha mudado (número diferente)
      if ( estadoPots[i] != ultimoEstadoPots[i] ) {
        
        // controlar de parâmetro
        controlChange(1, controles[i], estadoPots[i]);
        
        // enviar mensagem MIDI
        MidiUSB.flush();
      }
      
      // atualizar último estado do botão
      ultimoEstadoPots[i] = estadoPots[i];
    }

    
    // verificando botões
    for ( int i = 0; i < numBotoes; i++ ) {
      // caso o estado tenha mudado (pressionado / solto)
      if ( estadoBotoes[i] != ultimoEstadoBotoes[i] ) {
        
        if( estadoBotoes[i] == LOW ){ // ligue a nota caso esteja apertado
          noteOn( 3, notas[i], 127);   
        
        } else { // desligue a nota caso tenha sido solto
          noteOff( 3, notas[i], 0);
        
        }
        
        // enviar mensagem MIDI
        MidiUSB.flush();

        // atualizar último estado do botão
        ultimoEstadoBotoes[i] = estadoBotoes[i];
      }
    }
    
    // verificando valores no monitor serial
    /*
    Serial.print( "pots: " );
    for (int i = 0; i < numPots; i++ ) {
      Serial.print(estadoPots[i]);
      Serial.print(" ");
    }
    Serial.print( ", botões: " );
    for ( int i = 0; i < numBotoes; i++ ) {
      Serial.print(estadoBotoes[i]);
      Serial.print(" ");
    }
    Serial.println();
    */

}
