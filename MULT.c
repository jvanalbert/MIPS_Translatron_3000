#include "Instruction.h"


// will do later


void mult_reg_assm(void) {
   if (strcmp(OP_CODE, "MULT") !=0) {
       state = WRONG_COMMAND;
       return;
   } // This makes sure that MULT is currently in the opcode
   if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
       state = MISSING_REG;
       return;
   } // This checks to make sure no registers are missing in mult $rs, $rt
  
   //instruction layout:
   setBits_num(31, 0, 6); // opcode = 000000
   setBits_num(25, PARAM1.value, 5); //rs
   setBits_num(20, PARAM2.value, 5); //rt
   setBits_num(15, 0, 5); // rd = not used
   setBits_num(10,0,5); //shamt = 0
   setBits_num(5, 24, 6); // function = 011000 (24)


   state = COMPLETE_ENCODE;
}  


void mult_reg_bin(void) {
   if (checkBits(31, "000000") == 0 && checkBits(5, "011000") == 0) {
       setOp("MULT"); //checks the opcode and function bits to make sure this is a mult


       setParam(1, REGISTER, getBits(25,5)); //extracts register field for rs
       setParam(2, REGISTER, getBits(20, 5)); //extracts register field for rt


       state = COMPLETE_DECODE;
   } else {
       state = WRONG_COMMAND;
   }
}

// Here, multiple parts of the code were updated.  The first function mult_reg_assm was added to to 1. Make sure
// the MULT function is currently in the opcode. 2. Check the parameter type and make sure that there are no
// registers missing, otherwise an error will occur. 3. Establish a layout for the instructions by specifying
// their bit values (for example, opcode is 6 bits, starting at 31, rs is 5 bits starting at 25 (counts down))
// Next, the mult_reg_bin function was updated.  The following changes were 1. an if statement that checks to
// make sure the opcode and function bits are present and correct, which verifies the mult function status and
// extracts the register field for rs and rt from that mult function.  If the if statement is not true, an
// error will occur.
