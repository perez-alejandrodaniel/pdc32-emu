#include "alu.h"

bool carry_in = false;
uint32_t alu_flags = 0;
uint32_t a = 0;
uint32_t b = 0;

uint8_t alu_get_state(){
    uint32_t alu = alu_greater_than() ? alu_greater_than_bit : 0 |
                alu_equal_than() ? alu_equals_bit : 0 |
                alu_less_than() ? alu_less_than_bit : 0;
    bool carryOut = (uint64_t) a + (uint64_t) b > 0xFFFFFFFF;
    uint32_t carryOutBit = carryOut ? 8 : 0;
    return alu | carryOutBit;
}

void alu_set_flags(uint8_t flags){
    alu_flags = flags;
}

bool alu_less_than() {
    if (a!=b) {
        return a < b;
    }
    const bool greaterThan = alu_flags & 1;
    const bool equals = alu_flags & 2;
    if(equals) return false;
    if(greaterThan) return false;
    return true;
}

bool alu_greater_or_equal_than() {
    return !alu_less_than();
}

bool alu_equal_than() {
    if(a != b) {
        return false;
    }
    return alu_flags & 2; // Equals
}

bool alu_less_or_equal_than() {
    return alu_less_than() || alu_equal_than();
}

bool alu_not_equal_than() {
    return !alu_equal_than();
}

bool alu_greater_than() {
    return !alu_less_or_equal_than();
}

uint32_t alu_get_a(){
    return a;
}
uint32_t alu_get_b(){
    return b;
}
uint32_t alu_get_sum(){
    return (carry_in ? 1 : 0) + a + b;
}
void alu_set_carry_in(bool carry){
    carry_in = carry;
}
void alu_set_a(uint32_t ax){
    a = ax;
}
void alu_set_b(uint32_t bx){
    b = bx;
}
