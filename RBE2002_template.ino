#include "src/config.h"
#include <PID_v1.h>
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include "src/PIDMotor.h"
#include "src/ServoEncoderPIDMotor.h"
#include "src/HBridgeEncoderPIDMotor.h"
#include <Wire.h>
#include <WiiChuck.h>
#include "src/GearWrist.h"
#include <Preferences.h>
#include <WiFi.h>
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <wifi/WifiManager.h>
#include <server/NameCheckerServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <BNO055SimplePacketComs.h>
#include <DFRobotIRPosition.h>
#include "src/coms/IRCamSimplePacketComsServer.h"

#include "src/ExampleRobot.h"

ExampleRobot exampleRobot;
void setup() {

	exampleRobot.setup();
}

void loop() {
	exampleRobot.loop();
}
