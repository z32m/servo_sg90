#ifndef __servo_mg_90s__
#define __servo_mg_90s__

#include <xglob.h>
#include <xlog.h>
#include <zephyr/drivers/pwm.h>

#define SERVO_FREQ_MSEC 10
#define SERVO_FREQ PWM_MSEC(SERVO_FREQ_MSEC)
#define SERVO_TIMER_TICKS(n) K_MSEC(n *SERVO_FREQ_MSEC)

#define SERVO_POS_0 PWM_USEC(1500)
#define SERVO_CW PWM_USEC(1000)
#define SERVO_CCW PWM_USEC(2000)

typedef struct
{
    const pwm_t *pwm;
    k_event_t tick;
    k_timer_t timer;
} servo_mg90s_t;

void servo_mg90s_tick(k_timer_t *timer);
int servo_mg90s_init(servo_mg90s_t *servo, const pwm_t *pwm);
int servo_mg90s_rotate(servo_mg90s_t *servo, int32_t direction, size_t ticks);
int servo_mg90s_rotate_start(servo_mg90s_t *servo, int32_t direction);
int servo_mg90s_rotate_stop(servo_mg90s_t *servo, int32_t direction);

#endif