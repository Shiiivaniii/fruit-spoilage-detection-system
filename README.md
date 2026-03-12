# 🍎 Fruit Spoilage Detection System (IoT)

An **IoT-based fruit freshness monitoring system** that detects spoilage using environmental and gas sensors.

The system uses **ESP32**, **DHT11**, **MQ2**, and **MQ135 sensors** to monitor temperature, humidity, and gas levels emitted during fruit ripening.

Real-time results are delivered through:

* 📟 LCD Display
* 📲 Telegram Bot Alerts
* ☁️ ThingSpeak Cloud Dashboard

The goal is to **reduce food wastage by detecting fruit spoilage early** and providing timely alerts.

---

# 🚀 Features

* Real-time fruit freshness monitoring
* Gas detection using MQ sensors
* Temperature & humidity monitoring
* Telegram bot notifications
* ThingSpeak cloud visualization
* LCD display output
* Spoilage stage prediction

Fruit stages detected:

* **Unripe**
* **Fresh**
* **Ripe**
* **Spoiled**

---

# 🧰 Hardware Requirements

| Component    | Description                         |
| ------------ | ----------------------------------- |
| ESP32        | WiFi-enabled microcontroller        |
| DHT11        | Temperature & Humidity sensor       |
| MQ2          | Gas sensor for methane and hydrogen |
| MQ135        | Gas sensor for ammonia and VOCs     |
| 16x2 LCD     | Local display output                |
| Breadboard   | Circuit prototyping                 |
| Jumper wires | Hardware connections                |

---

# 💻 Software Requirements

Install the following:

* Arduino IDE
* Python 3.8+
* Telegram account
* ThingSpeak account

Python dependency:

```bash
pip install python-telegram-bot
```

---

# 📥 Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/fruit-spoilage-detection-system.git
cd fruit-spoilage-detection-system
```

---

# 🔧 Hardware Setup

Connect sensors to ESP32.

### DHT11

| DHT11 Pin | ESP32   |
| --------- | ------- |
| VCC       | 3.3V    |
| GND       | GND     |
| DATA      | GPIO 15 |

### MQ2 Sensor

| MQ2 Pin | ESP32   |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| AOUT    | GPIO 34 |

### MQ135 Sensor

| MQ135 Pin | ESP32   |
| --------- | ------- |
| VCC       | 5V      |
| GND       | GND     |
| AOUT      | GPIO 35 |

### LCD Display

| LCD Pin | ESP32 |
| ------- | ----- |
| RS      | 19    |
| E       | 23    |
| D4      | 18    |
| D5      | 5     |
| D6      | 21    |
| D7      | 4     |

---

# 🌐 Configure WiFi

Open:

```
esp32-code/fruit_spoilage_detection.ino
```

Update your WiFi credentials:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

---

# ☁️ Setup ThingSpeak

1. Create account at
   https://thingspeak.com

2. Create a **New Channel**

Enable fields:

* Field 1 → Temperature
* Field 2 → Humidity
* Field 3 → Gas Level

Copy **Write API Key**

Replace in ESP32 code:

```cpp
String apiKey = "YOUR_THINGSPEAK_API_KEY";
```

---

# 🤖 Create Telegram Bot

1. Open Telegram
2. Search **BotFather**
3. Run:

```
/newbot
```

4. Follow instructions
5. Copy **Bot Token**

Replace in ESP32 code:

```cpp
#define BOT_TOKEN "YOUR_BOT_TOKEN"
```

---

# 📩 Get Telegram Chat ID

Send a message to your bot.

Open in browser:

```
https://api.telegram.org/botYOUR_BOT_TOKEN/getUpdates
```

Find your **chat_id** and update code:

```cpp
#define CHAT_ID "YOUR_CHAT_ID"
```

---

# ⚙️ Upload Code to ESP32

1. Open Arduino IDE
2. Install ESP32 board support
3. Select board:

```
ESP32 Dev Module
```

4. Upload file:

```
esp32-code/fruit_spoilage_detection.ino
```

Open **Serial Monitor**

Baud rate:

```
115200
```

---

# 📱 Telegram Commands

Start bot:

```
/start
```

Select fruit:

```
/fruit apple
/fruit banana
/fruit tomato
```

Example response:

```
Fruit: Banana
Stage: Fresh
Consume in 1-2 days
```

Spoilage alert example:

```
⚠ Food Spoilage Alert!
Fruit: Banana
Stage: Spoiled
```

---

# 📊 View Data in ThingSpeak

Login to ThingSpeak.

Open your **channel dashboard**.

You will see graphs for:

* Temperature
* Humidity
* Gas levels

Data updates every **50 seconds**.

---

# 📂 Project Structure

```
Fruit-Spoilage-Detection-System
│
├── esp32-code
│   └── fruit_spoilage_detection.ino
│
├── telegram-bot
│   └── bot.py
│
├── hardware
│   └── hardware-components.md
│
├── .gitignore
├── LICENSE
└── README.md
```

---

# 🔬 Future Improvements

* Machine learning based spoilage prediction
* Camera based fruit inspection
* Ethylene gas sensors
* Automatic storage control
* Solar powered IoT system

---

# 👨‍💻 Author

**Shivam Shukla**
National Institute of Technology Kurukshetra

# 📜 License

This project is licensed under the MIT License.
