#include "wokwi-api.h"
#include <stdlib.h>

typedef struct {
  pin_t pin_out;
  uint32_t temp_attr;
} chip_state_t;

static void update_output(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;
  float tempC = attr_read_float(chip->temp_attr);
  float voltage = 0.5f + tempC * 0.01f;   // TMP36: 500 mV + 10 mV/°C
  pin_dac_write(chip->pin_out, voltage);
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_out = pin_init("OUT", ANALOG);
  chip->temp_attr = attr_init_float("temperature", 25.0);

  const timer_config_t timer_config = {
    .callback = update_output,
    .user_data = chip,
  };
  timer_t timer = timer_init(&timer_config);
  timer_start(timer, 1000, true);   // update every 1 ms
}