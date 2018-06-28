/**
******************************************************************************
* Copyright of anhgiau (nguyenanhgiau1008@gmail.com)
* Follow this coding style used at:
* http://www.csd.uoc.gr/~zakkak/hy255/reading/c_coding_style.pdf
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* - Development or contribute must follow this coding style.
*
* @file:      RINGBUF.c
* @author:    anhgiau (nguyenanhgiau1008@gmail.com)
* @version:   1.0.1
* @date:      6/24/2018
* @brief:     Implementation of RINGBUF
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "RINGBUF.h"

/* Private Typedef -----------------------------------------------------------*/
/* Private Define ------------------------------------------------------------*/
/* Private Structure Definition ----------------------------------------------*/
/* Global Variables ----------------------------------------------------------*/
/* Private Variables Declarations --------------------------------------------*/
/* Private Function Definitions ----------------------------------------------*/
/* Function Definitions ------------------------------------------------------*/
INT8S RINGBUF_Init(RINGBUF_t *r, INT8U *pt, INT32U size)
{
  r->head       = 0;
  r->tail       = 0;
  r->size       = size;
  r->p_data     = pt;
  return RINGBUF_NONE_ERR;
}

INT8S RINGBUF_PutChar(RINGBUF_t *r, INT8U data)
{
  INT32U tmp = r->head;
  tmp++;
  if (tmp >= r->size) {
    tmp = 0;
  }
  
  if (tmp == r->tail) {
    return RINGBUF_ERR_FULL;
  }
  
  r->p_data[r->head] = data;
  r->head = tmp;
  
  return RINGBUF_NONE_ERR;
}

INT8S RINGBUF_GetChar(RINGBUF_t *r, INT8U *data)
{
  INT32U tmp = r->tail;
  if (tmp == r->head) {
    return RINGBUF_ERR_EMPTY;
  }
  
  *data = r->p_data[tmp];
  tmp++;
  
  if (tmp == r->size) {
    tmp = 0;
  }
  
  r->tail = tmp;
  return RINGBUF_NONE_ERR;
}