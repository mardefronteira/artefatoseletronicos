#include "Mouse.h"
#include "Keyboard.h"

const int numBotoes = 5;
const int botoes [] = { 7,6,5,4,2 };
int estadoBotoes [numBotoes];

const int numPots = 2;
const int pots [] = { A9, A8 };
int estadoPots [numPots];

/*
const int pessoas [] = {cachorro, gato, galo}
int cidades [] = {latido, miado, cacareja}
pessoas[0] // cachorro
cidades[0] // latido
*/

const int seguranca = 10;
int estadoSeguranca;

void setup() {
  // for (estado inicial do índice; condicional; incremento)
  for ( int i = 0; i < numBotoes; i++ ) {
    pinMode( botoes[i], INPUT_PULLUP );
  }
  for ( int i = 0; i < numPots; i++ ) {
    pinMode( pots[i], INPUT );
  }
  
  pinMode( seguranca, INPUT_PULLUP );

  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  estadoSeguranca = digitalRead( seguranca );
  if ( estadoSeguranca == LOW ) {
    // atribuindo estados dos componentes às listas de estados
    for ( int i = 0; i < numBotoes; i++ ) {
     estadoBotoes[i] = digitalRead(botoes[i]);
    }
    for (int i = 0; i < numPots; i++ ) {
      estadoPots[i] = analogRead(pots[i]);
    }

    // mexer o mouse de acordo com o potenciômetro
    int mouseX = map(estadoPots[0], 0, 1023, -5, 5);
    int mouseY = map(estadoPots[1], 0, 1023, -5, 5);
    Mouse.move(mouseX, mouseY);   

    char escrever [] = {'o','i','e','r','s'};
    for ( int i = 0; i< numBotoes; i++ ) {
      if ( estadoBotoes[i] == LOW ) {
        Keyboard.write(escrever[i]);
      }
    }
   
    // verificação de valores
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
  }
}
