// Laboratorio 2 - Instrumentacion Biomedica III
// Checkpoint 1: Simulador de señal de pH con DAC ESP32

#define DAC_PIN 25   // DAC1 del ESP32

const float S = 0.05916;     // Pendiente de Nernst (V/pH)
const float Vbias = 1.65;    // Punto medio del DAC

void setup() {

  Serial.begin(115200);

  Serial.println("================================");
  Serial.println("Simulador de pH - Checkpoint 1");
  Serial.println("Ingrese un valor de pH entre 0 y 14");
  Serial.println("================================");

}

void loop() {

  if (Serial.available() > 0) {

    float pH = Serial.parseFloat();

    // Limpia datos restantes del puerto serie
    while (Serial.available()) {
      Serial.read();
    }


    if (pH >= 0 && pH <= 14) {

      // Ecuacion indicada en la guia:
      // Vin = Vbias - S*(pH - 7)

      float Vin = Vbias - S * (pH - 7);


      // Conversion de voltaje a DAC de 8 bits
      int valorDAC = round((Vin / 3.3) * 255);


      // Limites del DAC
      if (valorDAC < 0) {
        valorDAC = 0;
      }

      if (valorDAC > 255) {
        valorDAC = 255;
      }


      // Escritura en DAC
      dacWrite(DAC_PIN, valorDAC);


      Serial.print("pH ingresado: ");
      Serial.println(pH);


      Serial.print("Voltaje generado: ");
      Serial.print(Vin, 3);
      Serial.println(" V");


      Serial.print("Valor DAC: ");
      Serial.println(valorDAC);


      Serial.println("----------------------------");


    } else {

      Serial.println("ERROR: El pH debe estar entre 0 y 14");

    }

  }

}