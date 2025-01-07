# Smart Motion Sensor Monitoring System

## Project Overview
This project uses an **ESP8266** microcontroller to monitor motion using a **PIR sensor** and send notifications and email alerts when motion is detected. The system is integrated with the **Blynk IoT platform** to control and monitor the device remotely. When motion is detected, the system activates a **buzzer**, sends a **push notification** through Blynk, updates a **virtual gauge** on the Blynk app, and sends an **email alert** to the designated recipient.

## Features
- Motion detection using a **PIR sensor**.
- **Buzzer** activation when motion is detected.
- **Blynk** integration for remote monitoring and control.
- **Email notifications** sent using **Gmail SMTP**.
- **Push notifications** using the Blynk app.
- **Virtual LED** and **gauge** on the Blynk app to show the motion status.

## Hardware Requirements
- **ESP8266 NodeMCU** or any ESP8266-compatible board.
- **PIR Motion Sensor** (for detecting motion).
- **Buzzer** (to alert when motion is detected).
- **Jumper wires** for connections.
- **Breadboard** (optional, for easy prototyping).

## Software Requirements
- **Arduino IDE** (with ESP8266 board support installed).
- **Blynk Library** (for integrating with the Blynk app).
- **ESP Mail Client Library** (for sending email notifications).
- **Wi-Fi credentials** for your network.
- **Gmail account** for sending email notifications.

## Setup and Installation

### 1. Clone the repository
You can clone or download this repository to your local machine to use it in the Arduino IDE.

### 2. Install necessary libraries
Install the following libraries through the **Arduino Library Manager**:
- **Blynk**: For connecting the device to the Blynk platform.
- **ESP Mail Client**: For sending email notifications.
- **ESP8266WiFi**: To connect the ESP8266 to your Wi-Fi network.

### 3. Configure the code
1. Replace the following details in the code:
   - **Wi-Fi credentials** (`ssid` and `password`).
   - **Gmail credentials** (`EMAIL_SENDER` and `EMAIL_PASSWORD`).
   - **Blynk authentication token** (`BLYNK_AUTH_TOKEN`).
   - **Recipient email address** for notifications.

2. **Upload the code** to your ESP8266 board using the Arduino IDE.

### 4. Blynk App Setup
1. Open the **Blynk app** and create a new project.
2. Add the following widgets to your project:
   - **LED widget**: For visual indication of motion.
   - **Gauge widget**: To show motion intensity (optional).
   - **Push Notifications**: To notify when motion is detected.
3. Copy the **Blynk Auth Token** from your Blynk project and paste it in the code.

### 5. Connect hardware
- **PIR sensor**: Connect the **VCC** and **GND** pins of the PIR sensor to the **3.3V** and **GND** of the ESP8266.
- **Signal** pin of the PIR sensor: Connect it to **GPIO D2** of the ESP8266 (or change the pin in the code).
- **Buzzer**: Connect the **positive** leg to **GPIO D1** and the **negative** leg to **GND**.

## Operation

- When motion is detected by the **PIR sensor**, the **Buzzer** is activated, and the system will send:
  - A **Push notification** via the Blynk app.
  - A **Visual cue** by lighting up the **LED** widget in the app.
  - A **Gauge** widget updates to show the motion status (optional).
  - An **Email notification** is sent to the configured email address.

- When there is no motion detected, the **Buzzer** is turned off, and the **LED** widget is turned off.

## Troubleshooting
- **Wi-Fi connection issues**: Ensure that the ESP8266 is connected to the correct Wi-Fi network and that the credentials are correctly entered in the code.
- **Push notifications not received**: Check your **Blynk app settings** and ensure that notifications are enabled for the project.
- **Email not sent**: Ensure that the **SMTP settings** are correct, and check your **Gmail security settings** for allowing less secure apps or use an **App Password** if two-factor authentication is enabled.

## License
This project is open-source and available under the MIT License.

## Authors
- **Romysaa Hamdy** - [GitHub](https://github.com/Romysaa-Hamdy)

## Acknowledgments
- **Blynk**: For the easy-to-use IoT platform.
- **ESP8266**: For providing a reliable Wi-Fi module for embedded projects.
- **Gmail SMTP**: For sending email notifications.
