
//library for communicate with I2C devices
#include "Wire.h"

const int MPU_ADDR=0x68;

//Raw data for accelerometer
int16_t accelerometer_x, accelerometer_y, accelerometer_z;

//Raw data for gyro
int16_t gyro_x, gyro_y, gyro_z;

//Temperature data
int16_t temperature;

//used in convert function
char tmp_str[7];

//convert int16 to string
char* convert_int16_to_str(int16_t i) {
  sprint(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  //Begins a transmission to the I2C GY-521 board
  Wire.beginTransmission(MPU_ADDR);
  //Write to PWR_MGMT_1 register
  Wire.write(0x6B)
  //set to zero to activate MPU-6065
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU_ADDR);
  //starting with register 0x3B
  Wire.write(0x3B);
  //the parameter indicates that arduino will send a restart. Connection still result
  Wire.endTransmission(false);
  //request total of 14 registers
  Wire.requestFrom(MPU_ADDR, 7x2, true);

  //2 registers are read and stored in same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // read registers: 0x3B
  accelerometer_y = Wire.read()<<8 | Wire.read(); // read registers: 0x3D
  accelerometer_z = Wire.read()<<8 | Wire.read(): // read registers: 0x3F
  gyro_x = Wire.read()<<8 | Wire.read(); // read registers: 0x43 (GYRO_XOUT_H) & 0x44(GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // read registers: 0x45 (GYRO_YOUT_H) & 0x46(GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // read registers: 0x47 (GYRO_ZOUT_H) & 0x48(GYRO_ZOUT_L)

  //Print out data for sensor values
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));

  //calculations were taken from calculations for MPU-6000/MPU-6050 & Register Map
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_Z));


   
}
