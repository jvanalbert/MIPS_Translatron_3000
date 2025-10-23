/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void div_reg_assm(void) {
	if (strcmp(OP_CODE, "DIV") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check par
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// create binary
	setBits_str(31, "000000");
	setBits_num(25, PARAM1.value, 5); //changed for rs to get bits 25-21(changed by Gabriella)
	setBits_num(20, PARAM2.value, 5); //changed for rt to get bits 20-16(changed by Gabriella)
	setBits_num(15, 0, 10); //switched order of rd and shamt to match div format(changed by Gabriella)
	setBits_str(5, "011010");
	
	
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("DIV");
	setParam(1, REGISTER, Rs); //switched registers to match div format(changed by Gabriella)
	setParam(2, REGISTER, Rt); //switched registers to match div format(changed by Gabriella)

	state = COMPLETE_DECODE;
}


