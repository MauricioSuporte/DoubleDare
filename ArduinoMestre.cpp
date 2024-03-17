#define TEAM1_BUTTON_PIN 2 // Botão Time Vermelho
#define TEAM2_BUTTON_PIN 3 // Botão Time Azul
#define JUDGE_BUTTON_RESET_PIN 4 // Botão resetar pontuação
#define JUDGE_BUTTON_TEAM1_PIN 5 // Botão Adicionar ponto time Vermelho
#define JUDGE_BUTTON_TEAM2_PIN 6 // Botão Adicionar ponto time Azul
#define JUDGE_BUTTON_TURN_OFF 7 // Botão Apagar led e buzzer

#define TEAM1_LED_PIN 9 // LED vermelho
#define TEAM2_LED_PIN 8 // LED azul
#define BUZZER_PIN 10   // Pino do buzzer

int team1Score = 36; // Pontuação time Vermelho
int team2Score = 97; // Pontuação time Azul
const unsigned long debounceDelay = 3000; // Delay de debounce de 3 segundo
bool buttonPressed = false; // Se o botão dos times foi apertado ou não
unsigned long buttonPressedTime = 0; // Tempo em que botão dos times foi apertado

void setup() {
  pinMode(TEAM1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(TEAM2_BUTTON_PIN, INPUT_PULLUP);
  pinMode(JUDGE_BUTTON_RESET_PIN, INPUT_PULLUP);
  pinMode(JUDGE_BUTTON_TEAM1_PIN, INPUT_PULLUP);
  pinMode(JUDGE_BUTTON_TEAM2_PIN, INPUT_PULLUP);
  pinMode(JUDGE_BUTTON_TURN_OFF, INPUT_PULLUP);

  pinMode(TEAM1_LED_PIN, OUTPUT);
  pinMode(TEAM2_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  // Verifica se algum botão dos times foi pressionado
  if ((digitalRead(TEAM1_BUTTON_PIN) == HIGH || digitalRead(TEAM2_BUTTON_PIN) == HIGH) && !buttonPressed) {
    if (digitalRead(TEAM1_BUTTON_PIN) == HIGH) {
      digitalWrite(TEAM1_LED_PIN, HIGH); // Acende o LED vermelho
      Serial.println("Time vermelho apertou o botao!");
    }
    if (digitalRead(TEAM2_BUTTON_PIN) == HIGH) {
      digitalWrite(TEAM2_LED_PIN, HIGH); // Acende o LED azul
      Serial.println("Time azul apertou o botao!");
    }
    tone(BUZZER_PIN, 1000); // Liga o buzzer
    buttonPressed = true;
    buttonPressedTime = millis(); // Marca o tempo de pressionamento do botão
  }
  
  // Verifica se o juiz apertou o botão de desligar os led e buzzer ou se o tempo de espera de 3 segundos foi atingido
  if (digitalRead(JUDGE_BUTTON_TURN_OFF) == HIGH || (buttonPressed && millis() - buttonPressedTime >= 3000)) {
    digitalWrite(TEAM1_LED_PIN, LOW); // Desliga o LED vermelho
    digitalWrite(TEAM2_LED_PIN, LOW); // Desliga o LED azul
    noTone(BUZZER_PIN); // Desliga o buzzer
    buttonPressed = false; // Reseta o status do botão
    buttonPressedTime = millis(); // Reseta o horário que botão foi apertado
    Serial.println("Luzes e alertas foram desligados!");
  }
  
  // Verifica se o botão do juiz foi pressionado para resetar a pontuação
  if (digitalRead(JUDGE_BUTTON_RESET_PIN) == HIGH) {
    team1Score = 0;
    team2Score = 0;
    Serial.println("Juiz resetou os pontos!");
  }
  
  // Verifica se o botão do juiz foi pressionado para adicionar ponto ao Time 1
  if (digitalRead(JUDGE_BUTTON_TEAM1_PIN) == HIGH) {
    team1Score++;
    Serial.println("Juiz adicionou 1 ponto para o Time Vermelho!");
  }
  
  // Verifica se o botão do juiz foi pressionado para adicionar ponto ao Time 2
  if (digitalRead(JUDGE_BUTTON_TEAM2_PIN) == HIGH) {
    team2Score++;
    Serial.println("Juiz adicionou 1 ponto para o Time Azul!");
  }
  
  // Envie a pontuação atual pela comunicação serial
  Serial.print("Vermelho ");
  Serial.print(team1Score);
  Serial.print(" Azul ");
  Serial.println(team2Score);
}