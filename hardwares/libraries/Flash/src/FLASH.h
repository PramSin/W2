#ifndef __FLASH_H__
#define __FLASH_H__

#define FLASH_LOCK_REG              (*(volatile unsigned long *)(0x1F800B07))
#define OP_LOCK_FLASH               (FLASH_LOCK_REG = 0x0)
#define OP_UNLOCK_FLASH             (FLASH_LOCK_REG = 0xA5)

#define W2_FLASH_WRITE_REG          (0x260)
#define W2_FLASH_ERASE_REG          (0X294)
#define W2_NV_ERASE_REG             (0x2C8)

#define WORD_EMPTY                  (0xFFFFFFFF)
#define BYTE_EMPTY                  (0xFF)
#define W2_FLASH_VAILD_ADR          (0x3FFFF)
#define W2_SECTOR_SIZE              (512)      //512Byte

typedef void(*OS_EfWrite)(int,int);
typedef void(*OS_EfErase)(int);
typedef void(*OS_NvErase)(int);

void FlashUnlock();
void FlashLock();
void FlashWriteWord(unsigned int adr,unsigned int word);
unsigned int FlashRead(unsigned int adr);
void FlashEraseSector(unsigned int adr);

#endif