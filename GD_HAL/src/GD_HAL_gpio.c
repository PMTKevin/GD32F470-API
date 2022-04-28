#include "GD_HAL_gpio.h"

#define GPIO_NUMBER           16U

void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{

	uint32_t temp = 0x00U;
	uint32_t gpio_periph = (uint32_t)GPIOx;

	/*--------------------- GPIO Mode Configuration ------------------------*/
	if((GPIO_Init->Mode & GPIO_MODE) == MODE_INPUT)
	{
		gpio_mode_set(gpio_periph,  GPIO_Init->Mode,	GPIO_Init->Pull   ,	GPIO_Init->Pin);
	}

	if((GPIO_Init->Mode & GPIO_MODE) == MODE_OUTPUT)
	{
		temp = (GPIO_Init->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos;
		gpio_output_options_set(gpio_periph, temp, GPIO_Init->Speed, GPIO_Init->Pin);
		gpio_mode_set(gpio_periph,  GPIO_Init->Mode,	GPIO_Init->Pull   ,	GPIO_Init->Pin);
	}

	if((GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
	{
		temp = (GPIO_Init->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos;
		gpio_output_options_set(gpio_periph, temp, GPIO_Init->Speed, GPIO_Init->Pin);
		gpio_af_set(gpio_periph, GPIO_MODE_AF, GPIO_Init->Pin);
		gpio_mode_set(gpio_periph,  GPIO_Init->Mode,	GPIO_Init->Pull   ,	GPIO_Init->Pin);

	}

	if((GPIO_Init->Mode & GPIO_MODE) == MODE_ANALOG)
	{
		gpio_mode_set(gpio_periph,  GPIO_Init->Mode,	GPIO_Init->Pull   ,	GPIO_Init->Pin);
	}


	/*--------------------- EXTI Mode Configuration ------------------------*/
	/* Configure the External Interrupt or event for the current IO */
	if((GPIO_Init->Mode & EXTI_MODE) != 0x00U) //§P§O¦³EXTI_MODE¼Æ­È
	{
		//«Ý²¾´Ó
	}
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint32_t gpio_periph = (uint32_t)GPIOx;
	GPIO_PinState bitstatus;
	if((gpio_input_bit_get(gpio_periph, GPIO_Pin)) == SET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	uint32_t gpio_periph = (uint32_t)GPIOx;
	gpio_bit_write(gpio_periph, GPIO_Pin, PinState);
}

void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint32_t gpio_periph = (uint32_t)GPIOx;
	gpio_bit_toggle(gpio_periph, GPIO_Pin);
}

