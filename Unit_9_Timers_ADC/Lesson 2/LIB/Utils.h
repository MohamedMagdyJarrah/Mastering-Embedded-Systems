#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)		(REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)		(REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)		((REG>>BIT)&1)


#endif /* UTILS_H_ */