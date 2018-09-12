/****************************************************************************************************************************************** 
* �ļ�����:	system_SWM1000.c
* ����˵��:	SWM1200��Ƭ����ʱ������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2012��10��30��
* ������¼: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/ 
#include <stdint.h>
#include "SWM500.h"


uint32_t SystemCoreClock  = __HSI;   				//System Clock Frequency (Core Clock)
uint32_t CyclesPerUs      = (__HSI / 1000000); 		//Cycles per micro second



/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: This function is used to update the variable SystemCoreClock and must be called whenever the core clock is changed
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemCoreClockUpdate(void)    
{
	uint16_t clk_div;

	if(SYS->CLK_CFG.CORE_CLK_DIV == 0)			//ʱ�ӷ�ƵΪ 0
	{
		clk_div = 2;
	}
	else if(SYS->CLK_CFG.CORE_CLK_DIV%2 == 1)	//ʱ�ӷ�ƵΪ����
	{
		clk_div = 1;
	}
	else										//ʱ�ӷ�ƵΪż��
	{
		clk_div = SYS->CLK_CFG.CORE_CLK_DIV;
	}

	if(SYS->DBL_IRC.DBL_IRC == 1)
		SystemCoreClock  = __HSI*2/clk_div;
	else
		SystemCoreClock  = __HSI/clk_div;
}

/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: The necessary initializaiton of systerm
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemInit(void)
{
	uint32_t i;
		
	SYS->CLK_CFG.CORE_CLK_DIV = 1;	//����������Ƶ   ż������Ӧ��Ƶֵ��0Ϊ2��Ƶ��
	SYS->DBL_IRC.DBL_IRC = 0;		//0���ڲ�ʱ��22M  1���ڲ�ʱ��44M
	for(i = 0;i <10000;i++);		//�ȴ�ʱ���ȶ�������
	
	SystemCoreClockUpdate();
}
