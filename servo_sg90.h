#ifndef __servo_sg90__
#define __servo_sg90__

#include <xglob.h>
#include <xlog.h>
#include <zephyr/drivers/pwm.h>

#define SERVO_SG90_FREQ_MSEC 20
#define SERVO_SG90_FREQ PWM_MSEC(SERVO_SG90_FREQ_MSEC)

#define SERVO_SG90_POS_0 PWM_USEC(1500)
#define SERVO_SG90_POS_MIN PWM_USEC(500)
#define SERVO_SG90_POS_MAX PWM_USEC(2500)
#define SERVO_SG90_POS_RANGE (SERVO_SG90_POS_MAX - SERVO_SG90_POS_MIN)
typedef struct
{
    const pwm_t *pwm;
} servo_sg90_t;

int servo_sg90_init(servo_sg90_t *servo, const pwm_t *pwm);
int servo_sg90_rotate(servo_sg90_t *servo, int32_t pos);

#endif