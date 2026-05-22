// Onboard Module
#define RX 17
#define TX 16
#define ESTOP 27 // HIGH: Not EStopped, LOW: EStopped

// #define DEBOUNCE_LIMIT 8
// unsigned int debounce_count = 0;
// char filter_data = 'h';

unsigned long watchdog = 0; // Current time since last ping
unsigned long last_ping = 0; // Time of last ping
bool estopped = false;

void setup() {
  //Serial.begin(9600);
  Serial2.begin(115200, SERIAL_8N1, RX, TX);
  pinMode(ESTOP, OUTPUT);
  digitalWrite(ESTOP, LOW);
}

void loop() {
  // Update Watchdog Time
  watchdog = millis() - last_ping;
  // Query XBEE
  if (Serial2.available()) {
    char data = Serial2.read();
    switch (data) {
      case 'h': // "Hey there"
        last_ping = millis();
        //Serial.println("h");
        if (estopped)
        {
          digitalWrite(ESTOP, HIGH);
          estopped = false;
        }
        break;
    }
  }

  // if (data == filter_data)
  //   debounce_count += 1;
  // else
  //   debounce_count = 0;

  // if (debounce_count >= DEBOUNCE_LIMIT)
  // {
  //   last_ping = millis();
  //   if (estopped)
  //   {
  //     digitalWrite(ESTOP, HIGH);
  //     estopped = false;
  //   }
  //   filter_data = data;
  // }

  // Determine if we need to stop based on Watchdog Time
  // TODO: Determine best timeout time based on latency
  if (watchdog > 175 && !estopped) { 
    digitalWrite(ESTOP, LOW);
    //Serial.print("Watchdog activated, delaytime: ");
    //Serial.println(watchdog);
    estopped = true;
  }
}
