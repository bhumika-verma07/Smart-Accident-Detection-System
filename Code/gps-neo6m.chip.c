#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uart_dev_t uart;
  timer_t timer;
  double latitude;
  double longitude;
} chip_state_t;

static void send_gps_data(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;

  char sentence[150];

  snprintf(sentence, sizeof(sentence),
    "$GPRMC,120000.00,A,2836.8340,N,07712.5400,E,0.00,0.00,031026,,,A*59\r\n");

  uart_write(chip->uart, (uint8_t *)sentence, strlen(sentence));
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  const uart_config_t uart_config = {
    .tx = pin_init("TX", INPUT_PULLUP),
    .rx = pin_init("RX", INPUT),
    .baud_rate = 9600,
    .user_data = chip
  };

  chip->uart = uart_init(&uart_config);

  chip->latitude = 28.6139;
  chip->longitude = 77.2090;

  const timer_config_t timer_config = {
    .callback = send_gps_data,
    .user_data = chip
  };

  chip->timer = timer_init(&timer_config);
  timer_start(chip->timer, 1000000, true);

  printf("GPS NEO-6M simulator initialized.\n");
}
