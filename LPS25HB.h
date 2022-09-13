#ifndef _LPS25HB_H
#define _LPS25HB_H

#define LPS25HB_DEVICE_ADDRESS 0xB8

// Register addresses
#define LPS25HB_WHO_AM_I 0xF //who am I
#define LPS25HB_RES_CONF 0x10 //pressure and temperature resolution
#define LPS25HB_CTRL_REG1 0x20 //control register 1
#define LPS25HB_CTRL_REG2 0x21 //control register 2
#define LPS25HB_PRESS_OUT_XL 0x28
#define LPS25HB_PRESS_OUT_L 0x29
#define LPS25HB_PRESS_OUT_H 0x2A
#define LPS25HB_TEMP_OUT_L 0x2B
#define LPS25HB_TEMP_OUT_H 0x2C

#define LPS25HB_CR1_PD 0x80 //power-down 0x80
#define LPS25HB_CR1_ODR_ONE_SHOT 0x0 //output data rate is null
#define LPS25HB_CR1_ODR1HZ 0x30 //output data rate 1 Hz
#define LPS25HB_CR1_ODR25HZ 0x40 //output data rate 25 Hz
#define LPS25HB_CR1_BDU (1u << 2)	// bock data update during read

#endif
