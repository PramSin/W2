#include "FLASH.h"

void FlashUnlock()
{
  FLASH_LOCK_REG = 0xA5;
}
void FlashLock()
{
  FLASH_LOCK_REG = 0;
}
void FlashWriteWord(unsigned int adr,unsigned int word)
{
  OS_EfWrite p_flash_write_fxn;  
  p_flash_write_fxn = (OS_EfWrite)W2_FLASH_WRITE_REG;
  p_flash_write_fxn(word,adr);
}
unsigned int FlashRead(unsigned int adr)
{
  return ( *( volatile unsigned int* )(adr) );
}
void FlashEraseSector(unsigned int adr)
{
  OS_EfErase p_flash_erase_fxn;
  p_flash_erase_fxn = (OS_EfErase)W2_FLASH_ERASE_REG;
  p_flash_erase_fxn(adr | 0x10100000);
}