/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

/* State Machine Transition Logic
The first thing to note is that IDLE is also a state. The reason it is not in this table is because transitions
of each state are defined relative to IDLE. This is related to the second thing to note, which is that you can only
transition into one of these states (in the table below) if you are in IDLE. When buttons are clicked, a transition will
occur, and when the buttons are no longer being clicked, it will transition back to IDLE. The third thing to note is
that you can get to the PANIC state from any state based on the IMU readings.

Table layout explanation: The second column is representing how a transition from the state in that row to IDLE. The
third column has the conditions for how a transition can occur from IDLE to the state in that row.

State       |      Transition to IDLE      |      Transition away from IDLE
----------------------------------------------------------------------------------------------------------------
RAISE_LEGS  |    Buttons not clicked       |    Left top and right top buttons clicked and we are in idle

LOWER_LEGS  |    Buttons not clicked       |    Left top and right bottom buttons clicked and we are in idle

RAISE_SEAT  |    Buttons not clicked       |    Left bottom and right top buttons clicked and we are in idle 

LOWER_SEAT  |    Buttons not clicked       |    Left bottom and right bottom buttons clicked and we are in idle 

PANIC       |    IMU values read normal    |    IMU trigger (walker fell over)

*/

// This is the enumerate type that defines possible states of the walker
typedef enum { IDLE, RAISE_LEGS, LOWER_LEGS, RAISE_SEAT, LOWER_SEAT, PANIC } State;

State currentState = IDLE;

void handle_idle_state() {

}

void handle_raise_legs_state() {
    
}

void handle_lower_legs_state() {

}

void handle_raise_seat_state() {

}

void handle_lower_seat_state() {

}

void handle_panic_state() {

}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    switch (currentState) {
        case IDLE:
            handle_idle_state();
            break;
            
        case RAISE_LEGS:
            handle_raise_legs_state();
            break;
            
        case LOWER_LEGS:
            handle_lower_legs_state();
            break;
            
        case RAISE_SEAT:
            handle_raise_seat_state();
            break;
            
        case LOWER_SEAT:
            handle_lower_seat_state();
            break;
            
        case PANIC:
            handle_panic_state();
            break;
    }
    
    
    
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
