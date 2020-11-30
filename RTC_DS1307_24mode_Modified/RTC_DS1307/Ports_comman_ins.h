#ifndef  ports_Comman_ins
#define ports_Comman_ins
#include "data_types.h"

#define Acess_REG_8bit(REG)          (*(volatile uint8*)REG )

#define Acess_REG_16bit(REG)          (*(volatile uint16*)REG )

#define PUT_VALUE_8bit(REG,val)      ((REG))=(val)

#define Set_BIT(REG,BIT_NUM)    ((REG)|=1<<(BIT_NUM))

#define CLEAR_BIT(REG,BIT_NUM)  ((REG) &=(~(1<<(BIT_NUM))))

#define Toggl_BIT(REG,PIN)      ((REG)=(REG)^(1<<PIN))

#define Bit_IS_SET(REG,BIT_NUM)       (((REG) & (1 << BIT_NUM)))

#define Bit_is_CLEAR(REG,BIT_NUM)     (!(Bit_is_set(REG,BIT_NUM)))

#define Rotate_BIT(REG,BIT_NUM)       ((REG)=1<<(BIT_NUM))

#define Rotate_Right_BIT(REG,BIT_NUM)       ((REG)=1>>(BIT_NUM))

#define  READ_BIT(reg,bit)             ((reg>>bit)&1)

#define SET_REGISTER_PIN(REG, BIT, VAL) ((REG) = (((REG) & (~(1<<BIT))) | ((VAL) << (BIT))))


#endif