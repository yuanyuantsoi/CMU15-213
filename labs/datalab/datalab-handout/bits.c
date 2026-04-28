/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * yuanyuantsoi
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

/*
 * 解题思路：
 * 一句话模型： x ^ y = (x & ~y) | (~x & y);通过德摩根公式转换为只有符号～和&
 * 核心技巧：x^y用与或非表达式和德摩根公式
 * 最简代码： ~(~(x & ~y) & ~(~x & y));
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
  return ~(~(x & ~y) & (~(~x & y)));
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
/*
 * 解题思路：
 * 一句话模型：
 * 	tmin = -2^(w-1), w bit的int
 * 核心技巧：
 * 左移低位补0，因此将1左移(w - 1)位即可得到该数
 * 对于32位int(w = 32),即1 << 31
 *
 * 最终代码： 1 << 31;
 */

int tmin(void) {
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

/*
 * 解题思路：
 * 一句话模型：
 * 利用tmax的特点： tmax + 1 = tmin; ~tmin = tmax;
 *
 * 如果x = tmax, 则：
 * 	x == ~(x + 1)
 * 由于-1也符合这个规则，则需要排除掉-1
 *
 * 核心技巧：
 * 利用tmin = tmax + 1; tmax = ~tmin;
 * 排除掉-1;
 *
 * 代码实现：
 * 先根据tmax的特殊性质筛选出来，在通过!isNegOne排除掉-1;
 *
 */
int isTmax(int x) {
	int isSpecial, isNegOne;
	isSpecial = !(x ^ (~(x + 1)));
	isNegOne = !(x + 1);
  return isSpecial & !isNegOne;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */

/*
 * 解题思路：
 * 构造mask = 0xAAAAAAAA
 * 由于常量限制0x0-0xFF, 通过拼接0xAA得到完整mask
 * 
 * 判断逻辑：
 * 1. x & mask -> 提取所有奇数位
 * 2. 如果这些为全为1，则应等于mask
 * 3. 使用异或判断是否相等
 * 	(x & mask) ^ mask == 0 --> 表示完全匹配
 * 4. 用！转换为布尔值
 */
int allOddBits(int x) {
	int mask;
	mask = 0xAA;
	mask = (mask << 8) | mask;
	mask = (mask << 16) | mask;
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 *
 *   解题思路：
 *   根据原码和补码(2's complement)的关系：-x = ~x + 1
 *
 *   相关知识点：
 *   统一加法和减法使得 a-b = a + (-b)
 *   如何表示-b:
 *   	计算机本质为模运算 2^n
 *   	-x = 2^n - x  --> 例如 -3 = 16 - 3
 *   	-x = 2^n - 1 - x + 1
 *   	   = (2^n - 1 - x) + 1  --> 2^n - 1 - x = ~x
 *   	   = ~x + 1
 */
int negate(int x) {
  return ~ x + 1;
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
 * 
 * 解题思路一：(溢出风险）
 * 0x30 <= x <= 0x39 
 * 1. 根据two's complement的符号位表示规则，最高位为0为正数，最高位为1为负数
 *    asciiDigit的范围等价于
 *   	 x - 0x30 >=0 && x - 0x3a < 0
 * 2. 由于操作符限制无法使用减法，根据2‘s complement负数 -x = ~ x + 1,可得到：
 * 	 -0x30 = ~0x30 + 1
 * 	 -0x40 = ~0x3a + 1
 *    left = x - 0x30 = x + (~0x30 + 1) 
 *    right = x - 0x3a = x + (~0x3a + 1)
 *  
 * 3. 通过left >> 31, right >> 31（Arithmtic right shift高位补充符号位）得到
 *    left和right的符号位扩展
 *    	当 left为0x0, right为0xFFFFFFFF时，x为asciiDigit
 *    	 return ~left & right;
 *
 *
 * 解题思路二：
 *  1. 利用位运算判断每位是否在范围内:
 *  	x的高28位应该为0x3
 *  	x的低四位应为0x0~0x9
 *  2. 通过移位和异或判断高位
 *  	high = !((x >> 4) ^ 0x3); 高位为3时，结果为1
 *  3. 通过是否产生进位，判断是否在范围内
 *  	low = x & 0xf
 *  	le9 = !((x + 0x6) >> 4);
 *     若x + 0x6的第5位没有进位，则low <= 9
 */
int isAsciiDigit(int x) {
	int high, low, le9;
	high = !((x >> 4) ^ 0x3);
	low = x & 0xf;
	le9 = !((low + 0x6) >> 4);

  return high & le9;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 *
 *   解题思路：
 *   一句话模型：
 *    x ? y : z -> x 等价于 x为非0值时，选y; x为0时选z
 *
 *   核心技巧：
 *   	通过mask选择y和z
 *   	 (mask & y) | (~mask & z)
 *	
 *	通过!!x把x规整为0/1
 *	当!!x为0时
 *		0 << 31 >> 31 = 0x00000000
 *		mask全0选择z
 *	当!!x为1时
 *		1 << 31 >> 31 = 0xFFFFFFFF
 *		mask全1选择y
 */
int conditional(int x, int y, int z) {
	int mask = ((!!x) << 31) >> 31;
  return  ((mask & y) | (~mask & z));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 *
 * 解法思路：
 *  一句话模型： 
 *  x <= y
 *  1. 异号时
 *  	- 如果x为负数，则x <=y 成立
 *  2. 同号时
 *  	- 判断x - y 是否< 0
 *  3. x = y
 *
 *  核心技巧：
 *  - isEqual: x==y
 *  - oppFlag: x ^ y的符号位，异号时为全1，否则为0
 *  - diffSign: x - y 的符号，负数时为全1
 *  - signX: x的符号，负数时为全1
 */
int isLessOrEqual(int x, int y) {
	int isEqual, oppFlag, diffSign, signX;
	isEqual = !(x ^ y);
	oppFlag = (x ^ y) >> 31;
	diffSign = (x + (~y) + 1) >> 31;
	signX = x >> 31;

  return !!(isEqual | (oppFlag & signX) | ((~oppFlag) & diffSign));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 *
 *   解法思路：
 *   	！x = x所有位相或再取反
 *
 *   核心技巧：
 *   	1. 位折叠（移位和或）得到x所有位相或，结果保存在lsb位
 *   	2. mask lsb位，再取反，得到!x
 *   	
 */
int logicalNeg(int x) {
  x = x | (x >> 16);
  x = x | (x >> 8);
  x = x | (x >> 4);
  x = x | (x >> 2);
  x = x | (x >> 1);
  return (~x & 0x1) ;
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
 * 
 * 解法思路：
 * 	x为正数时，找到最高位1的位置
 * 	x为负数时，找到最高位0的位置
 *
 * 核心技巧：
 * 	x ^ (x >> 31)
 * 		- x为正时，不变；
 * 		- x为负时，按位取反
 * 	将问题统一为寻找最高位1
 * 	利用二分查找法，查找1的位置
 * 	 - b16: !!(x >> 16) 高16位有1时结果为1，否则为0
 * 	 	!!(x >> 16) << 4，高位有1则等于16，无1则为0，可表示位移次数
 * 	 - b8, b4, b2, b0同理
 * 	 - b0: 为1时，权重为1
 * 	       为0时，权重为0
 *       - totalbits = b16 + b8 + ... + b2 + b1 + b0 + 1
 *       因为b16 + b8...+ b0得到最高位1的位置(长度而非index),但表示two's complement
 *       需要一位额外的符号位，所以需要加1
 *
 */
int howManyBits(int x) {
	int total_bits, b16, b8, b4, b2, b1, b0;

	x = x ^ (x >> 31);

	total_bits = 0;
	b16 = (!!(x >> 16)) << 4; //高位有1时，为1；无1时为0；
	x = x >> b16; //x为高16位或低16位
	
	b8 = (!!(x >> 8)) << 3;
	x = x >> b8;

	b4 = (!!(x >> 4)) << 2;
	x = x >> b4;

	b2 = (!!(x >> 2)) << 1;
	x = x >> b2;

	b1 = (!!(x >> 1));
	x = x >> b1;

	b0 = x;

	total_bits = b16 + b8 + b4 + b2 + b1 + b0 + 1;


  return total_bits;
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
 *
 *   解法思路：
 *   	32-bit的single float point argument f中
 *   	分别是：s bit(1位）+  exp(8位) + frac(23位)
 *   	2*f = (-1)^s * M * 2^E,bias = 2^7-1 = 127
 *   	 - e为全0(denormalized)
 *   	 	- M = 0.frac; E = 1 - bias;
 *   	 	- frac << 1表示2*f,若frac最高位为1，E不变，e=e + 1,f从denormalized变为normalized
 *   	 - e为全1（+/-无穷 / NAN）
 *   	 	- +/-∞ * 任何数 = +/- ∞, e不变，frac << 1
 *   	 	- nan, return f unchanged
 *       - e为非特殊值(normalized)
 *       	- M = 1 + f, E = e - bias
 *       	- M不变，E + 1来表示2*f, e = e + 1
 */
unsigned floatScale2(unsigned uf) {
     unsigned e = (uf >> 23) & 0xff;
     unsigned fMask = 0x7fffff;
     unsigned f = uf & fMask;  //Alternative: (f << 9) >> 9 extract the lower 23 bits 
     unsigned s = (uf >> 31) & 1;
     unsigned result;

     if (e == 0x0) {
	     unsigned msbF = (f >> 22) & 1;
	     f = (f << 1) & fMask;
	     if (msbF == 1) {
		     e = e + 1;
	     }
     } else if (e == 0xff) {
	     if (f == 0) {
		     f = (f << 1) & fMask;
	     } else {
		     return uf;
	     }
     } else {
	     e = e + 1;
     }

     result = (s << 31) + (e << 23) + f;

  return result;
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
 *  
 *  解法思路：
 *   将IEEE 754 single precision float 转成int.
 *
 *   字段：
 *    sign: 1 bit
 *    exp: 8 bits
 *    frac: 23 bits
 *
 *   Normalized:
 *   	(-1)^sign * 1.frac * 2^E
 *   	E = e - bias, bias = 127
 *
 *   核心判断：
 *     - E < 0:
 *     		|V| < 1,转int后为0
 *     - E >= 31:
 *     		超出int范围，返回0x80000000u
 *     		同时覆盖NaN/Inf,因为exp == 255时，E == 128
 *     - 0 <= E < 31:
 *     		total_bits = (1 << 23) | frac
 *     		用total_bits保存1.frac的24位有效位
 *
 *   位移规则：
 *   	- E < 23
 *   	 	float2I = total_bits >> (23 - E) //Total_bits共24位，不涉及符号位
 *   	- E >= 23:
 *   		float2I = total_bits << (E - 23)
 *   最后根据sign决定是否取反
 *
 *
 *   int范围(-1)*2^31 ~ 2^31 -1
 *   single float point表示范围大于int, 超出int范围时返回0x80000000u
 *
 *   核心技巧：
 *   	- normalized: E = e - bias, M = 1 + 0.f
 *   	    1. E >= 31, 返回0x80000000u
 *   	    2. E < 0, 返回0
 *   	    3. 0 < E < 31时, total_bits = M << 23 保存M中所有位信息
 *   	    	 - float2I = M << E
 *   		 - E > 23时，M << E --> total_bits << E - 23
 *   	    	 - E < 23时，M << E --> float2I = (total_bits >> (23 - E)) & (1 << (23 - E)));
 *   	    当sign bit 为-1时,float2I = -float2I
 *   	- denormalized: E = 1 - bias = -123, M = 0.f,超出int范围,返回0x80000000u
 *   	- Nan/Inf：E = 128,超出int范围，返回0x80000000u
 *   	其实无需考虑是否normalized/denomalized/Inf/NaN,只需考虑E的大小
 */
int floatFloat2Int(unsigned uf) {
	unsigned sign, exp, frac, total_bits, float2I; 
	int E;
	sign = (uf >> 31) & 1;
	exp = (uf >> 23) & 0xff;
	E = exp - 127;
	frac = uf & 0x7FFFFF;

	if (E < 0) {
		return 0;
	} 

	if (E >= 31) {
		return 0x80000000u;
	}


	total_bits = (1 << 23) | frac;  // used to store all bits information

	if (E < 23) {
		float2I = total_bits >> (23 - E);
	} else {
		float2I = total_bits << (E - 23);
	}

	if (sign == 1) float2I = -float2I;
  	
	return float2I;
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
	int e;
	unsigned ue;
	unsigned uf;

	 if (x <= -127) {
		 return 0;
	 } else if (x >= 128) {
		 ue = 0xff;
	 } else {
		 e = x + 127;
		 ue = e;
	 }

	 uf = ue << 23;
	 return uf;
}
