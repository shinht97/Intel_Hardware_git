<h3>ADC</h3>

ADC :  Anaolog Digital Converter

ADC Mode

1. 수동 모드 : 프로그래머가 ADC Sampling 타이밍부터 읽어오는 타이밍을 다 결정
2. Interrupt 모드 : Sampling Interrupt를 사용, 단 Callback 함수에 갇힌다는 단점 존재
3. DMA 모드 : DMA 기능을 사용하여, Interrupt처럼 사용, 메모리에 계속 저장하기 때문에, Callback에 갇히는 위험 없음

- [x] ADC Concept
- [x] ADC 사용방법 

```
short dValue[2] = { 0 }; // char(1) short(2) int(4, old int 2) long(4)

int xValue = -1; // "-1" is not generated from ADC, ADC => 0 ~ 4095
int yValue = -1;
int n = 0;

int getADCValue()
{
	HAL_ADC_Start(&hadc1); // Sampling -> Shift -> Shift Register & adding dummy process start

	HAL_ADC_PollForConversion(&hadc1, 100); // stay until conversion finish, waiting()

	int val = HAL_ADC_GetValue(&hadc1); // just read data (0 ~ 4095)

	return val;
}

void noOperation()
{
    // do nothing for waste clock
}

void myDelay(int ms)
{
	// make some delay with do nothing
  // 클락만 소비하여 딜레이를 구현
	for(int j = 0; j < ms; j++)
	{
		for(int i = 0; i < 500; i++)
		{
			noOperation();
		}
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) // it only use 1 time
{
	// not used in main function
	// can't use return value

	// n is for channel info, Interrupt has no channel info

	if(!n)
	{
		xValue = HAL_ADC_GetValue(&hadc1);

		n++;
	}
	else
	{
		yValue = HAL_ADC_GetValue(&hadc1);
		printf("(interrupt) X value : %d\r\n", xValue);
		printf("(interrupt) Y value : %d\r\n", yValue);
		printf("(interrupt) Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));

		n = 0;
	}

	myDelay(5000);

	HAL_ADC_Start_IT(&hadc1); // make ready for next interrupt
}

int main()
{
  // Interrupt 방식의 ADC
  HAL_ADC_Start_IT(&hadc1);

  // DMA 방식을 위해 이벤트 발생용 타이머와 DMA ADC 시작
  HAL_TIM_Base_Start(&htim3);

  HAL_ADC_Start_DMA(&hadc1, (int*)dValue, sizeof(short)); // pData => DMA Memory address

  while (1)
  {
	  /* Single Conversion --------------------- */
	  printf("X value : %d\r\n", getADCValue());
	  printf("Y value : %d\r\n", getADCValue());
	  printf("Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));

	  HAL_Delay(500);
	  /* --------------------------------------- */

	  /* Interrupt ----------------------------- */

	  // can't move out from interrupt loop

	  /* --------------------------------------- */

	  /* DMA ----------------------------------- */

	  printf("X value : %d\r\n", dValue[0]); // access to DMA Array(dValue[])
	  printf("Y value : %d\r\n", dValue[1]);
	  printf("Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));

	  myDelay(500*1000);

	  /* --------------------------------------- */
  }
}

```
