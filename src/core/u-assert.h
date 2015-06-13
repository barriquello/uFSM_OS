/*
 * Copyright (c) 2015, Universidade Federal de Santa Maria.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uFSM real time operating system.
 *
 * Author: Carlos H. Barriquello <barriquello@gmail.com>
 *
 */
/**
 * \file u-assert.h
 * Implementation of static assertions
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#ifndef __U_ASSERT_H__
#define __U_ASSERT_H__

/** assertions */
#ifdef UNIQUE_NAME
#undef UNIQUE_NAME
#endif

#define UNIQUE_NAME                     MAKE_NAME(__LINE__)
#define MAKE_NAME(line)                 MAKE_NAME2(line)
#define MAKE_NAME2(line)                constraint_ ## line

#define COMPILE_TIME_ASSERT(expr)       char UNIQUE_NAME[(expr)];
#define COMPILE_TIME_ASSERT_FN(pred)    switch(0){case 0:case pred:;}              

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)

#if 1
#define STATIC_ASSERT(e)  \
    { enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!((e))) }; }
#else
#define STATIC_ASSERT(e)	do{}while((e));
#endif
    
#define MAX_LINE 65536   /* max number of lines of a file */

#ifdef U_ASSERT_FN

void compile_time_assertions(void);

#pragma push   
#pragma MESSAGE DISABLE C5908 /* constant switch expression */

void compile_time_assertions(void)
{
    COMPILE_TIME_ASSERT_FN((U_NUM_TASKS <= MAX_NUM_U_TASKS));  /* check max utasks number */
}
#pragma pop /* constant switch expression */
#endif

#endif
