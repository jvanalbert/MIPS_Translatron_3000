/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/


#include "Instruction.h"


void sub_reg_assm(void) {
   // Checking that the op code matches
   // strcmp(string1, string2) return 0 if they match
   if (strcmp(OP_CODE, "SUB") != 0) {
       // If the op code doesnt match, this isnt the correct command
       state = WRONG_COMMAND;
       return;
   }


   /*
       Checking the type of parameters
   */


   // Generally the first parameter should always be a register
   if (PARAM1.type != REGISTER) {
       state = MISSING_REG;
       return;
   }


   // This is SUB register, so param 2 needs to be a register
   if (PARAM2.type != REGISTER) {
       state = MISSING_REG;
       return;
   }


   // This is SUB register, so param 3 needs to be a register
   if (PARAM3.type != REGISTER) {
       state = MISSING_REG;
       return;
   }




   /*
       Checking the value of parameters
   */


   // Rd should be 31 or less
   if (PARAM1.value > 31) {
       state = INVALID_REG;
       return;
   }


   // Rs should be 31 or less
   if (PARAM2.value > 31) {
       state = INVALID_REG;
       return;
   }


   // Rt should be 31 or less
   if (PARAM3.value > 31) {
       state = INVALID_REG;
       return;
   }


  


   /*
       Putting the binary together
   */


   // Set the opcode
   setBits_num(31, 0, 6);


   // Set rs
   setBits_num(25, PARAM2.value, 5); // Wrong, changed by Maggie to setBits_num(25, PARAM2.value, 5)


   // set Rt
   setBits_num(20, PARAM3.value, 5); // Wrong, changed by Maggie


   // set Rd
   setBits_num(15, PARAM1.value, 5); // Wrong, changed by Maggie


   // shamt = 00000
   setBits_num(10, 0, 5); // Wrong, changed by Maggie


   // funct = 100010
   setBits_str(5, "100010"); // added by Maggie, correct SUB opcode, originally ADD opcode


   // tell the system the encoding is done
   state = COMPLETE_ENCODE;
}


void sub_reg_bin(void) {
   // Check if the op code bits match
   // check_bits(start_bit, bit_string) returns 0 if the bit_string matches
   // any x will be skipped
   // If the manual shows (0), then the value of that bit doesn't matter
   if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0 ) { // 100100 is the function for ADD, not SUB; Maggie changed this
       state = WRONG_COMMAND;
       return;
   }


   // If the op code bits match, then the rest can be read as correctly


   /*
       Finding values in the binary
   */
   // getBits(start_bit, width)
   uint32_t Rs = getBits(25, 5); // changed the order so it is Rs, Rt, Rd
   uint32_t Rt = getBits(20, 5);  
   uint32_t Rd = getBits(15, 5);


   /*
       Setting Instruction values
   */


   setOp("SUB");
   //setCond_num(cond);
   //setParam(param_num, param_type, param_value)
   setParam(1, REGISTER, Rd); //destination
   setParam(2, REGISTER, Rs); //first source register operand
   setParam(3, REGISTER, Rt); //second source register operand




   // tell the system the decoding is done
   state = COMPLETE_DECODE;
}


