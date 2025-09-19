#include "l298n.h"

#include <sys/cdefs.h>

void l298n_motor_init(motor_t *m, pin_id_t in1, pin_id_t in2) {
   m->in1 = in1;
   m->in2 = in2;
   pin_init(m->in1, PIN_OUT);
   pin_init(m->in2, PIN_OUT);
}

void l298n_motor_drive(motor_t *m, motor_action_t action) {
   switch (action) {
      case MOTOR_FORWARD:
         pin_set_value(m->in1, HIGH);
         pin_set_value(m->in2, LOW);
         break;
      case MOTOR_REVERSE:
         pin_set_value(m->in1, LOW);
         pin_set_value(m->in2, HIGH);
         break;
      case MOTOR_BRAKE:
         pin_set_value(m->in1, HIGH);
         pin_set_value(m->in2, HIGH);
         break;
      default:
         pin_set_value(m->in1, LOW);
         pin_set_value(m->in2, LOW);
         break;
   }
}