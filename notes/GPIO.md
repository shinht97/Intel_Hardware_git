<h3>GPIO</h3>

GPIO : Gerneral Purpose In/Out pin

GPIO의 Interrupt를 이용하여 버튼을 눌렀을때 Interrupt 명령을 수행 할수 있게 된다.

- [x] GPIO
- [x] Iterrupt Concept

```
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // Interrupt Service Routine
{
	// working code for what you want when interrupt occurred
	// don't use heavy program in interrupt

//	val = !val; // reverse val
//				// same as if(val == 0) val = 1; else val = 0;

//	val++; // increase blinking times
//
//	if(val > 4)
//	{
//		val = 0;
//	}

//	flag = 1;
//
//	if(val++ > 4) // comparison first 0 ~ 5
//	{
//		val = 0;
//	}

//	val = !val;

	val = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
}

Interrupt가 발생한 경우 동작하는 함수, HAL_GPIO_EXTI_Callback은 weak함수 이기 때문에 오버라이딩을 이용하여 사용해야함

/* led blinking --------------------------------------- */
HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1); // LED turn ON
// HAL_GPIO_WritePin(PORT, PIN, STATE);
// same as HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1)
HAL_Delay(1000); // delay 1 sec (uint_32 : msec)

HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0); // LED turn OFF

HAL_Delay(1000);

/* ---------------------------------------------------- */


/* button push ----------------------------------------- */
int input = HAL_GPIO_ReadPin(B1_GPIO_Port, BLUE_Pin);

// BLUE is pull up circuit => open 1, close 0

if(input == 0) // button pushed
{
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); // LED turn ON

  HAL_Delay(200);

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); // LED turn OFF

  HAL_Delay(200);
}


/* Button Interrupt ------------------------------------------------ */

if(val == 0)
{
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); // LED turn ON

  HAL_Delay(200);

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); // LED turn OFF

  HAL_Delay(200);
}

/* ------------------------------------------------------ */

if(val != 0) // val is public variable
{
  if(flag == 1) // turn on the led when button was pushed
  {
	  for (int i = 0; i < val; i++)
	  {
		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); // LED turn ON

		  HAL_Delay(200);

		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); // LED turn OFF

		  HAL_Delay(200);
	  }

	  flag = 0;
  }

//	HAL_Delay(400);
}
else
{
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); // LED turn OFF
}

/* Toggle Pin ------------------------------------------------------- */

if(val == 1)
{
  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  HAL_Delay(300);
}
```


