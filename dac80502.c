#include "dac80502.h"

DAC80502 *gParams;


void Log(char *msg,uint16_t val){
    printf("%s %d \n",msg,val);
}
void errorHandler(uint16_t errorCode){
    printf("Error Handler \n 0x%x",errorCode);
    while(1);
}
uint16_t setBit(uint16_t n, uint8_t k)
{
    return (n | (1 << k));
}
uint16_t clearBit(uint16_t n, uint8_t k)
{
    return (n & (~(1 << k)));
}
uint16_t setWriteValue(bool state,uint16_t val,uint8_t bitIndex){
    uint16_t retVal =0;
    if(state){
        retVal = setBit(val,bitIndex);
    }
    else{
        retVal = clearBit(val,bitIndex);
    }
    return retVal;
}


DAC_RESPONSE DAC80502_readRegister(uint8_t regAddress,uint16_t *value){
    DAC_RESPONSE retVal = ERROR;
    uint16_t rxBuffer;
    bool i2cResponse = gParams->i2c.i2cReadReg(regAddress,&rxBuffer);
    if(i2cResponse){
        *value= rxBuffer;
        retVal = OK;
    }
    else{
        *value = 0;
        retVal = ERROR;
    }
    return retVal;
}

DAC_RESPONSE DAC80502_setRegister(uint8_t regAddress,uint16_t value){
    DAC_RESPONSE retVal = ERROR;
    uint16_t txBuffer=value;
    bool i2cResponse = gParams->i2c.i2cWriteReg(regAddress,txBuffer);
    if(i2cResponse){
        retVal = OK;
    }
    else{
        retVal = ERROR;
    }
    return retVal;

}
DAC_RESPONSE DAC80502_getDevID(uint16_t *id){
    return DAC80502_readRegister(DEVID,id);
}
DAC_RESPONSE DAC80502_getStatus(uint16_t *status){
    return DAC80502_readRegister(STATUS,status);
}

DAC_RESPONSE DAC80502_setClearBit(uint8_t regAddress,uint8_t bitIndex,bool bitState){
    DAC_RESPONSE retVal = ERROR;
    uint16_t rxBuffer;
    bool i2cResponse = gParams->i2c.i2cReadReg(regAddress,&rxBuffer);
    if(i2cResponse){
        rxBuffer = setWriteValue(bitState,rxBuffer,bitIndex);
        i2cResponse = gParams->i2c.i2cWriteReg(regAddress,rxBuffer);
        if(i2cResponse){
            retVal = OK;
        }
        else{
            retVal = ERROR;
        }
    }
    else{
            retVal = ERROR;
    }
    return retVal;

}

DAC_RESPONSE DAC80502_broadcastA(bool en){
    return DAC80502_setClearBit(SYNC,8,en);
}
DAC_RESPONSE DAC80502_broadcastB(bool en){
    return DAC80502_setClearBit(SYNC,9,en);
}
DAC_RESPONSE DAC80502_syncA(bool en){
    return DAC80502_setClearBit(SYNC,0,en);
}
DAC_RESPONSE DAC80502_syncB(bool en){
    return DAC80502_setClearBit(SYNC,1,en);
}
DAC_RESPONSE DAC80502_powerDownReferance(bool en){
    return DAC80502_setClearBit(CONFIG,8,en);
}
DAC_RESPONSE DAC80502_powerDownA(bool en){
    return DAC80502_setClearBit(CONFIG,0,en);
}
DAC_RESPONSE DAC80502_powerDownB(bool en){
    return DAC80502_setClearBit(CONFIG,1,en);
}
DAC_RESPONSE DAC80502_referanceDiv(bool en){
    return DAC80502_setClearBit(GAIN,8,en);
}
DAC_RESPONSE DAC80502_gainA(bool en){
    return DAC80502_setClearBit(GAIN,0,en);
}
DAC_RESPONSE DAC80502_gainB(bool en){
    return DAC80502_setClearBit(GAIN,1,en);
}
DAC_RESPONSE DAC80502_trigerLDAC(void){
    return DAC80502_setRegister(TRIGGER,TRIGGER_LDAC);
}
DAC_RESPONSE DAC80502_softReset (void){
    return DAC80502_setRegister(TRIGGER,SOFT_RESET);
}
DAC_RESPONSE DAC80502_broadcastData(uint16_t data){
    return DAC80502_setRegister(BRDCAST,data);
}
DAC_RESPONSE DAC80502_OutputA(uint16_t data){
    return DAC80502_setRegister(DACADATA,data);
}
DAC_RESPONSE DAC80502_OutputB(uint16_t data){
    return DAC80502_setRegister(DACBDATA,data);
}
DAC_RESPONSE DAC80502_Init(DAC80502 *params){
    DAC_RESPONSE res = ERROR;
    gParams =params;
    res = DAC80502_softReset();
    if(res != OK){
       errorHandler(SOFT_RESET_ERROR);
    }
    else{
        Log("Soft Reset Succesfull",0);
    }
    res = DAC80502_broadcastA(params->broadcastA);
    if(res != OK){
       errorHandler(BROADCASTA_ERROR);
    }
    else{
        Log("Broadcast A Init Succesfull Set Value: ",params->broadcastA);
    }

    res = DAC80502_broadcastB(params->broadcastB);
    if(res != OK){
       errorHandler(BROADCASTB_ERROR);
    }
    else{
        Log("Broadcast B Init Succesfull Set Value: ",params->broadcastB);
    }

    res = DAC80502_syncA(params->syncA);
    if(res != OK){
       errorHandler(SYNCA_ERROR);
    }
    else{
        Log("SYNC A Init Succesfull Set Value: ",params->syncA);
    }

    res = DAC80502_syncB(params->syncB);
    if(res != OK){
       errorHandler(SYNCB_ERROR);
    }
    else{
        Log("SYNC B Init Succesfull Set Value: ",params->syncB);
    }

    res = DAC80502_powerDownReferance(params->powerDownRef);
    if(res != OK){
       errorHandler(POWERDONW_REF_ERROR);
    }
    else{
        Log("POWER DOWN REF Init Succesfull Set Value: ",params->powerDownRef);
    }

    res = DAC80502_powerDownA(params->powerDownA);
    if(res != OK){
       errorHandler(POWERDONW_A_ERROR);
    }
    else{
        Log("POWER DOWN A Init Succesfull Set Value: ",params->powerDownA);
    }

    res = DAC80502_powerDownB(params->powerDownB);
    if(res != OK){
       errorHandler(POWERDONW_B_ERROR);
    }
    else{
        Log("POWER DOWN B Init Succesfull Set Value: ",params->powerDownB);
    }

    res = DAC80502_referanceDiv(params->referenceDiv);
    if(res != OK){
       errorHandler(REF_DIV_ERROR);
    }
    else{
        Log("REFERANCE DIV Init Succesfull Set Value: ",params->referenceDiv);
    }

    res = DAC80502_gainA(params->gainBufferA);
    if(res != OK){
       errorHandler(GAIN_A_ERROR);
    }
    else{
        Log("GAIN A  Init Succesfull Set Value: ",params->gainBufferA);
    }

    res = DAC80502_gainB(params->gainBufferB);
    if(res != OK){
       errorHandler(GAIN_B_ERROR);
    }
    else{
        Log("GAIN B  Init Succesfull Set Value: ",params->gainBufferB);
    }
}

