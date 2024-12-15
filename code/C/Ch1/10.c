#include<stdint.h>
#include<stm32g431xx.h>

/* Task: Rewrite the code as state machine
    led: 0,3 -> PA0 ..3
    button: S1: PB0, S2: PB4, S3: PB5, S4: PB4
*/

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1 | 0X2; //Enable Clock for GPIOA AND GPIOB

    GPIOA->MODER &= ~(0x30);
    GPIOA->MODER |= (0x10);

    GPIOB->MODER &= ~(0x3);
    GPIOB->PUPDR &= ~(0x3);
    GPIOB->PUPDR |= (0x1);
}

void delay(uint32_t count) {
    while (count--)
        asm("NOP");
}

void led_toggle(){
    GPIOA->ODR ^= 0x4;
}

void led_off(){
    GPIOA->ODR |= 0X4;
}

typedef enum {
    B_PRESSED,
    B_RELEASED
} event_t;

typedef enum {
    OFF,
    TOGGLE
} state_t;

typedef struct {
    state_t cur_state;
    event_t event;
    state_t next_state;
} state_machine_t;

typedef struct {
    state_t state;
    void (*action) (void);
} state_action_t;

state_machine_t StateTransition[] = {
    {OFF, B_PRESSED, TOGGLE},
    {OFF, B_RELEASED, OFF},
    {TOGGLE, B_RELEASED, OFF},
    {TOGGLE, B_PRESSED, TOGGLE}
};

state_action_t StateAction[] = {
    {OFF, &led_off},
    {TOGGLE, &led_toggle}
};

state_machine_t sm;

void loop_sm_step(){
    event_t event;
    event = (GPIOB->IDR & (0x1)) ? B_RELEASED : B_PRESSED; //if bitwise TRUE then RELEASED

    for(uint32_t i = 0; i < sizeof(StateTransition)/sizeof(StateTransition[0]); i++){
        if(StateTransition[i].cur_state == sm.cur_state){
            if(StateTransition[i].event == (event_t) event){
                sm.cur_state = (state_t) StateTransition[i].next_state;
                StateAction[sm.cur_state].action();
                break;
            }
        }
    }

}

int main(void){

    sm.cur_state = OFF;
    setup();

    while(1){
        loop_sm_step();
        delay(500000);
    }
}
