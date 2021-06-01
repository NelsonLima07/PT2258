/*
 * J3_SH1106.h
 *
 *  Created on: May 31, 2021
 *      Author: Nelson Lima
 */

#include "stdlib.h"

#include "usr/J3_PT2258.h"

#define VOL_MAX 79
#define VOL_MIN 0

struct TPT2258{
	I2C_HandleTypeDef* i2c;
  uint8_t address;
};

typedef struct TPT2258 TPT2258;

/* Canal 0 é o master */
uint8_t aCanais[7] = {MASTER, CANAL1, CANAL2, CANAL3, CANAL4, CANAL5, CANAL6};


/* Enviar comando para o PT2258 */
void j3_PT2258_sendCmd(TPT2258* _pt2258, uint8_t _b1, uint8_t _b2){
  if (_pt2258->i2c != NULL){
    HAL_StatusTypeDef ret;
    uint8_t buf[2];

    buf[0] = _b1;
    buf[1] = _b2;
    ret = HAL_I2C_Master_Transmit(_pt2258->i2c, _pt2258->address, buf, 2, HAL_MAX_DELAY);
    if (ret == HAL_OK) {
    }
    else {
    }
  }
}


TPT2258* J3_PT2258_new(I2C_HandleTypeDef* _i2c, uint8_t _i2c_address){ /* Retorna um ponteiro para o CI PT2258 */
	TPT2258* auxPT2258;

	auxPT2258 = malloc(sizeof(TPT2258));
	auxPT2258->address = _i2c_address;
	auxPT2258->i2c = _i2c;

	return auxPT2258;
}


void J3_PT2258_setVolumeCanal(TPT2258* _pt2258, uint8_t _canal, uint8_t _vol){
	if (_canal > 6){
		return;
	}
	uint8_t auxU, auxD;

	if (_vol > VOL_MAX)
		_vol = VOL_MAX;


	auxU = ( aCanais[_canal]  | (_vol % 10) ); // Byte da Unidade
	auxD = ( (aCanais[_canal] - 0x10)  | (_vol / 10) ); // Byte da Dezeza

	j3_PT2258_sendCmd(_pt2258, auxD, auxU);
}
