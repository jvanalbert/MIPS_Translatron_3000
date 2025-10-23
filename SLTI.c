/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// give this to the intern

// Previously was incorrectly treating PARAM3 as register, now correctly handles immediate values

#include "Instruction.h"

void slti_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "SLTI") != 0) {
		// If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters 
		SLTI format: SLTI $rt, $rs, immediate
	*/

	// The first parameter should be a register (destination)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be a register (source)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// CHANGE: Fixed parameter type check - PARAM3 should be IMMEDIATE, not REGISTER
	// This was the main bug - SLTI uses immediate value, not a third register
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}
	/*
		Checking the value of parameters
	*/

	// CHANGE:register validation - check both registers in one condition
	// Rt (PARAM1) and Rs (PARAM2) should both be 31 or less (valid register numbers)
	if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

	// CHANGE: Added proper immediate value range validation for 16-bit signed immediate
	// SLTI uses 16-bit signed immediate: range −2¹⁵ to 2¹⁵−1 (-32768 to 32767)
	// This is different from SLT which only uses 5-bit register values
	if (PARAM3.value < -32768 || PARAM3.value > 32767) {
		state = INVALID_IMMED;
		return;
	}
	/*
		Putting the binary together - I-type instruction format
		SLTI format: | opcode(6) | rs(5) | rt(5) | immediate(16) |
	*/

	// CHANGE: Set correct SLTI opcode (001010 = 0x0A = 10)
	// Different from SLT which uses opcode 000000 with function field
	setBits_num(31, 10, 6); // SLTI opcode = 0x0A (001010 in binary)

	// CHANGE: Corrected bit field assignments for I-type format
	setBits_num(25, PARAM2.value, 5); // rs - source register (bits 25-21)
    setBits_num(20, PARAM1.value, 5); // rt - destination register (bits 20-16)
    setBits_num(15, PARAM3.value, 16); // immediate - 16-bit signed immediate (bits 15-0)

    // Tell the system the encoding is complete
    state = COMPLETE_ENCODE;

}

void slti_immd_bin(void) {
	// CHANGE: Updated binary decoding for I-type SLTI instruction
	// Check if the opcode bits match SLTI (001010 = 0x0A)
	// checkBits(start_bit, bit_string) returns 0 if the bit_string matches
    if (checkBits(31, "001010") != 0) {
        state = WRONG_COMMAND;
        return;
    }
	
	// If the opcode bits match, then the rest can be read correctly
	
	/*
		Finding values in the binary - I-type instruction format
		SLTI format: | opcode(6) | rs(5) | rt(5) | immediate(16) |
	*/
	// getBits(start_bit, width)
	uint32_t rs  = getBits(25, 5);  // Source register (bits 25-21)
    uint32_t rt  = getBits(20, 5);  // Destination register (bits 20-16)
    // CHANGE: Proper sign extension of 16-bit immediate value
    int16_t imm  = (int16_t)getBits(15, 16); // 16-bit signed immediate (bits 15-0)

	/*
		Setting Instruction values
	*/
	setOp("SLTI");
	// CHANGE: Corrected parameter assignments to match SLTI semantics
    setParam(1, REGISTER, rt);     // Destination register ($rt)
    setParam(2, REGISTER, rs);     // Source register ($rs)  
    setParam(3, IMMEDIATE, imm);   // 16-bit signed immediate value

    // Tell the system the decoding is complete
    state = COMPLETE_DECODE;
}





