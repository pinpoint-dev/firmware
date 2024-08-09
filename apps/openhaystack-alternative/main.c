#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ble_stack.h"
#include "openhaystack.h"
#include "pinpoint_board.h"
#include "led.h"

/** 
 * advertising interval in milliseconds 
 */
#define ADVERTISING_INTERVAL 5000

static char public_key[28] = "OFFLINEFINDINGPUBLICKEYHERE!";

#ifndef LEDS_ACTIVE_LOW
#define LEDS_ACTIVE_LOW 1
#endif

const int leds_list[] = LEDS_LIST;

/**
 * main function
 */
int main(void) {
    // Variable to hold the data to advertise
    uint8_t *ble_address;
    uint8_t *raw_data;
    uint8_t data_len;

    // Set key to be advertised
    data_len = setAdvertisementKey(public_key, &ble_address, &raw_data);

    // Init BLE stack
    init_ble();

    //init leds
    for (int i = 0; i < LEDS_NUMBER; i++) {
        led_init(leds_list[i]);
    }

    led_on(LED_R);
    led_on(LED_G);
    led_on(LED_B);

    // Set bluetooth address
    setMacAddress(ble_address);

    // Set advertisement data
    setAdvertisementData(raw_data, data_len);

    // Start advertising
    startAdvertisement(ADVERTISING_INTERVAL);

    // Go to low power mode
    while (1) {
        power_manage();
        led_toggle(LED_R);
        led_toggle(LED_G);
        led_toggle(LED_B);
    }
}
