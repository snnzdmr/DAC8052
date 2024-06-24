#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "dac80502.h"


#define NOOP			 0x00
#define DEVID			 0x01
#define SYNC			 0x02
#define CONFIG			 0x03
#define GAIN			 0x04
#define TRIGGER			 0x05
#define BRDCAST			 0x06
#define STATUS			 0x07
#define DACADATA		 0x08
#define DACBDATA		 0x09

#define TRIGGER_LDAC                        0x10
#define SOFT_RESET                          0x0A

#define DAC80502_SLAVE_ADDRESS              0x48


bool I2C_WriteRegister_16(uint8_t regAddress,uint16_t txData);
bool I2C_ReadRegister_16(uint8_t regAddress,uint16_t *RxBuffer);



bool I2C_WriteRegister_16(uint8_t regAddress,uint16_t txData){
    printf("I2C_WriteRegister_16(Address:0x%x,Data:0x%x); \n",regAddress,txData);
    return true;
}


bool I2C_ReadRegister_16(uint8_t regAddress,uint16_t *RxBuffer){
    *RxBuffer =0x00;
    printf("I2C_ReadRegister_16(Address:0x%x,Data:0x%x);\n",regAddress,*RxBuffer);
    return true;
}

int main()
{
    DAC80502 dParams;
    dParams.slaveAddress = DAC80502_SLAVE_ADDRESS;
    dParams.broadcastA = false;
    dParams.broadcastB = false;
    dParams.syncA = false;
    dParams.syncB = false;
    dParams.powerDownRef = false;
    dParams.powerDownA = false;
    dParams.powerDownB = false;
    dParams.gainBufferA = false;
    dParams.gainBufferB = false;
    dParams.referenceDiv = false;

    dParams.i2c.i2cWriteReg = &I2C_WriteRegister_16;
    dParams.i2c.i2cReadReg  = &I2C_ReadRegister_16;
    DAC80502_Init(&dParams);
    DAC80502_broadcastData(0x1111);
    DAC80502_OutputA(0xAAAA);
    DAC80502_OutputB(0xBBBB);
    return 0;
}






















