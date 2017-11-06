#include "stm32f4xx.h"



#define APPLICATION_ADDRESS 0x00

typedef void (*pFunction)(void);
pFunction function;
unsigned int JumpAddress; 

void RunToDFU()
{
	JumpAddress = *(__IO uint32_t*) (0x1FFF0000 + 4);
	function = (pFunction) JumpAddress;
	__set_MSP(*(__IO uint32_t*) 0x1FFF0000);
	function();
}

void RunToApplication()
{
	JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
	function = (pFunction) JumpAddress;
	__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
	function();
}

int main(void)
{
	if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
	{
		RunToApplication();
	}
	RunToDFU();
}

