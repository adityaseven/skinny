/*
 * =====================================================================================
 *
 *       Filename:  i2c.h
 *
 *    Description:  i2c.h helper files
 *
 *        Version:  1.0
 *        Created:  08/12/2017 17:40:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Raghava Aditya Renukunta (), adi.raghava3@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _I2C_H_
#define _I2C_H_

#include <MKL46Z4.h>
#include <stdint.h>
#include <stdbool.h>

static inline void i2c_set_tx_mode(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 |= I2C_C1_TX_MASK;
}

static inline void i2c_set_rx_mode(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 &= ~I2C_C1_TX_MASK;
}

static inline void i2c_set_master_mode(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 |= I2C_C1_MST_MASK;
}

static inline void i2c_set_slave_mode(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 &= ~I2C_C1_MST_MASK;
}

static inline void i2c_send_ack(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 &= ~I2C_C1_TXAK_MASK;
}

static inline void i2c_send_nack(volatile I2C_Type *i2c_b)
{
	i2c_b->C1 |= I2C_C1_TXAK_MASK;
}

static inline bool i2c_is_ack(volatile I2C_Type *i2c_b)
{
	if ((i2c_b->S & I2C_S_RXAK_MASK) == 0)
		return true;
	else
		return false;
}

static inline bool i2c_is_bus_busy(volatile I2C_Type *i2c_b)
{
	if ((i2c_b->S & I2C_S_BUSY_MASK) == 0)
		return false;
	else
		return true;
}

static inline bool i2c_is_arbitration_lost(volatile I2C_Type *i2c_b )
{
	if ((i2c_b->S & I2C_S_ARBL_MASK) == 0)
		return false;
	else
		return true;
}

static inline void i2c_do_repeated_start(volatile I2C_Type *i2c_b )
{
	i2c_b->C1 |=I2C_C1_RSTA_MASK;
}

static inline void i2c_wait(volatile I2C_Type *i2c_b)
{
	while (! (i2c_b->S & I2C_S_IICIF_MASK));

	i2c_b->S = I2C_S_IICIF_MASK;
}

static inline void i2c_wait_transfer_complete(volatile I2C_Type *i2c_b)
{
	while (! (i2c_b->S & I2C_S_TCF_MASK));
}

static inline uint8_t i2c_read_byte(volatile I2C_Type *i2c_b)
{
	return i2c_b->D;
}

static inline void i2c_write_byte(volatile I2C_Type *i2c_b, uint8_t b)
{
	i2c_b->D = b;
}

static inline void i2c_start(volatile I2C_Type *i2c_b)
{
	i2c_set_master_mode(i2c_b);
	i2c_set_tx_mode(i2c_b);
}

static inline void i2c_stop(volatile I2C_Type *i2c_b)
{
	i2c_set_slave_mode(i2c_b);
	i2c_set_rx_mode(i2c_b);
}

bool i2c_write_register(uint32_t i2c_idx, uint8_t addr, uint8_t data);
bool i2c_read_register(uint32_t i2c_idx, uint8_t addr, uint8_t *val);
void i2c_init(uint32_t i2c_idx, uint32_t baud);

#endif /* ifndef _I2C_H_


 */