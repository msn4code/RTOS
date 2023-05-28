#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define STACK_SIZE 64
#define MAX_TASKS 3

// Task control block structure
typedef struct {
  uint8_t stack[STACK_SIZE];
  void (*taskFunc)(void);
} TaskControlBlock;

// Define tasks
void task1(void);
void task2(void);
void task3(void);

// Task control block array
TaskControlBlock tcb[MAX_TASKS];
volatile uint8_t currentTask = 0;

// Initialize ports
void initializePorts(void) {
  // Set PB0, PB1, and PB2 as outputs for LEDs
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
}

// Initialize timers
void initializeTimers(void) {
  // Configure Timer0 for CTC mode with prescaler 64
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS01) | (1 << CS00);
  OCR0A = 249; // Set compare value for 1 ms at 16 MHz
}

// Initialize interrupts
void initializeInterrupts(void) {
  // Enable Timer0 compare match interrupt
  TIMSK0 |= (1 << OCIE0A);
}

// Perform context switching
void contextSwitch(void) {
  asm volatile("push r0\n\t"
               "in r0, __SREG__\n\t"
               "cli\n\t"
               "push r0\n\t"
               "push r1\n\t"
               "clr r1\n\t"
               "push r2\n\t"
               "push r3\n\t"
               "push r4\n\t"
               "push r5\n\t"
               "push r6\n\t"
               "push r7\n\t"
               "push r8\n\t"
               "push r9\n\t"
               "push r10\n\t"
               "push r11\n\t"
               "push r12\n\t"
               "push r13\n\t"
               "push r14\n\t"
               "push r15\n\t"
               "push r16\n\t"
               "push r17\n\t"
               "push r18\n\t"
               "push r19\n\t"
               "push r20\n\t"
               "push r21\n\t"
               "push r22\n\t"
               "push r23\n\t"
               "push r24\n\t"
               "push r25\n\t"
               "push r26\n\t"
               "push r27\n\t"
               "push r28\n\t"
               "push r29\n\t"
               "push r30\n\t"
               "push r31\n\t");
}

// Perform context restoration
void restoreContext(void) {
  asm volatile("pop r31\n\t"
               "pop r30\n\t"
               "pop r29\n\t"
               "pop r28\n\t"
               "pop r27\n\t"
               "pop r26\n\t"
               "pop r25\n\t"
               "pop r24\n\t"
               "pop r23\n\t"
               "pop r22\n\t"
               "pop r21\n\t"
               "pop r20\n\t"
               "pop r19\n\t"
               "pop r18\n\t"
               "pop r17\n\t"
               "pop r16\n\t"
               "pop r15\n\t"
               "pop r14\n\t"
               "pop r13\n\t"
               "pop r12\n\t"
               "pop r11\n\t"
               "pop r10\n\t"
               "pop r9\n\t"
               "pop r8\n\t"
               "pop r7\n\t"
               "pop r6\n\t"
               "pop r5\n\t"
               "pop r4\n\t"
               "pop r3\n\t"
               "pop r2\n\t"
               "pop r1\n\t"
               "pop r0\n\t"
               "out __SREG__, r0\n\t"
               "pop r0\n\t");
}

// Timer interrupt handler
ISR(TIMER0_COMPA_vect) {
  // Save current context
  contextSwitch();

  // Switch to next task
  currentTask = (currentTask + 1) % MAX_TASKS;

  // Load context of the next task
  restoreContext();
}

// Task 1 - LED Blinking
void task1(void) {
  while (1) {
    PORTB ^= (1 << PB0); // Toggle PB0 state (LED)
    _delay_ms(500);     // Delay for 500 ms
  }
}

// Task 2 - LED Blinking
void task2(void) {
  while (1) {
    PORTB ^= (1 << PB1); // Toggle PB1 state (LED)
    _delay_ms(1000);    // Delay for 1 second
  }
}

// Task 3 - LED Blinking
void task3(void) {
  while (1) {
    PORTB ^= (1 << PB2); // Toggle PB2 state (LED)
    _delay_ms(2000);    // Delay for 2 seconds
  }
}

int main(void) {
  // Initialize ports, timers, etc.
  initializePorts();
  initializeTimers();
  initializeInterrupts();

  // Create tasks
  tcb[0].taskFunc = task1;
  tcb[1].taskFunc = task2;
  tcb[2].taskFunc = task3;

  // Enable interrupts
  sei();

  // Start the first task
  tcb[currentTask].taskFunc();

  while (1) {
   
  }

  return 0;
}
