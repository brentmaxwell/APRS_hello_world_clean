#pragma once

#include <furi.h>
#include <gui/gui.h>

#include <furi_hal.h>
#include <furi_hal_pwm.h>

#include <notification/notification_messages.h>

#ifndef FURI_CRITICAL_ENTER
#define FURI_CRITICAL_ENTER()               \
    uint32_t primask_bit = __get_PRIMASK(); \
    __disable_irq()
#define FURI_CRITICAL_ENTER()                   \
    uint32_t __isrm = 0;                        \
    bool __from_isr = FURI_IS_ISR();            \
    if(__from_isr) {                            \
        __isrm = taskENTER_CRITICAL_FROM_ISR(); \
    } else {                                    \
        taskENTER_CRITICAL();                   \
    }
#endif

#ifndef FURI_CRITICAL_EXIT
#define FURI_CRITICAL_EXIT() __set_PRIMASK(primask_bit)
#define FURI_CRITICAL_EXIT()                \
    if(__from_isr) {                        \
        taskEXIT_CRITICAL_FROM_ISR(__isrm); \
    } else {                                \
        taskEXIT_CRITICAL();                \
    }
#endif

typedef enum {
    EventTypeTick,
    EventTypeInput,
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} APRSHelloWorldCleanEvent;

struct APRSHelloWorldCleanApp{
    Gui* gui;
    ViewPort* view_port;
    FuriMessageQueue* event_queue;

    FuriTimer* timer;

    NotificationApp* notifications;

    const GpioPin* output_pin;

    bool output_value;
};

typedef struct APRSHelloWorldCleanApp APRSHelloWorldCleanApp;

const NotificationSequence red_led_enable = {
    
    &message_red_255,
    &message_delay_500,

    NULL,
};

const NotificationSequence red_led_disable = {
    
    &message_red_0,

    NULL,
};

const NotificationSequence blue_led_enable = {
    
    &message_blue_255,
    &message_delay_250,
    &message_blue_0,

    NULL,
};
