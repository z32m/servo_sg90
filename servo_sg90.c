#include <servo_mg90s.h>

#ifndef SERVO_MG90S_DEBUG
LOG_MODULE_REGISTER(SERVO_MG90S, LOG_LEVEL_INF);
#else
LOG_MODULE_REGISTER(SERVO_MG90S, LOG_LEVEL_DBG);
#endif

int servo_mg90s_init(servo_mg90s_t *servo, const pwm_t *pwm)
{
    servo->pwm = pwm;
    fallbacks(pwm_set_dt, servo->pwm, SERVO_FREQ, SERVO_POS_0);
    k_event_init(&servo->tick);
    k_timer_init(&servo->timer, servo_mg90s_tick, NULL);
    (servo->timer).user_data = servo;

    return 0;
}

void servo_mg90s_tick(k_timer_t *timer)
{
    servo_mg90s_t *servo = timer->user_data;
    k_event_set(&servo->tick, 1);
}

int servo_mg90s_rotate(servo_mg90s_t *servo, int32_t direction, size_t ticks)
{
    fallbacks(pwm_set_dt, servo->pwm, SERVO_FREQ, direction);
    k_timer_start(&servo->timer, SERVO_TIMER_TICKS(ticks), K_NO_WAIT);
    k_event_wait(&servo->tick, 1, true, K_FOREVER);
    fallbacks(pwm_set_dt, servo->pwm, SERVO_FREQ, SERVO_POS_0);

    return 0;
}

int servo_mg90s_rotate_start(servo_mg90s_t *servo, int32_t direction)
{
    return pwm_set_dt(servo->pwm, SERVO_FREQ, direction);
}

int servo_mg90s_rotate_stop(servo_mg90s_t *servo, int32_t direction)
{
    return pwm_set_dt(servo->pwm, SERVO_FREQ, SERVO_POS_0);
}