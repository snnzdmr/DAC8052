#ifndef DAC80502

#include <stdint.h>
#include <stdbool.h>

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


typedef enum DAC_RESPONSE{
    OK=0,
    ERROR,
    SOFT_RESET_ERROR,
    BROADCASTA_ERROR,
    BROADCASTB_ERROR,
    SYNCA_ERROR,
    SYNCB_ERROR,
    POWERDONW_REF_ERROR,
    POWERDONW_A_ERROR,
    POWERDONW_B_ERROR,
    REF_DIV_ERROR,
    GAIN_A_ERROR,
    GAIN_B_ERROR,

}DAC_RESPONSE;

typedef struct I2cFunctions{
    bool (*i2cWriteReg)(uint8_t,uint16_t);
    bool (*i2cReadReg)(uint8_t,uint16_t *);
}I2cFunctions;


typedef struct DAC80502{
    uint8_t slaveAddress;
    bool broadcastA;         // false
    bool broadcastB;         // false
    bool syncA;              // false
    bool syncB;              // false
    bool powerDownRef;       // true: disables the device internal reference
    bool powerDownA;         // true: output is connected to GND through a 1-kΩ internal resistor
    bool powerDownB;         // true: output is connected to GND through a 1-kΩ internal resistor
    bool referenceDiv;       // true : divided by a factor of 2. false : not divide
    bool gainBufferA;        // true : DAC has a gain of 2. false : DAC has a gain of 1
    bool gainBufferB;        // true : DAC has a gain of 2. false : DAC has a gain of 1
    uint16_t dataA;
    uint16_t dataB;
    I2cFunctions i2c;
}DAC80502;
DAC80502 *gParams;

void Log(char *msg,uint16_t val);
void errorHandler(uint16_t errorCode);
uint16_t setBit(uint16_t n, uint8_t k);
uint16_t clearBit(uint16_t n, uint8_t k);
uint16_t setWriteValue(bool state,uint16_t val,uint8_t bitIndex);
DAC_RESPONSE DAC80502_readRegister(uint8_t regAddress,uint16_t *value);
DAC_RESPONSE DAC80502_setRegister(uint8_t regAddress,uint16_t value);
DAC_RESPONSE DAC80502_getDevID(uint16_t *id);
DAC_RESPONSE DAC80502_getStatus(uint16_t *status);
DAC_RESPONSE DAC80502_setClearBit(uint8_t regAddress,uint8_t bitIndex,bool bitState);
DAC_RESPONSE DAC80502_broadcastA(bool en);
DAC_RESPONSE DAC80502_broadcastB(bool en);
DAC_RESPONSE DAC80502_syncA(bool en);
DAC_RESPONSE DAC80502_syncB(bool en);
DAC_RESPONSE DAC80502_powerDownReferance(bool en);
DAC_RESPONSE DAC80502_powerDownA(bool en);
DAC_RESPONSE DAC80502_powerDownB(bool en);
DAC_RESPONSE DAC80502_referanceDiv(bool en);
DAC_RESPONSE DAC80502_gainA(bool en);
DAC_RESPONSE DAC80502_gainB(bool en);
DAC_RESPONSE DAC80502_trigerLDAC(void);
DAC_RESPONSE DAC80502_softReset (void);
DAC_RESPONSE DAC80502_broadcastData(uint16_t data);
DAC_RESPONSE DAC80502_OutputA(uint16_t data);
DAC_RESPONSE DAC80502_OutputB(uint16_t data);
DAC_RESPONSE DAC80502_Init(DAC80502 *params);


#endif // DAC80502
