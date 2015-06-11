#ifndef __U_ASSERT_H__
#define __U_ASSERT_H__

/** assertions */
#ifdef UNIQUE_NAME
#undef UNIQUE_NAME
#endif

#define UNIQUE_NAME                     MAKE_NAME(__LINE__)
#define MAKE_NAME(line)                 MAKE_NAME2(line)
#define MAKE_NAME2(line)                constraint_ ## line

#define COMPILE_TIME_ASSERT(expr)       char UNIQUE_NAME[(expr)]; (void)UNIQUE_NAME[];
#define COMPILE_TIME_ASSERT_FN(pred)    switch(0){case 0:case pred:;}              

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define STATIC_ASSERT(e) \
    { enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }; }
    
#define MAX_LINE 255   /* max number of lines of a file */

#ifdef U_ASSERT_FN

void compile_time_assertions(void);

#pragma push   
#pragma MESSAGE DISABLE C5908 /* constant switch expression */

void compile_time_assertions(void)
{
    COMPILE_TIME_ASSERT_FN((NUM_PT <= MAX_NUM_PT));  /* check max pt. number */
}
#pragma pop /* constant switch expression */
#endif

#endif
