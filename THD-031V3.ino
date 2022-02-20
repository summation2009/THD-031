#include <ModbusMaster.h> //https://www.arduinolibraries.infoModbusMaster/libraries/modbus-master
#include <SoftwareSerial.h>  //https://github.com/PaulStoffregen/SoftwareSerial
#define TXD 4  // your software serial TXD pin
#define RXD 3  // your software serial RXD pin
#define slaveID 1

SoftwareSerial mySerial(RXD, TXD);

ModbusMaster node;

void setup() {
  Serial.begin(9600);   // config baudrate modbus
  mySerial.begin(9600);

}

void loop() {
  get_th031();

}

int get_modbusRTU_sensor(int addr , uint16_t  REG) {
  int result;
  node.begin(addr, mySerial);
  //result = node.readInputRegisters (REG, 2); ///< Modbus function 0x04 Read Input Registers
  result = node.readHoldingRegisters (REG, 2);
  if (result == node.ku8MBSuccess) {
    return node.getResponseBuffer(0);
  } else {
    //Serial.print("Connec modbus fail. REG >>> "); mySerial.println(REG, HEX); // Debug
    return -270;
  }
}

/************************TH-031**************************/
void get_th031() {
#define HUMIDITY_REG 0
#define TEMPERATURE_REG 1
  float Temperature, Humidity;
  Humidity = get_modbusRTU_sensor(slaveID, HUMIDITY_REG) / 10;
  delay(1000);
  Temperature = get_modbusRTU_sensor(slaveID, TEMPERATURE_REG) / 10;
  delay(1000);
  Serial.print("Temperature = ");
  Serial.print(Temperature, 1);
  Serial.print("C,");
  Serial.print("Humidity = ");
  Serial.print(Humidity, 1);
  Serial.println("%RH");
}
