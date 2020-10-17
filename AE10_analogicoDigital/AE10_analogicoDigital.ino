/*
 * ANALÓGICO e DIGITAL
 * 
 * Neste exemplo, utilizamos um potenciômetro, uma chave (botão ou interruptor), e dois LEDs 
 * para compreender o uso de analogRead(), analogWrite(), digitalRead() e digitalWrite().
 * 
 * Repositório: https://github.com/mardefronteira/artefatoseletronicos
 * 
 * \\ ARTEFATOS ELETRÔNICOS 
 * por Marcela Mancino
 * Outubro, 2020
 */
 
// declarar constantes dos pinos nos quais estão conectados os componentes
const int pinoPot = A2; // pino analógico leva um "A" à frente, mesmo sendo declarado como número inteiro
const int pinoChave = 2;
const int pinoLedAzul = 10; // deve ser um pino PWM
const int pinoLedVermelho = 9;

// declarar variáveis para armazenar os valores da chave e potenciômetro
int statusChave;
int valorPot;

void setup() {
  // definir se os pinos serão usados como entradas ou saídas
  pinMode( pinoPot, INPUT ); // não é necessário declarar pinos analógicos, mas é uma boa prática
  pinMode( pinoChave, INPUT );
  pinMode( pinoLedAzul, OUTPUT );
  pinMode( pinoLedVermelho, OUTPUT );

  // iniciar comunicação serial
  Serial.begin(9600);
}

void loop() {
  // ler (receber) os valores da chave e potenciômetro, e atribuí-los às respectivas variáveis
  statusChave = digitalRead( pinoChave ); // valor digital (HIGH/LOW)
  valorPot = analogRead( pinoPot ); // valor analógico (0-1023)

  // modificar o brilho dos LEDs de acordo com os valores recebidos
  digitalWrite(pinoLedVermelho, statusChave); // LED estará ligado (HIGH) ou desligado (LOW)
  analogWrite(pinoLedAzul, valorPot / 4); // analogWrite() só envia valores entre 0-255

  // ver valores no monitor
  Serial.print("chave: ");
  Serial.print(statusChave);
  Serial.print(", potenciômetro: ");
  Serial.print(valorPot);
  Serial.print(", brilhoAzul: ");
  Serial.println(valorPot / 4);
}
