/*
 * log.h
 *
 * Omschrijving:	Logging en profiling functies die naar std{out/err} schrijven
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_LOG_H_
#define SOFTWARE_LOG_H_

#include <chrono>

#include "sys/alt_stdio.h"

/**
 * Switch om logging aan/uit te zetten
 **/
//#define LOG_ENABLE // comment deze regel uit als je logging niet wilt gebruiken

#ifdef LOG_ENABLE

/**
 * Print een informatiebericht naar stdout.
 **/
#define LOG_INFO(format, ...)	printf("INFO | " format "\n", ##__VA_ARGS__)

/**
 * Print een foutmelding naar stdout.
 **/
#define LOG_ERROR(format, ...)	fprintf(stderr, "ERROR | " format "\n", ##__VA_ARGS__)

/**
 * Print een initialisatiebericht naar stdout.
 **/
#define LOG_INIT_MSG(component)    (LOG_INFO(component " is geinitialiseerd"))

/**
 * Meet hoe lang het uitvoeren van een functie duurt.<br />
 * <br />
 * In het logbericht wordt het aantal milliseconden vermeld,
 * dus het zal alleen handig zijn voor functies die lang duren.
 **/
#define LOG_MEASURE(stmt) \
	{ \
		auto start = std::chrono::high_resolution_clock::now(); \
		stmt; \
		auto end = std::chrono::high_resolution_clock::now(); \
		std::chrono::duration<double> diff = end - start; \
		std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(diff); \
		LOG_INFO(#stmt " duurde %d ms", d.count()); \
	}

#else
#define LOG_INFO(format, ...)	({(void)0;})
#define LOG_ERROR(format, ...)	({(void)0;})
#define LOG_MEASURE(stmt)		stmt
#define LOG_INIT_MSG(component) ({(void)0;})
#endif

#endif /* SOFTWARE_LOG_H_ */
