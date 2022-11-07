//code fragments for Ka-Nucleo_multisensor sensors
#include "LIS35DH.h"
#include "LPS25HB.h"

//LIS35DH accelerometer commands
// init: write once the following 2 commands
static const uint8_t lis35_reboot[] = {LIS35_WRITE | LIS35_ADDR_NO_INC | LIS35_REG_CR2, LIS35_CR2_BOOT};
static const uint8_t lis35_setup[] = {LIS35_WRITE | LIS35_ADDR_NO_INC | LIS35_REG_CR1, LIS35_CR1_XEN | LIS35_CR1_YEN | LIS35_CR1_ZEN | LIS35_CR1_ACTIVE};
// read: send this command to read data into lis35_data_ structure
static const uint8_t lis35_cmd[] = {LIS35_READ | LIS35_ADDR_INC | LIS35_REG_OUTX, 0, 0, 0, 0, 0};

// LPS25HB pressure sensor
// init: write once to LPS25HB_CTRL_REG1 register address
const uint8_t barometer_settings[] = {LPS25HB_CR1_ODR1HZ | LPS25HB_CR1_PD | LPS25HB_CR1_BDU};
// readout: read 4 bytes from register address (LPS25HB_PRESS_OUT_L | LPS25HB_ADDR_INC) into lps25_data_ structure
// to get displayable values, use:
float pressure_result = lps_data.pressure / 16.f;
float temperature_result = (lps_data.temperature + 85 * 240) / 480.f;
