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
 * \file
 * System tasks
 * \author
 * Carlos H. Barriquello <barriquello@gmail.com>
 *
 */

#include "ufsm-rtos.h"

#if (CONF_U_CORE_SCHED_OPT == 1)

const u08 U_SCHED_TABLE[] = {
  0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,  /* 0x00 to 0x0F */
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  /* 0x10 to 0x1F */
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  /* 0x20 to 0x2F */
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  /* 0x30 to 0x3F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x40 to 0x4F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x50 to 0x5F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x60 to 0x6F */
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,  /* 0x70 to 0x7F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0x80 to 0x8F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0x90 to 0x9F */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xA0 to 0xAF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xB0 to 0xBF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xC0 to 0xCF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xD0 to 0xDF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xE0 to 0xEF */
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  /* 0xF0 to 0xFF */
};

#elif (CONF_U_CORE_SCHED_OPT == 2)

const u08 U_SCHED_TABLE[] = {
  0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,  /* 0x00 to 0x0F */
};

#endif


/*---------------------------------------------------------------*/
/******************* scheduler ***************/

u08 u_sched(u_prio_list_t list){

#if (CONF_U_CORE_SCHED_OPT == 0)
	 u16 list_tmp16;
	 u08 list_tmp, off;

	if(list.w[1] > 0)
	{
		list_tmp16 = list.w[1];
		off=16;
	}else
	{
		list_tmp16 = list.w[0];
		off=0;
	}

    if (list_tmp16 > 0xFF)
    {
        list_tmp = (u08)(list_tmp16 >> 8);
        off += 8;
    }else
    {
        list_tmp = (u08)list_tmp16;
        off += 0;
    }


    if (list_tmp > 0x0F)
    {
      if (list_tmp > 0x3F)
      {
        if (list_tmp > 0x7F)
        {
          return off+7;
        }
        else
        {
          return off+6;
        }
      }
      else
      {
        if (list_tmp > 0x1F)
        {
          return off+5;
        }
        else
        {
          return off+4;
        }
      }
    }
    else
    {
      if (list_tmp > 0x03)
      {
        if (list_tmp > 0x07)
        {
          return off+3;
        }
        else
        {
          return off+2;
        }
      }
      else
      {
        if (list_tmp > 0x01)
        {
          return off+1;
        }
        else
        {
          return off+0;
        }
      }
    }
#elif (CONF_U_CORE_SCHED_OPT == 1)

    u16 list_tmp16;
    u08 list_tmp;
    u08 off = 0;

    if(list.w[1] > 0)
    {
    	list_tmp16 = list.w[1];
    	off = 16;
    }else
    {
    	list_tmp16 = list.w[0];
    	off = 0;
    }

    if (list_tmp16 > 0xFF)
    {
      list_tmp = (u08) (list_tmp16 >> 8);
      return (U_SCHED_TABLE[list_tmp] + 8 + off);
    }else
    {
      list_tmp = (u08)list_tmp16;
      return (U_SCHED_TABLE[list_tmp] + off);
    }

#elif (CONF_U_CORE_SCHED_OPT == 2)

    u16 list_tmp16;
    u08 list_tmp;
    u08 off = 0;

	if(list.w[1] > 0)
	{
		list_tmp16 = list.w[1];
		off = 16;
	}else
	{
		list_tmp16 = list.w[0];
		off = 0;
	}

    if (list_tmp16 > 0xFF)
    {
      list_tmp = (u08) (list_tmp16 >> 8);
      if (list_tmp > 0x0F)
      {
         list_tmp = (u08) (list_tmp >> 4);
         return (U_SCHED_TABLE[list_tmp] + 12 + off);
      }else
      {
         return (U_SCHED_TABLE[list_tmp] + 8 + off);
      }
    }else
    {
      list_tmp = (u08)list_tmp16;
      if (list_tmp > 0x0F)
      {
         list_tmp = (u08) (list_tmp >> 4);
         return (U_SCHED_TABLE[list_tmp] + 4 + off);
      }else
      {
         return (U_SCHED_TABLE[list_tmp] + off);
      }
    }

#endif
}




