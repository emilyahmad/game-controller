const int X_pin = A0;   // change to your joystick pins
const int Y_pin = A1;

const int A_button   = D10;
const int One_button = D9;
const int Two_button = D8;

struct Button { int pin; const char* name; bool last; unsigned long t; };
Button buttons[] = {
  {A_button,   "A", true, 0},
  {One_button, "1", true, 0},
  {Two_button, "2", true, 0},
};

const unsigned long DEBOUNCE_MS = 20;
const unsigned long STICK_MS    = 100;
const int           DEADBAND    = 40;   // ignore changes smaller than this

int lastX = 0, lastY = 0;
unsigned long lastStick = 0;

void setup() {
  Serial.begin(115200);
  for (Button &b : buttons) pinMode(b.pin, INPUT_PULLUP);
}

void loop() {
  // Buttons: print on press/release only
  for (Button &b : buttons) {
    bool s = digitalRead(b.pin);
    if (s != b.last && millis() - b.t > DEBOUNCE_MS) {
      b.t = millis();
      b.last = s;
      Serial.printf("Button %s %s\n", b.name, s == LOW ? "pressed" : "released");
    }
  }

  // Joystick: print at most every STICK_MS, and only if it moved
  if (millis() - lastStick >= STICK_MS) {
    lastStick = millis();
    int x = analogRead(X_pin);
    int y = analogRead(Y_pin);
    if (abs(x - lastX) > DEADBAND || abs(y - lastY) > DEADBAND) {
      lastX = x; lastY = y;
      Serial.printf("Stick X:%d Y:%d\n", x, y);
    }
  }
}