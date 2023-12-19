<h3>RTOS</h3>

RTOS : Real Time Operating System
실시간으로 처리가 가능한 OS
처리 시간이 보장되어야 하는 프로그램 작성 가능

RTOS를 사용하게 되면 main.c의 main()의 while문을 사용하지 않음
- 각 task를 수행하는 thread를 생성하고, 각 task에서 실행할 함수를 따로 작성하여 사용

- [x] RTOS Concept
- [x] multi thread

```
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("\033[1J\033[1;1HRTOS Test Program Started.....\r\n");
  printf("press B1 button to release Semaphore...\r\n");

  int n = 0;
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
    // 각 thread에서 할 작업을 지정, thread 생성

  /* definition and creation of myTask01 */
  osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 128);
  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityBelowNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityLow, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, StartTask04, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  while(osSemaphoreWait(myBinarySem01Handle, 10) == osOK)
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  // in RTOS don't use while loop

	  // controlled in main()

	  printf("in Main procedure......%d\r\n", n++);

	  HAL_GPIO_TogglePin(LDR_GPIO_Port, LDR_Pin);
	  HAL_GPIO_TogglePin(LDG_GPIO_Port, LDG_Pin);
	  HAL_GPIO_TogglePin(LDY_GPIO_Port, LDY_Pin);
	  HAL_Delay(500);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void StartTask01(void const * argument)
{
    int n = 0;

  for(;;)
  {
	  if(osSemaphoreWait(myBinarySem01Handle, 0) == osOK) // check about semaphore gets
	  {
		  printf("\033[3;1Hin Task 01......%d   \r\n", n++);

		  HAL_GPIO_TogglePin(LDR_GPIO_Port, LDR_Pin);
		  // HAL_Delay() can't change task, just delay the working task

		  osSemaphoreRelease(myBinarySem01Handle); // release semaphore
	  }

    osDelay(1);
  }
}

void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	int n = 0;
  /* Infinite loop */
  for(;;)
  {
	  if(osSemaphoreWait(myBinarySem01Handle, 0) == osOK)
	  {
		  printf("\033[5;1Hin Task 02......%d   \r\n", n++);

		  HAL_GPIO_TogglePin(LDG_GPIO_Port, LDG_Pin);

		  osSemaphoreRelease(myBinarySem01Handle);
	  }

    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	int n = 0;
  /* Infinite loop */
  for(;;)
  {
	  if(osSemaphoreWait(myBinarySem01Handle, 0) == osOK)
	  {
		  printf("\033[7;1Hin Task 03......%d   \r\n", n++);

		  HAL_GPIO_TogglePin(LDY_GPIO_Port, LDY_Pin);

		  osSemaphoreRelease(myBinarySem01Handle);
	  }

    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
	int n = 0;
  /* Infinite loop */
  for(;;)
  {
	  if(osSemaphoreWait(myBinarySem01Handle, 10) == osOK)
	  {
		  printf("\033[9;1Hin Task 04......%d   \r\n", n++);

		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		  osSemaphoreRelease(myBinarySem01Handle);
	  }

    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

```


