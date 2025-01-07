#define BLYNK_TEMPLATE_ID "id"
#define BLYNK_TEMPLATE_NAME "name of template"
#define BLYNK_AUTH_TOKEN "Auth" //  Blynk Auth Token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP_Mail_Client.h>

// Wi-Fi credentials
const char* ssid = "SSID";       // Wi-Fi name
const char* password = "PASSWORD"; //Wi-Fi password

// SMTP server settings
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 587
#define EMAIL_SENDER "S-EMAIL"   // Sender email
#define EMAIL_PASSWORD "APP PASSWORD"      // Sender app password
#define EMAIL_RECIPIENT "R-EMAIL"   // Receiver email

// PIR Sensor and Buzzer
#define PIR_SENSOR_PIN D2
#define BUZZER_PIN D1

// Blynk virtual pins
#define VIRTUAL_LED V1
#define VIRTUAL_GAUGE V2

// Email and Blynk instances
SMTPSession smtp;
BlynkTimer timer;

// Function to send email notification
void sendEmailNotification() {
  smtp.callback([](SMTP_Status status) {
    Serial.println("Email Status: " + String(status.info()));
  });

  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = EMAIL_SENDER;
  session.login.password = EMAIL_PASSWORD;

  SMTP_Message message;
  message.sender.name = "Motion Detector";
  message.sender.email = EMAIL_SENDER;
  message.subject = "Motion Detected Alert";
  message.addRecipient("Recipient", EMAIL_RECIPIENT);
  message.text.content = "Motion has been detected in the monitored area.";

  if (!smtp.connect(&session)) {
    Serial.println("Failed to connect to SMTP server: " + smtp.errorReason());
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Error sending email: " + smtp.errorReason());
  } else {
    Serial.println("Email sent successfully!");
  }

  smtp.closeSession();
}

// Function to check motion and trigger actions
void checkMotion() {
  int pirState = digitalRead(PIR_SENSOR_PIN);

  if (pirState == HIGH) { // Motion detected
    Serial.println("Motion Detected! Activating Buzzer and Notifications.");
    
    // Activate buzzer
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(300);
      digitalWrite(BUZZER_PIN, LOW);
      delay(300);
    }

    // Send Blynk and email notifications
    Blynk.virtualWrite(VIRTUAL_LED, 255);      // Turn on virtual LED
    Blynk.virtualWrite(VIRTUAL_GAUGE, 100);    // Update virtual gauge
    Blynk.logEvent("motion_detected", "Motion Detected!"); // Blynk push notification
    sendEmailNotification();                   // Email notification

    delay(2000); // Avoid repeated triggers
  } else { // No motion detected
    digitalWrite(BUZZER_PIN, LOW);             // Ensure buzzer is off
    Blynk.virtualWrite(VIRTUAL_LED, 0);        // Turn off virtual LED
    Blynk.virtualWrite(VIRTUAL_GAUGE, 0);      // Reset gauge
    Serial.println("No Motion Detected.");
  }
}

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT); // Set the PIR sensor pin as input
  pinMode(BUZZER_PIN, OUTPUT);    // Set the buzzer pin as output
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password, "blynk.cloud", 80);
  Serial.println("Connected to Blynk!");

  // Set a timer to check for motion every second
  timer.setInterval(1000L, checkMotion);
}

void loop() {
  Blynk.run();
  timer.run();
}
