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
  * @file:      RINGBUF.h
  * @author:    anhgiau (nguyenanhgiau1008@gmail.com)
  * @version:   1.0.1
  * @date:      6/24/2018
  * @brief:     Header file of RINGBUF
  ******************************************************************************
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RINGBUF_H
#define __RINGBUF_H
 
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "INCLUDES.h"
/* Exported Define -----------------------------------------------------------*/
#define RINGBUF_NONE_ERR                (0)
#define RINGBUF_ERR_PTR_NULL            (-1)
#define RINGBUF_ERR_FULL                (-2)
#define RINGBUF_ERR_EMPTY               (-3)
/* Exported Typedefs ---------------------------------------------------------*/
typedef struct{
  INT32U        head;
  INT32U        tail;
  INT32U        size;
  INT8U         *p_data;
}RINGBUF_t;
/* Exported Structure Declarations -------------------------------------------*/
/* Exported Functions Declarations -------------------------------------------*/

/**
  * @brief:  This function is called to initialize buffer
  * @param:  
  *     - 'r' is a pointer to RINGBUF_t, 
  *     - 'pt' is a pointer to array where stored data, 
  *     - 'size' is a size of buffer
  * @retval: RINGBUF_NONE_ERR if successful
  */
INT8S RINGBUF_Init(RINGBUF_t *r, INT8U *pt, INT32U size);

/**
  * @brief:  This function is called to add 1 BYTE data into buffer
  * @param:  
  *     -'r' is a pointer to RINGBUF_t, 
  *     -'data' value need to add into
  * @retval: RINGBUF_NONE_ERR if successful
  */
INT8S RINGBUF_PutChar(RINGBUF_t *r, INT8U data);

/**
  * @brief:  This function is called to get 1 BYTE data from buffer
  * @param:  
  *     -'r' is a pointer to RINGBUF_t, 
  *     -'data' value need to add into
  * @retval: RINGBUF_NONE_ERR if successful
  */
INT8S RINGBUF_GetChar(RINGBUF_t *r, INT8U *data);

/* External Variable Declarations --------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /*__RINGBUF_H*/
/************************ (C) COPYRIGHT anhgiau ****************END OF FILE****/
