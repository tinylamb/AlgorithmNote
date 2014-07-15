/*
 * =========================================================
 *       Filename:  main_void.c
 *    Description:  int main(void) 与 int main()在c中的区别
 *
 * =========================================================
 */
#include <stdio.h>
// Program 1 (Compiles and runs fine in C, but not in C++)
void fun() {  } 
int main(void)
{
    fun(10, "GfG", "GQ");
    return 0;
}

/* // Program 2 (Fails in compilation in both C and C++)
 * void fun(void) {  }
 * int main(void)
 * {
 *     fun(10, "GfG", "GQ");
 *     return 0;
 * }
 */

/* So the difference is, in C, int main() can be called with any 
 * number of arguments, but int main(void) can only be called without
 * any argument. Although it doesn’t make any difference most of the
 * times, using “int main(void)” is a recommended practice in C.
 */
