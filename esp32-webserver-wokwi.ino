#include <WiFi.h>
#include <WebServer.h>

// ---------- Wi-Fi ----------
#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL  6

// ---------- Hardware ----------
const int LED1 = 26;
const int LED2 = 27;

// ---------- Estados dos LEDs ----------
bool led1Ligado = false;
bool led2Ligado = false;

// ---------- Servidor HTTP ----------
WebServer server(80);

// --------------------------------------------------
// Atualiza os pinos físicos de acordo com as variáveis
// --------------------------------------------------
void atualizarLeds() {
  digitalWrite(LED1, led1Ligado ? HIGH : LOW);
  digitalWrite(LED2, led2Ligado ? HIGH : LOW);
}

// --------------------------------------------------
// Converte bool para texto
// --------------------------------------------------
String textoEstado(bool estado) {
  if (estado) {
    return "LIGADO";
  } else {
    return "DESLIGADO";
  }
}

// --------------------------------------------------
// Monta a página HTML enviada ao navegador
// --------------------------------------------------
String gerarPagina() {
  String html = "";

  html += "<!DOCTYPE html>";
  html += "<html lang='pt-BR'>";
  html += "<head>";
  html += "  <meta charset='UTF-8'>";
  html += "  <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "  <title>ESP32 Web Server</title>";
  html += "  <style>";
  html += "    body { font-family: Arial, sans-serif; text-align: center; margin-top: 40px; }";
  html += "    .card { max-width: 400px; margin: auto; padding: 20px; border: 1px solid #ccc; border-radius: 12px; }";
  html += "    .linha { margin: 20px 0; }";
  html += "    .botao { display: inline-block; padding: 12px 20px; margin: 5px; ";
  html += "             text-decoration: none; color: white; border-radius: 8px; font-weight: bold; }";
  html += "    .on  { background-color: #2e7d32; }";
  html += "    .off { background-color: #c62828; }";
  html += "  </style>";
  html += "</head>";
  html += "<body>";
  html += "  <div class='card'>";
  html += "    <h1>ESP32 Web Server</h1>";

  html += "    <div class='linha'>";
  html += "      <h2>LED 1</h2>";
  html += "      <p>Estado atual: <strong>" + textoEstado(led1Ligado) + "</strong></p>";
  html += "      <a class='botao on' href='/led1/on'>Ligar</a>";
  html += "      <a class='botao off' href='/led1/off'>Desligar</a>";
  html += "    </div>";

  html += "    <div class='linha'>";
  html += "      <h2>LED 2</h2>";
  html += "      <p>Estado atual: <strong>" + textoEstado(led2Ligado) + "</strong></p>";
  html += "      <a class='botao on' href='/led2/on'>Ligar</a>";
  html += "      <a class='botao off' href='/led2/off'>Desligar</a>";
  html += "    </div>";

  html += "  </div>";
  html += "</body>";
  html += "</html>";

  return html;
}

// --------------------------------------------------
// Envia a página principal
// --------------------------------------------------
void enviarPagina() {
  server.send(200, "text/html", gerarPagina());
}

// --------------------------------------------------
// Rotas do LED 1
// --------------------------------------------------
void ligarLed1() {
  led1Ligado = true;
  atualizarLeds();

  Serial.println("LED 1 ligado");
  enviarPagina();
}

void desligarLed1() {
  led1Ligado = false;
  atualizarLeds();

  Serial.println("LED 1 desligado");
  enviarPagina();
}

// --------------------------------------------------
// Rotas do LED 2
// --------------------------------------------------
void ligarLed2() {
  led2Ligado = true;
  atualizarLeds();

  Serial.println("LED 2 ligado");
  enviarPagina();
}

void desligarLed2() {
  led2Ligado = false;
  atualizarLeds();

  Serial.println("LED 2 desligado");
  enviarPagina();
}

// --------------------------------------------------
// Caso a rota não exista
// --------------------------------------------------
void paginaNaoEncontrada() {
  server.send(404, "text/plain", "Rota nao encontrada.");
}

// --------------------------------------------------
// Conexão Wi-Fi
// --------------------------------------------------
void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

// --------------------------------------------------
// Setup
// --------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  atualizarLeds();

  conectarWiFi();

  // Página principal
  server.on("/", enviarPagina);

  // Rotas do LED 1
  server.on("/led1/on", ligarLed1);
  server.on("/led1/off", desligarLed1);

  // Rotas do LED 2
  server.on("/led2/on", ligarLed2);
  server.on("/led2/off", desligarLed2);

  // Rota inexistente
  server.onNotFound(paginaNaoEncontrada);

  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

// --------------------------------------------------
// Loop principal
// --------------------------------------------------
void loop() {
  server.handleClient();
}