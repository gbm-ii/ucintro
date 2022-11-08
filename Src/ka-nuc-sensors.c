//code fragments for Ka-Nucleo_multisensor sensors

// include in main.h
#include "LIS35DE.h"
#include "LPS25HB.h"

// init in main.c, main() function

  /* USER CODE BEGIN 2 */
	static const uint8_t lis35_reboot[] = {LIS35_WRITE | LIS35_ADDR_NO_INC | LIS35_REG_CR2, LIS35_CR2_BOOT};
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, (uint8_t *)lis35_reboot, sizeof(lis35_reboot), 100);
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);

	const uint8_t barometer_settings[] = {LPS25HB_CR1_ODR1HZ | LPS25HB_CR1_PD | LPS25HB_CR1_BDU};
	HAL_I2C_Mem_Write(&hi2c2, LPS25HB_DEVICE_ADDRESS, LPS25HB_CTRL_REG1, 1, (uint8_t *)barometer_settings, 1, 100);

	static const uint8_t lis35_setup[] = {LIS35_WRITE | LIS35_ADDR_NO_INC | LIS35_REG_CR1, LIS35_CR1_XEN | LIS35_CR1_YEN | LIS35_CR1_ZEN | LIS35_CR1_ACTIVE};
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, (uint8_t *)lis35_setup, sizeof(lis35_setup), 100);
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);
  /* USER CODE END 2 */

// data readout in timer interrupt, 1..5 times/s

		static char s[100];
		static uint16_t scnt;
		static struct lis35_data_ lis_data;
		static struct lps25_data_ lps_data;

		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);
		float pressure_result = lps_data.pressure / 16.f;
		float temperature_result = (lps_data.temperature + 85 * 240) / 480.f;

		uint16_t len = sprintf(s, "time: %5" PRIu16 ", x: %+4d, y: %+4d, z: %+4d, %7.2f mbar, %.2f°C\r\n",
			++scnt, lis_data.outx, lis_data.outy, lis_data.outz, pressure_result, temperature_result);
		HAL_UART_Transmit_IT(&huart2, (const uint8_t *)s, len);

		static const uint8_t lis35_cmd[] = {LIS35_READ | LIS35_ADDR_INC | LIS35_REG_OUTX, 0, 0, 0, 0, 0};
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);
		HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)lis35_cmd, (uint8_t *)&lis_data, sizeof(lis35_cmd));

		HAL_I2C_Mem_Read_IT(&hi2c2, LPS25HB_DEVICE_ADDRESS, LPS25HB_PRESS_OUT_L | LPS25HB_ADDR_INC, 1, (uint8_t *)&lps_data, 4);
