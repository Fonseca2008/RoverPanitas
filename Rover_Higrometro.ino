int Humedad;
const int seco=600;//falta configurarlo
const int moja=200;//Falta configurarlo
void setup() {
  Serial.begin(9600);
}

void loop() {
  HumSuelo();
}
void HumSuelo(){
  int Valor=analogRead(A0);
  int Humedad = map(Valor, moja, seco, 100, 0);
}
