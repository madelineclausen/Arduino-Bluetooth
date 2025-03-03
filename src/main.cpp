#include <Arduino.h>
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <SparkFunLSM6DS3.h>
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.println("*********");
            Serial.print("New value: ");
            for (int i = 0; i < value.length(); i++)
                Serial.print(value[i]);
                Serial.println();
                Serial.println("*********");
        }
    }
};

LSM6DS3 IMU;

void setup() {
    Serial.begin(9600);
    BLEDevice::init("CS 147 (Kevin & Madeline)");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    pCharacteristic->setCallbacks(new MyCallbacks());
    pCharacteristic->setValue("Hello World");
    pService->start();
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    
    IMU.begin();
}
void loop() 
{
  Serial.println();
  Serial.print("X: ");
  Serial.println(IMU.readFloatAccelX(), 4);

  Serial.print("Y: ");
  Serial.println(IMU.readFloatAccelY(), 4);

  Serial.print("Z: ");
  Serial.println(IMU.readFloatAccelZ(), 4);

  Serial.println();

  delay(2000);
}
