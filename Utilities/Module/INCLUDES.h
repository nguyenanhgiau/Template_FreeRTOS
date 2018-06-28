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
  * @file:      INCLUDES.h
  * @author:    anhgiau (nguyenanhgiau1008@gmail.com)
  * @version:   1.0.1
  * @date:      6/24/2018
  * @brief:     Header file of INCLUDES
  ******************************************************************************
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INCLUDES_H
#define __INCLUDES_H
 
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/* Exported Define -----------------------------------------------------------*/
/* Exported Typedefs ---------------------------------------------------------*/
typedef unsigned char   BOOLEAN;

typedef unsigned char   INT8U;

typedef signed char     INT8S;

typedef unsigned int    INT16U;

typedef signed int      INT16S;

typedef unsigned long   INT32U;

typedef signed long     INT32S;

typedef float           FP32;

typedef double          FP64;

#ifndef NULL
#define NULL    '\0'
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif
/* Exported Structure Declarations -------------------------------------------*/
/* Exported Functions Declarations -------------------------------------------*/
/* External Variable Declarations --------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /*__INCLUDES_H*/
/************************ (C) COPYRIGHT anhgiau ****************END OF FILE****/
