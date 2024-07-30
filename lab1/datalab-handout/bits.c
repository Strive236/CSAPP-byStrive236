/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * Strive236 without userid
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 由布尔代数：a^b = ~(~(a & (~b)) & ~(b & (~a)))
  return ~(~(x & (~y)) & ~(y & (~x)));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // tmin为10000...000, 右移31位即可
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // 确定符号, x + 1为10...0, x为01...1，相与后取反为00...0，！其值为1
  int flag = !(~((x + 1) ^ x));
  // 上面那个方法有一种特殊情况，即-1(11...1)，在溢出时也满足此条件
  // 利用正数性质，排除掉-1，-1 + 1后为0, 而01...1加1后不会为0
  int not_minus1 = !!(x + 1);
  return flag & not_minus1; 
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 将x中每个字节全部提取出来与0b10101010(0xaa)相与, 可得奇数位上情况, 最后再加上0b01010101(0x55), 再+1, 若第8位为1, 即成功
  x = (x >> 24) & (x >> 16) & (x >> 8) & x & 0xaa;
  x = (x | 0x55) + 1;
  return (x >> 8);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 补码为按位取反后+1
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // 0x30 - 0x39即0b00110000 - 0b00111001
  // 首先确保为正数，然后检查第4、5位是否为1，最后再用0x39来+上x的补码(即0x39 - x)，如果符号位不变位就搞定
  return (~(x >> 31)) & (x >> 4) & (x >> 5) & 1 & (~((0x39 + (~x) + 1) >> 31));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 1左移31为10...0，然后右移31为11...1
  // 0左移31为00...0，然后右移31为00...0
  int flag = ((!!x) << 31) >> 31; // flag为全1表示x大于0，为全0表示x<=0，用其来&y或z便能达到控制值的效果
  return (flag & y) | ((~flag) & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // 将x <= y转换成x - y <= 0, 去观察x - y
  // x - y有以下几种情况
  // x, y同号，不会溢出，直接取决于最终结果是否<=0
  // x为负数，y为正数，x - y 如果不溢出则还是负数，如果溢出符号位会变，会变成正数
  // x为正数，y为负数，x - y 如果不溢出则还是正数，如果溢出符号位会变，会变成负数
  // x <= y有两种情况：1. xy同号且x-y<=0 2. x为负y为正
  int x_minux_y = x + (~y) + 1;
  int x_minux_y_lessOrEqual = (x_minux_y >> 31) | (!x_minux_y & 1);
  // xy同号
  int same_sign = (~((x ^ y) >> 31)) & 1;
  int x_negative_y_positive = (x >> 31) & (~(y >> 31)) & 1;
  int res = (same_sign & x_minux_y_lessOrEqual) | x_negative_y_positive;
  return res;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // return: 如果是0则为1, 其他则为0
  // (!x) 实际上为 x==0
  // 破局点：0-1即(0 + (~1 + 1)) 二进制表示为11...1, 符号位会变号 
  int sign_x = (~(x >> 31) & 1); // 符号位为0
  int x_minus_1 = x + (~1 + 1); // 0-1后的值
  int sign_x_minus_1 = (x_minus_1 >> 31) & 1; // -1后符号位为1
  int zero = sign_x & sign_x_minus_1;
  return zero;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // 样例描述：
  // 12: 0b0 1100
  // 298: 0b01 0010 1010
  // return: 符号位(1位) + 除符号位外用来表示该数所需位数 
  // 二分法：5位2进制数可表示0 - 31，最后再+1即可(每次选一半来检查，选有1的那边)
      int sign, bit16, bit8, bit4, bit2, bit1, bit0;
    
    // 获取符号位
    sign = x >> 31;
    
    // 如果是负数，将其取反
    x = (sign & ~x) | (~sign & x);
    
    // 二分查找最高位的1
    bit16 = !!(x >> 16) << 4;  // 检查16位是否有1 若有1则bit16为10000，反之为0
    x = x >> bit16;  // 如果有，右移16位
    
    bit8 = !!(x >> 8) << 3;  // 检查8位是否有1
    x = x >> bit8;
    
    bit4 = !!(x >> 4) << 2;  // 检查4位是否有1
    x = x >> bit4;
    
    bit2 = !!(x >> 2) << 1;  // 检查2位是否有1
    x = x >> bit2;
    
    bit1 = !!(x >> 1);  // 检查次高位是否为1
    x = x >> bit1;
    
    bit0 = x;  // 检查最后一位
    
    // 计算总位数并加上符号位
    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // 举例：0b   1    000 0101 0     111 0011 1010 1011 0101 1111
  //         sign        exp                  frac
  unsigned sign = uf >> 31 & 1;
  unsigned exp = uf >> 23 & 0xff;
  unsigned frac = uf & 0x7fffff;

  // 如果exp全为1, 即数为NaN或无穷大, 即x2无意义，直接返回参数
  if (exp == 0xff) return uf;

  // 如果exp全为0，则直接frac左移一位即可
  if (!exp) {
    frac = frac << 1;
  }
  else {
    // 如果exp不全为0，则+1
    exp = exp + 1;
    
    // 如果exp+1后全为1且frac不为0, 即数为NaN, 直接返回参数
    if ((exp == 0xff) && (frac != 0)) return uf;
  }

  return (sign << 31) + (exp << 23) + frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // 提取各部分
  unsigned sign = uf >> 31 & 1;
  unsigned exp = uf >> 23 & 0xff;
  unsigned frac = uf & 0x7fffff;
  int e = -23;

  // 如果exp全为1, 即数为NaN或无穷大, 返回0x80000000u
  if (exp == 0xff) return 0x80000000u;
  // 如果exp全为0，小数部分为0.frac, 判断是否为-0
  else if (exp == 0x0) {
    // 如果为-0
    if ((sign == 1) && (!frac)) return 0;
    else {
      e = e + exp - 127;
    }
  } 
  // 其他情况, exp为1-254之间值，小数部分为1.frac
  else {
    e = e + exp - 127;
    frac = frac | 0x800000; // 将0.frac改成1.frac
  }

  // 判断e正负号决定左移右移, 注意e绝对值大于等于32时会有意想不到的效果
  if (e <= -32) return 0;
  else if (e >= 32) return 0x80000000u;
  else if (e >= 0) frac = frac << e;
  else frac = frac >> (-e);
  
  // -0特殊处理
  if ((frac == 0) && (sign == 1)) return 0; 

  // 此时处理出来结果是unsigned，还需要转成int
  if (sign == 1) return -(frac & 0xffffffff); // 负数取补码
  else return frac; // 正数直接取
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    // 用浮点数来表示2^x次方，实际上就是操作浮点数的指数部分

    if (x + 127 <= 0) return 0;
    if (x + 127 > 254) return 0x7f800000;  // 返回+INF
    
    // sign必为0
    // frac为0，exp为x + 127
    return (x + 127) << 23;
}
