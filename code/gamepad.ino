#include <BleGamepad.h>

BleGamepad bleGamepad("Emoolii Remote", "DIY", 100);

const int A_button   = D10;
const int One_button = D9;
const int Two_button = D8;

const int Stick_X    = D0;
const int Stick_Y    = D1;

const int DEADZONE   = 200;  // raw ADC units around center (0-4095 scale)
const int SEND_DELTA = 150;  // minimum axis change (0-32767 scale) to send a report

const int AXIS_MAX   = 32767;
const int AXIS_MID   = 0;      // was 16384

int centerX = 16384, centerY = 16384;
int lastX = AXIS_MID, lastY = AXIS_MID;
bool lastConnected = false;

int readAvg(int pin) {
  long sum = 0;
  for (int i = 0; i < 8; i++) sum += analogRead(pin);
  return sum / 8;
}

int scaleAxis(int raw, int center) {
  int offset = raw - center;
  if (abs(offset) < DEADZONE) return 0;
  long v = (long)offset * AXIS_MAX / 2048;
  return constrain(v, -AXIS_MAX, AXIS_MAX);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(A_button,   INPUT_PULLUP);
  pinMode(One_button, INPUT_PULLUP);
  pinMode(Two_button, INPUT_PULLUP);

  analogReadResolution(12);
  delay(200);
  centerX = readAvg(Stick_X);   // keep the stick untouched at power-up
  centerY = readAvg(Stick_Y);
  Serial.printf("Stick center: X=%d Y=%d\n", centerX, centerY);
  
  bleGamepad.begin();
  Serial.println("BLE started, waiting for a connection...");
}

void loop() {
  bool connected = bleGamepad.isConnected();
  if (connected != lastConnected) {
    lastConnected = connected;
    Serial.println(connected ? "Connected" : "Disconnected");
  }

  bool changed = false;
  changed |= update(A_button,   BUTTON_1, "A");
  changed |= update(One_button, BUTTON_2, "1");
  changed |= update(Two_button, BUTTON_3, "2");

  int x = scaleAxis(readAvg(Stick_X), centerX);
  int y = scaleAxis(readAvg(Stick_Y), centerY);
  if (abs(x - lastX) > SEND_DELTA || abs(y - lastY) > SEND_DELTA) {
    bleGamepad.setLeftThumb(x, y);
    lastX = x;
    lastY = y;
    changed = true;
    Serial.printf("Stick: x=%d y=%d\n", x, y);
  }

  if (connected && changed) bleGamepad.sendReport();
  delay(5);
}

bool update(int pin, int btn, const char* name) {
  bool pressed = (digitalRead(pin) == LOW);
  bool wasPressed = bleGamepad.isPressed(btn);
  if (pressed == wasPressed) return false;

  if (pressed) bleGamepad.press(btn);
  else         bleGamepad.release(btn);
  Serial.print(name);
  Serial.println(pressed ? " pressed" : " released");
  return true;
}