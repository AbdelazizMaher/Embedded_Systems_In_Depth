/*
 * Utils.h
 *
 * Created: 3/24/2023 1:08:07 PM
 *  Author: Abdelaziz Maher
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define SET_BIT(reg,bit)			 reg |= ( 1 << bit )

#define RESET_BIT(reg,bit)		     reg &= ~( 1 << bit )

#define READ_BIT(reg,bit)		     ( (reg >> bit) & 1 )

#define TOGGLE_BIT(reg,bit)		     reg ^= ( 1 << bit )


#endif /* UTILS_H_ */