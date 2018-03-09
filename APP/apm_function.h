#ifndef apm_function_h
#define apm_function_h
#include "stm32f10x.h"

#define CH1 "ch1"
#define CH2 "ch2"
#define CH3 "ch3"
#define CH4 "ch4"
#define CH5 "ch5"

void change_ch_value(char*,int);
void unlock(void);
void lock(void);
void MOD_ALT_HOLD(void);
void MOD_Stable(void);
void ALT_HOLD(void);

#endif
