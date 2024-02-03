#include <servo_sg90.h>

#ifndef SERVO_SG90_DEBUG
LOG_MODULE_REGISTER(SERVO_SG90, LOG_LEVEL_INF);
#else
LOG_MODULE_REGISTER(SERVO_SG90, LOG_LEVEL_DBG);
#endif

int servo_sg90_init(servo_sg90_t *servo, const pwm_t *pwm)
{
    servo->pwm = pwm;
    fallbacks(pwm_set_dt, servo->pwm, SERVO_SG90_FREQ, SERVO_SG90_POS_0);

    return 0;
}

int servo_sg90_rotate(servo_sg90_t *servo, int32_t pos])
{
    fallbacks(pwm_set_dt, servo->pwm, SERVO_SG90_FREQ, pos);
    return 0;
}
