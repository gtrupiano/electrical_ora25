// Remote Module
#define RX 17 //on ESP32-WROOM
#define TX 16 //on ESP32-WROOM

//const uint8_t RX = 3;
//const uint8_t TX = 1;

unsigned long sent_delay = 0;
unsigned long last_write = 0;

void setup() {
  Serial2.begin(115200, SERIAL_8N1, RX, TX);
  //Serial1.begin(9600);
}

void loop() {
  sent_delay = millis() - last_write;
  if (sent_delay >= 5) {
    last_write = millis();
    Serial2.write('h');
  }
}
