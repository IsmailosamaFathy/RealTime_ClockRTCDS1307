/*
 * data_types.h
 *
 * Created: 9/18/2020 1:39:29 PM
 *  Author: hp
 */ 


#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef char          sint8;
typedef int           sint16;
typedef float         uint32;
typedef long long        uint64;
  
typedef enum
{
 FALSE=0,
 TRUE=1,	
 NONE=2
}Bool_t;

typedef void(*ptr_call_back)(void);     


#define NULL_PTR         ((void *)0)

#endif /* DATA_TYPES_H_ */