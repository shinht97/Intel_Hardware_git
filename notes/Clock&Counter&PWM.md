<h3>Clock & Counter & PWM</h3>

Clock의 분주를 이용하여 timer와 counter를 만들수 있음

1Hz = clk / ((prescaler) * (AutoReload Register))

- [x] 분주를 이용한 clock 설정
- [x] counter를 이용한 delay 함수
- [x] 분주를 이용한 PWM 

```
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	// 1. Timer Interrupt Callback func
	// it works in every 1sec

	// HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	// HAL_Delay(10); // Timer works every 0.5sec, but delay 1sec it makes some bug
					  // don't use heavy works in interrupt
					  // also, don't use delay in interrupt

	// 2. Counter delay
	// my_Delay(10 * 1000);

	printf("\033[11;30HTimer3... %d \r\n", cnt++);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // Interrupt Callback function
{
//	pwm_pwr += 50;
//
//	if(pwm_pwr > 1000)
//	{
//		pwm_pwr = 0;
//	}
//
//	printf("pwm_pwr : %d\r\n", pwm_pwr);

	if(pwm_pwr++ > STEP)
	{
		pwm_pwr = 0;
	}

	printf("pwm_pwr : %d\r\n", pwm_pwr);
}

void my_Delay(int _interval) // make some usec delay, _interval : usec
{
	// delay func made with counter

	// htim5 is struct

	// volatile int start = htim5.Instance->CNT;
	htim5.Instance->CNT = 0; // reset timer 5 cnt value

	while(1)
	{
//		volatile int cur = htim5.Instance->CNT;
//    volatile : 컴파일러가 건너 뛰지 못하도록 고정 시키는 역할
//		if((cur - start) > _interval)
//		{
//			return;
//		}

		// do nothing until reach "_interval"

		if(htim5.Instance->CNT > _interval)
		{
			return;
		}
	}
}

int __io_putchar(int ch) // output on console, 시리얼 통신을 이용하여 터미널에 출력하기 위한 함수
{
	HAL_UART_Transmit(&huart2, &ch, sizeof(ch), 10);

	return ch;
}

int main()
{
  printf("\033[1JProgram started...!\r\n");
  // 0x1b[0j is same as \033[0j

  // "start" is needed
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // using pwm
  //HAL_TIM_Base_Start_IT(&htim3); // Timer Interrupt start with handler_timer3
  //HAL_TIM_Base_Start(&htim5);

  // int ccr = 0;

  gap = htim2.Instance->ARR / STEP;
  while (1)
  {
	  htim2.Instance->CCR1 = pwm_pwr * gap;

//	  if (ccr > htim2.Instance->ARR)
//	  {
//		  ccr = 0;
//	  }

	  // my_Delay(10*1000);
  }
}

```
