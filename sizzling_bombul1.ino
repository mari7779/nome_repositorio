#include <DHT.h>

// Definir o tipo do sensor
#define DHTTYPE DHT11

// Definir os pinos dos sensores
#define TEMP_PIN 4
#define HUMID_PIN 5

// Criar uma instância do objeto DHT
DHT dht(TEMP_PIN, DHTTYPE);

void setup() {
  // Iniciar o Serial Monitor
  Serial.begin(9600);

  // Iniciar o sensor DHT
  dht.begin();
}

void loop() {
  // Esperar um pouco entre as leituras
  delay(2000);

  // Ler a umidade
  float humidity = dht.readHumidity();
  
  // Ler a temperatura em Celsius
  float temperature = dht.readTemperature();

  // Verificar se as leituras falharam e sair se isso acontecer
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  // Exibir as leituras no Serial Monitor
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" C");
}
