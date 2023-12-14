/*
 * put_char.c
 *
 *  Created on: Dec 13, 2023
 *      Author: Administrator1
 */


// #include "../Inc/myLib.h"

int __io_putchar(int _c)
{
	// make sure correct function name "__io_putchar(int c)"

	HAL_UART_Transmit(&huart2, &_c, 1, 10);

	return _c;
}

void noOperation()
{

}

void myDelay(int usec)
{
	for(int j = 0; j < usec; j++)
	{
		for(int i = 0; i < 4; i++)
		{
			noOperation();
		}
	}
}

