/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/


#include "Instruction.h"
//LUIU only uses 2 parameters: rt and immediate, no rs(param3)
void lui_immd_assm(void) {
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != IMMEDIATE) {
		state = MISSING_IMMED;
		return;
	}

	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	setBits_str(31, "001111");
	//rs field is 0 for LUI since its not used
	setBits_num(25, 0, 5);
	setBits_num(20, PARAM1.value, 5);
	setBits_num(15, PARAM2.value, 16);

	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	//uint32_t Rs = getBits(25, 5); rs field is not used
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	setOp("LUI");
	setParam(1, REGISTER, Rt); 
	setParam(2, IMMEDIATE, imm16); 
	// REMOVED: setParam(3, IMMEDIATE, imm16) - now this is parameter 2

	state = COMPLETE_DECODE;
}



