/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// dont get paid enough to implement

#include "Instruction.h"

void ori_immd_assm(void) {

	//ensure the current operation is ORI
	//if it is not, sets the state to WRONG_COMMAND and returns 
	if(strcmp(OP_CODE, "ORI")!=0)
	{
		state = WRONG_COMMAND;
		return; 
	}
	//validates the first parameter is a register
	if(PARAM1.type!=REGISTER)
	{
		state = MISSING_REG; 
		return; 
	}
	//validates the second parameter is a register
	if(PARAM2.type!=REGISTER)
	{
		state = MISSING_REG; 
		return; 
	}
	//validates the third parameter is an immediate value
	if(PARAM3.type!=IMMEDIATE)
	{
		state = INVALID_PARAM; 
		return; 
	}

	//checks that the register numbers within range 0-31, which is the valid MIPS range
	if(PARAM1.value>31)
	{
		state = INVALID_REG;
		return; 
	}
	//checks that the register numbers within range 0-31, which is the valid MIPS range
	if(PARAM2.value>31)
	{
		state = INVALID_REG;
		return; 
	}
	//checks that the immediate value is within range 0-65535 (0xFFFF), 
	//which is the valid MIPS range for 16-bit immediates
	if(PARAM3.value>0xFFFF)
	{
		state = INVALID_IMMED;
		return; 
	}
	//Set opcode bits [31–26] to binary for ORI
	setBits_str(31, "001101");
	//Encode the source register ($rs) into bits
	setBits_num(25, PARAM2.value, 5); 
	//Encode the target register ($rt) into bits
	setBits_num(20, PARAM1.value, 5);
	//Encode the immediate constant into bits 
	setBits_num(15, PARAM3.value, 16);
	
	//marks end of the encoding process(successful)
	state = COMPLETE_ENCODE; 
}

void ori_immd_bin(void) {

	//verifies the instructions opcode bits so they match ORI
	//if not it is the wrong instruction and returns
	if(!checkBits(31, "001101"))
	{
		state = WRONG_COMMAND;
		return; 
	}

	//Extract bits [25–21] → source register (rs)
	uint32_t rs = getBits_num(25, 5);
	//Extract bits [20–16] → target register (rt)
	uint32_t rt = getBits_num(20, 5);
	//Extract bits [15–0] → immediate constant
	uint32_t immediate = getBits_num(15, 16);

	// Set the operation to "ORI"
	setOp("ORI");
	//Set parameter 1 → destination register ($rt)
	setParam(1, REGISTER, rt);
	//Set parameter 2 → source register ($rs)
	setParam(2, REGISTER, rs);
	//Set parameter 3 → immediate constant
	setParam(3, IMMEDIATE, immediate);
	
	//marks end of the decoding process(successful)
	state = COMPLETE_DECODE; 
}



