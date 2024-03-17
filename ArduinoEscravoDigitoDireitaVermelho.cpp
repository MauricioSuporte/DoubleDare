// Definição dos pinos para controlar cada segmento do display de 7 segmentos
#define SEGMENT_A 2
#define SEGMENT_B 3
#define SEGMENT_C 4
#define SEGMENT_D 5
#define SEGMENT_E 6
#define SEGMENT_F 7
#define SEGMENT_G 8

// Matriz para representar os segmentos de cada dígito
int digits[10][7] = {
 //A  B  C  D  E  F  G <- Segmento correspondente
  {1, 1, 1, 0, 1, 1, 1}, // 0
  {0, 0, 1, 0, 0, 1, 0}, // 1
  {1, 0, 1, 1, 1, 0, 1}, // 2
  {1, 0, 1, 1, 0, 1, 1}, // 3
  {0, 1, 1, 1, 0, 1, 0}, // 4
  {1, 1, 0, 1, 0, 1, 1}, // 5
  {1, 1, 0, 1, 1, 1, 1}, // 6
  {1, 0, 1, 0, 0, 1, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

char receivedMessage[30]; // Buffer para armazenar a mensagem recebida
int teamScore = 0; // Variável para armazenar a pontuação do time azul

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
  // Define os pinos como saídas
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);
  // Inicializa todos os segmentos desligados
  resetSegments();
}

void loop() {
  if (Serial.available() > 0) {
    // Limpa o buffer
    memset(receivedMessage, 0, sizeof(receivedMessage));
    // Lê a mensagem da serial
    Serial.readBytesUntil('\n', receivedMessage, sizeof(receivedMessage) - 1);
    // Interpretar a mensagem e extrair a pontuação do time vermelho
    teamScore = extractTeamScore(receivedMessage, "Vermelho");
    // Exibir o dígito mais à direita da pontuação do time vermelho
    displayDigit(teamScore % 10);
    
    // Propaga a pontuação para os outros arduinos
    Serial.println(receivedMessage);
  }
}

// Função para acender os segmentos correspondentes a um dígito
void displayDigit(int digit) {
  resetSegments(); // Reseta todos os segmentos
  // Liga os segmentos correspondentes ao dígito
  for (int i = 0; i < 7; i++) {
    if (digits[digit][i] == 1) {
      digitalWrite(i + 2, HIGH); // Os segmentos começam no pino 2
    }
  }
}

// Função para desligar todos os segmentos
void resetSegments() {
  for (int i = 2; i <= 8; i++) { // Os segmentos vão do pino 2 ao 8
    digitalWrite(i, LOW);
  }
}

// Função para extrair a pontuação do time especificado da mensagem
int extractTeamScore(char* message, const char* teamName) {
  char* p = strstr(message, teamName);
  if (p == NULL) {
    return 0; // Time não encontrado na mensagem
  }
  p += strlen(teamName); // Avança para além do nome do time
  // Encontra a pontuação que vem após o nome do time
  while (*p && !isdigit(*p)) {
    p++;
  }
  // Converte a pontuação para int
  return atoi(p);
}
