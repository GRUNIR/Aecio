#include "Aecio.h"

void setup() {
  
  INTERVALOVERDE = 450;
  INTERVALOBLACK = 700;
  INTERVALOSENSORPRETO = 200;
  
  configuracoes();

}

void loop() {
  
  Velocidade();
  
  
  Leitura();
  Calibragem();
  //Linhapreta();

}
