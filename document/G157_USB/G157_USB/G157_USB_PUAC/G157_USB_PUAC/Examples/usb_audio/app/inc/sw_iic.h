#ifndef __SW_IIC_H__
#define __SW_IIC_H__

void IIC_Write_NByte(uint8_t devaddr,uint8_t* buf,uint8_t len);
void IIC_Write(uint8_t devaddr,uint8_t regaddr,uint8_t* buf,uint8_t len);
void IIC_Read(uint8_t devaddr,uint8_t regaddr,uint8_t* buf,uint8_t len);


#endif
