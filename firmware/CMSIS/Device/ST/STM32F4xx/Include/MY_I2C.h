#ifndef __MY_I2C_H
#define __MY_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f4xx.h"
	 
void I2C_ByteWrite(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u16 NumByteToWrite);
void I2C_BufferRead(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u16 NumByteToRead);
void I2C_BufferRead_Addr(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);
   
void I2C_ByteWrite(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u16 NumByteToWrite)
{
	int i;
  /* Send START condition */
  I2C_GenerateSTART(I2Cx, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send slave address for write */
  I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  for(i=0;i<NumByteToWrite;i++)
  {
    /* Send the byte to be written */
    I2C_SendData(I2Cx, pBuffer[i]);

    /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(I2Cx, ENABLE);
}

void I2C_BufferRead(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u16 NumByteToRead)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2Cx, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send slave address for write */
  I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2Cx, ENABLE);


  /* Send START condition a second time */
  I2C_GenerateSTART(I2Cx, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send slave address for read */
  I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Receiver);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2Cx, DISABLE);

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the slave */
      *pBuffer = I2C_ReceiveData(I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

void I2C_BufferRead_Addr(I2C_TypeDef* I2Cx, u8 slaveAddr, u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2Cx, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send slave address for write */
  I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2Cx, ENABLE);

  /* Send the slave internal address to write to */
  I2C_SendData(I2Cx, ReadAddr);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send START condition a second time */
  I2C_GenerateSTART(I2Cx, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send slave address for read */
  I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Receiver);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2Cx, DISABLE);

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the slave */
      *pBuffer = I2C_ReceiveData(I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/************************ (C) COPYRIGHT ICViet.vn *****END OF FILE****/
