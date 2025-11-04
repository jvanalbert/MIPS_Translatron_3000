/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void sw_immd_assm(void) {
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// changed: Immediate should be 16-bit signed value (-32768 to 32767)
	if (PARAM2.value < -32768 || PARAM2.value > 32767) {
		state = INVALID_IMMED;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
	// encode instruction
	setBits_str(31, "101011"); // opcode for SW
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM3.value, 5);
	setBits_num(15, PARAM2.value, 16);

	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	uint32_t base = getBits(25, 5);
	uint32_t rt = getBits(20, 5);
	int32_t offset = (int32_t)getBits(15, 16); // signed offset

	setOp("SW");
	setParam(1, REGISTER, rt); // source register
	setParam(2, IMMEDIATE, offset); // offset
	setParam(3, REGISTER, base); // base register

	state = COMPLETE_DECODE;
}