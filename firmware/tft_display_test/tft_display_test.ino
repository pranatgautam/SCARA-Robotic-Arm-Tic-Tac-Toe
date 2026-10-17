#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#include <ESP32WebServer.h> 
#include <TFT_eSPI.h>   // Hardware-specific library
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiMulti.h> 
#include "camera_pins.h"
#include "CSS.h"
#include "esp_camera.h"

#define TEXT_SIZE   2 

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

ESP32WebServer  server(80);

const char* host = "esp32";
const char* ssid = "#####";
const char* password = "********";//Enter your desired password


void setup() {

  tft.begin(); // Resolution in UserSteup file 320 x 240
  tft.setRotation(0);	// 0 & 2 Portrait. 1 & 3 landscape
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(TEXT_SIZE);
  tft.setCursor(10, 10); // Set cursor position
  tft.print("Start config...");
  

  Serial.print("Starting Camera Configuration.....")
    
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565; 

  config.frame_size = FRAMESIZE_240X240;
    //config.frame_size = FRAMESIZE_96X96;

   config.fb_count = 1; // <------ Frame buffer count

   Serial.print("\r\n Camera init...")
   esp_err_t err = esp_camera_init(&config); // Init Camera
   if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
   return;
  }

}

camera_fb_t * fb;
void loop() {

  fb = esp_camera_fb_get();   // Capture a frame from the camera
if (!fb) {
                delay(250); // If failure, try again, atleast once
                camera_fb_t * fb = esp_camera_fb_get();
                if (!fb) {                  
                  Serial.print("\r\n Camera capture failed");
                  tft.setTextColor(TFT_WHITE, TFT_RED); //  text, background
                  tft.print("Capture failed");
                  return;

 // Display the captured image on the TFT display
  tft.pushImage(0, 0, fb->width, fb->height, (uint16_t*)fb->buf);
  esp_camera_fb_return(fb); // Return the frame buffer to the camera

  delay(1000); // Delay for 1 second before capturing the next image
 

}
