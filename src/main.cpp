#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 10 // Define the buzzer pin
#define TEMP_THRESHOLD 24.0 // Temperature threshold in degrees Celsius

Adafruit_BME280 bme; // I2C
Adafruit_MPU6050 mpu;

float initialAccelX = 0.0;
float initialAccelY = 0.0;
float initialAccelZ = 0.0;

void setup() {
  Serial.begin(9600);

  // Initialize the buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize BME280
  if (!bme.begin(0x76)) {  // Change to 0x77 depending on your board
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Change address 0x3C or 0x3D depending on your display
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Read and record initial accelerometer values
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  initialAccelX = a.acceleration.x;
  initialAccelY = a.acceleration.y;
  initialAccelZ = a.acceleration.z;
}

void loop() {
  // Read data from the BME280
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  // Read data from the MPU6050 and adjust for initial values
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float accelX = a.acceleration.x - initialAccelX;
  float accelY = a.acceleration.y - initialAccelY;
  float accelZ = a.acceleration.z - initialAccelZ;

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  // Print BME280 data
  display.println("BME280 Data:");
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Humidity: "); display.print(humidity); display.println(" %");
  display.print("Pressure: "); display.print(pressure); display.println(" hPa");

  // Print MPU6050 data
  display.println("MPU6050 Data:");
  display.print("Accel X: "); display.print(accelX); display.println(" m/s^2");
  display.print("Accel Y: "); display.print(accelY); display.println(" m/s^2");
  display.print("Accel Z: "); display.print(accelZ); display.println(" m/s^2");
  display.display();

  // Buzzer logic for temperature threshold
  if (temperature > TEMP_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn the buzzer on
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Turn the buzzer off
  }

  // Send data over Serial
  Serial.print(millis());
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);
  Serial.print(",");
  Serial.println(accelZ);

  delay(2000); // Update every 2 seconds
}
