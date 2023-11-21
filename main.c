#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "nrf_gpio.h"

/* constants */
#define ID 6597
#define BLINK_PAUSE_MS 500
// #define LED_PAUSE_MS 1000
/* ========= */

/* pins */
#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6)

#define LED1_PIN NRF_GPIO_PIN_MAP(0, 6)
#define LED2_R_PIN NRF_GPIO_PIN_MAP(0, 8)
#define LED2_G_PIN NRF_GPIO_PIN_MAP(1, 9)
#define LED2_B_PIN NRF_GPIO_PIN_MAP(0, 12)
/* ==== */

/* button status */
#define BUTTON_ON 0
/* ============= */

/* leds status */
#define LED_INVERT(counter) ((counter) % 2)
/* =========== */

int main(void) {
    bsp_board_init(BSP_INIT_LEDS);

    int leds_pins[LEDS_NUMBER] = {LED1_PIN, LED2_R_PIN, LED2_G_PIN, LED2_B_PIN};
    int count_blinks[LEDS_NUMBER] = {ID / 1000, ID / 100 % 10, ID / 10 % 10, ID % 10};

    for (int i = 0; i < LEDS_NUMBER; i++) {
        nrf_gpio_cfg_output(leds_pins[i]);
    }
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
    while (true) {
        for (int current_led = 0; current_led < LEDS_NUMBER; current_led++) {
            for (int current_blinks = 0; current_blinks < count_blinks[current_led] * 2; current_blinks++) {
                while (nrf_gpio_pin_read(BUTTON_PIN) != BUTTON_ON) { }
                nrf_gpio_pin_write(leds_pins[current_led], LED_INVERT(current_blinks));
                nrf_delay_ms(BLINK_PAUSE_MS);
            }
        }
    }
}
