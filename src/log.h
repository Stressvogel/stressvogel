/*
 * log.h
 *
 *  Created on: Dec 14, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_LOG_H_
#define SOFTWARE_LOG_H_

#include "sys/alt_stdio.h"

#ifdef LOG_ENABLE
#define LOG_INFO(format, ...)	printf("INFO | " format "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...)	fprintf(stderr, "ERROR | " format "\n", ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)	({(void)0;})
#define LOG_ERROR(format, ...)	({(void)0;})
#endif

#endif /* SOFTWARE_LOG_H_ */
