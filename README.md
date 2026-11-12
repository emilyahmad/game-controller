<p align="center">
<img src="https://github.com/emilyahmad/game-controller/blob/main/images/emoolii-logo.png" width=50% alt="Emoolii logo">
<br>
</p>

<h1 align="center">Emoolii Remote</h1>

A custom game controller for playing Super Mario Bros on Dolphin Emulator. For now, just a breaboard, joystick, some push buttons and ESP32-BLE-Gamepad

<p align="center">
<img src="https://github.com/emilyahmad/game-controller/blob/main/images/v2_demo.gif" width=50% alt="Gameplay demo with working joystick and button controls on the breadboard prototype">
<br>
<sub>Runthrough with my prototype</sub>
</p>

### Components

Pin assignments assume the **ESP32-C3 SuperMini** (GPIO numbers, not silkscreen labels). Strapping pins GPIO8/9 are used for I²C (they idle high, which is safe at boot), and GPIO2 is a button with a pull-up, so don't hold HOME while powering on.

| Component | ESP32 SuperMini pins | Use | Qty | Price | Link |
|---|---|---|---|---|---|
| ESP32 SuperMini | — | MCU, BLE gamepad (ESP32-BLE-Gamepad) | 1 | TBD | [Amazon](https://www.amazon.com/dp/B0GS283V6F) |
| 3.7 V 1800 mAh LiPo (Nova 654141) | + → slide switch → 5V, − → GND | Power | 1 | Already owned | — |
| 2-pin JST-PH header | Between battery and slide switch | Battery connector | 1 | TBD | — |
| Slide switch | Inline on battery + | Power on/off | 1 | TBD | — |
| Analog joystick | VRx → GPIO0, VRy → GPIO1, SW → GPIO3, VCC → 3V3, GND → GND | Movement (D-pad); press = B | 1 | Already owned | — |
| 12 × 12 mm illuminated tactile switch | A → GPIO4, 1 → GPIO5, 2 → GPIO6 (other leg → GND, `INPUT_PULLUP`) | A, 1, 2 buttons, light up on press | 3 | TBD | [Amazon](https://www.amazon.com/dp/B0DLH9RZ13) |
| 6 × 6 mm tactile switch | SELECT → GPIO7, HOME → GPIO2, START → GPIO20 (other leg → GND, `INPUT_PULLUP`) | Menu buttons (−, HOME, +) | 3 | Already owned | — |
| Adafruit LIS3DH accelerometer (2809) | SDA → GPIO8, SCL → GPIO9, INT1 → GPIO21, VIN → 3V3, GND → GND | Shake detection, mapped to a "shake" button | 1 | $4.95 | [Adafruit](https://www.adafruit.com/product/2809) |
| Vibrating Mini Motor Disc (1201) | + → 3V3, − → AO3400A drain | Rumble | 1 | $1.95 | [Adafruit](https://www.adafruit.com/product/1201) |
| AO3400A N-channel MOSFET | Gate → GPIO10 (100 Ω series, 10 kΩ to GND), source → GND | Motor driver (add a flyback diode across the motor) | 1 | TBD | — |
| Silicone button caps | — | Button covers | 1 set | TBD | [AliExpress](https://www.aliexpress.us/item/3256812674561376.html) |
| Silicone joystick caps | — | Thumb grip | 1 set | TBD | [Amazon](https://www.amazon.com/dp/B08KS5Y1JF) |


<!-- Aiming for something like this:

<table align="center">
  <tr>
    <td align="center" valign="bottom">
      <img src="https://github.com/emilyahmad/game-controller/blob/main/images/wii-remote-inspo.png" height=250 alt="Pink Wii Remote alongside a grid of Wii Remotes in other colors and character themes">
      <br>
      <sub>Wii remote inspo</sub>
    </td>
    <td>&emsp;&emsp;</td>
    <td align="center" valign="bottom">
      <img src="https://github.com/emilyahmad/game-controller/blob/main/images/custom-design.png" height=250 alt="Pink controller design sketch with a cross D-pad, large A button, three small center buttons, 1 and 2 buttons, and four player LEDs">
      <br>
      <sub>Custom design</sub>
    </td>
  </tr>
</table>
<br> -->