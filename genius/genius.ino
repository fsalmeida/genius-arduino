#define ledVerde 8
#define ledVermelho 9
#define botaoVerde 2
#define botaoVermelho 3

const int numeroMaximoJogadas = 40;

int jogo[numeroMaximoJogadas];
boolean deveReiniciarJogo = true;
boolean deveApresentarJogo = true;
int level = 0;
int indiceJogada = 0;

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoVermelho, INPUT);

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);

  randomSeed(analogRead(0));
}

void loop() {

  if(deveReiniciarJogo){
    leBotao();
    piscarLeds(3);
    delay(2000);
    reiniciarJogo(); 
  }

  if(deveApresentarJogo)
    apresentarJogoNoLevelAtual();

  int botaoPressionado = leBotao();
  verificarJogada(botaoPressionado);
}

void verificarJogada(int botaoPressionado){
  boolean acertou = jogo[indiceJogada] == botaoPressionado;
  if(acertou){
    sinalizarAcerto(botaoPressionado);
    if(indiceJogada == level){
      avancarDeNivel();
      //TODO: Implementar final de jogo caso tenha chegado no level maximo..
    }else{
      indiceJogada++;
    }
  }else{
    sinalizarErro();
    deveReiniciarJogo = true;
  }
}

void avancarDeNivel(){
  indiceJogada = 0;
  level++;
  deveApresentarJogo = true;
  delay(1000);
}

void sinalizarErro(){
  piscarLeds(5);
}

void sinalizarAcerto(int botaoPressionado){
  piscarLed(botaoPressionado);
}

void apresentarJogoNoLevelAtual(){
  for(int indiceLevel = 0; indiceLevel <= level; indiceLevel++){
    piscarLed(jogo[indiceLevel]);
    delay(500);
  }
  deveApresentarJogo = false;
}

void reiniciarJogo(){
  level = 0;
  deveReiniciarJogo = false;
  deveApresentarJogo = true;
  sortearJogo();
}

void sortearJogo(){
  for(int jogada = 0; jogada < numeroMaximoJogadas; jogada++){
    jogo[jogada] = random(botaoVerde, botaoVermelho+1);
  }
}

int leBotao () {
  int result = -1;

  while (result == -1) {
    if (digitalRead(botaoVerde) == HIGH) {
      result = botaoVerde;    //posição 0
    }
    else if (digitalRead(botaoVermelho) == HIGH) {
      result = botaoVermelho;
    }
  }

  return result;
}

void piscarLed(int botao){
  int led;
  if(botao == botaoVerde)
    led = ledVerde;
  else
    led = ledVermelho;
    
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
}

void piscarLeds(int qtdVezes){
  for(int i = 0; i < qtdVezes; i++){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, HIGH);
    delay(200); 
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    delay(500);
  }
}
