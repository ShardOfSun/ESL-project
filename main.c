#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define ID 6597
#define BLINK_PAUSE_MS 500
#define LED_PAUSE_MS 1000

int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Toggle LEDs. */
    while (true)
    {
        /* My plate ID: #6597 */
        int countBlinks[LEDS_NUMBER] = {ID / 1000, ID / 100 % 10, ID / 10 % 10, ID % 10};
        
        for (int i = 0; i < LEDS_NUMBER; i++) {
            for (int j = 0; j < countBlinks[i] * 2; j++) {
                bsp_board_led_invert(i);
                nrf_delay_ms(BLINK_PAUSE_MS);
            }

            nrf_delay_ms(LED_PAUSE_MS);
        }    
    }
}