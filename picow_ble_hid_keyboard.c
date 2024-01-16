#include <stdio.h>
#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"
#include "pico/cyw43_arch.h"
#include "pico/util/queue.h"

queue_t hid_keyboard_report_queue;

extern void btstack_main();


int main()
{
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("cyw43_init_error\n");
        return 0;
    }

    btstack_main();

    queue_init_with_spinlock(&hid_keyboard_report_queue, sizeof(hid_keyboard_report_t), 10, spin_lock_claim_unused(true));
    board_init();
    if (!tuh_init(BOARD_TUH_RHPORT)) { 
        printf("tuh init\n");
        return 0;
    }  else {
        printf("tinyusb init successfully\n");
    }

    

    while(1) {
        // tinyusb host task
        tuh_task();
    }

    

    return 0;
}
