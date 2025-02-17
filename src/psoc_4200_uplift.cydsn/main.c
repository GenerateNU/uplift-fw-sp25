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
#include <stdio.h>
#include <stdbool.h>

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
SLEEP       |  When any button is clicked  |    After a certain amount of time

RAISE_LEGS  |    Buttons not clicked       |    Left top and right top buttons clicked and we are in idle

LOWER_LEGS  |    Buttons not clicked       |    Left top and right bottom buttons clicked and we are in idle

RAISE_SEAT  |    Buttons not clicked       |    Left bottom and right top buttons clicked and we are in idle 

LOWER_SEAT  |    Buttons not clicked       |    Left bottom and right bottom buttons clicked and we are in idle 

PANIC       |    IMU values read normal    |    IMU trigger (walker fell over)

*/

/* I2C Clarification
- Since we are using the I2C SCB (not EZI2C), the packet does not have to be manually parsed.
- Instead, the following scheme is followed to interface with slave devices:
    1. Initialize communication session
    2. Request data (single or multiple bytes) from slave device
    3. Transfer that data to a buffer for later use
    4. End communication session
    
- For scanning the I2C bus for devices that may be there, a scan function can be used
    - since the possible address range is from 0x08 to 0x77, a for loop should work
    - iterate through each address and use the read function to try and read a single byte
    - if a response is received, remember that address
    - if not response is recevied after a few seconds, go to the next address

*/

// This is the enumerate type that defines possible states of the walker
typedef enum { SLEEP, IDLE, RAISE_LEGS, LOWER_LEGS, RAISE_SEAT, LOWER_SEAT, PANIC } State;

void i2c_read_transaction(uint32 slave_address, uint8 read_slave_register, uint8 *copy_to, uint32 size) {
    /*
    Abstracted function for dealing with reading data from the I2C bus.
    
    Args:
        slave_address (unint32) - The address of the slave device desired to be read from on the I2C bus
        read_from_register (unit32) - The register on the slave device that holds the information that you want to read
        copy_to (uint8 *) - Buffer that the read values get copied to
        size (unit32) - The number of bytes that you want to read from the slave device
    
    Return:
        (uint8 *) - A pointer to the buffer of data we want to use in our other functions
    */

    // start function handles initialization and enabling communication for I2C
    //  - init configures the SCB block to use I2C, and enable activates the component's hardware and internal interrupt
    I2C_0_Start();
    
    I2C_0_I2CMasterWriteBuf(slave_address, &read_slave_register, 1, I2C_0_I2C_MODE_NO_STOP);

    uint32 errS = I2C_0_I2CMasterReadBuf(slave_address, copy_to, size, I2C_0_I2C_MODE_REPEAT_START);
}

bool check_imu(State *current_state) {
    /*
    Checks IMU readings from the I2C bus and will transition back to IDLE if the readings are within a safe range
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    
    Returns:
        (bool) - true if walker has fallen over and false if the IMU readings are within a safe range
    */
    uint8 roll_imu_raw_data[2];
    uint8 pitch_imu_raw_data[2];
    
    // TODO: abstract the parameters to these functions like slave device and registers being read from
    i2c_read_transaction(0x28, 0x1c, roll_imu_raw_data, 2);
    i2c_read_transaction(0x28, 0x1e, pitch_imu_raw_data, 2);
    
    int16_t usable_roll_data = (int16_t) ((roll_imu_raw_data[1] << 8) | roll_imu_raw_data[0]) / 16;
    int16_t usable_pitch_data = (int16_t) ((pitch_imu_raw_data[1] << 8) | pitch_imu_raw_data[0]) / 16;
    
    // TODO: check conditionals for usable roll and pitch data to return true if walker is knocked over and false if safe

    return false;
}

// watchdog timer or real time clock for sleep state to wake it back up based on watchdog interrupts or go to sleep after an amount of time
void handle_sleep_state(/* State current_state, current time on the realt time clock */) {
    
}

void handle_idle_state(State *current_state) {
    /*
    Handles the IDLE state of the walker. The purpose of this function is to check buttons pressed and other conditionals
    that determine the next state.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    uint8 tilt_seat_button = BUTTON_TILT_EN_Read();
    uint8 all_legs_button = BUTTON_MOTOR_EN_Read();
    uint8 motors_up_button = BUTTON_DIR_UP_Read();
    uint8 motors_down_button = BUTTON_DIR_DOWN_Read();
    
    // IMU function handling if the IMU is reading that the walker has fallen over (we only care about pitch or roll readings)
    bool did_you_fall = check_imu(current_state);
    if (did_you_fall) {
        *current_state = PANIC;
    }
    
    // TODO: add a timer here (real time clock) to transition to sleep state after a certain period of time
    //  - Before transitioning to another state, reset the clock
    //  - also only start the clock when we enter idle state
    //  - if the clock reads over a specific time, transition to sleep
    
    if (all_legs_button && motors_up_button) {
        *current_state = RAISE_LEGS;
    }
    else if (all_legs_button && motors_down_button) {
        *current_state = LOWER_LEGS;
    }
    else if (tilt_seat_button && motors_up_button) {
        *current_state = RAISE_SEAT;
    }
    else if (tilt_seat_button && motors_down_button) {
        *current_state = LOWER_SEAT;
    }
}

void handle_raise_legs_state(State *current_state) {
    /*
    Handles the RAISE_LEGS state, where all legs of the walker should be raised together. If we are nearing the top,
    the pulses should slow down and motors should only activate if they are not trying to pass the upper limit.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    uint8 all_legs_button = BUTTON_MOTOR_EN_Read();
    uint8 motors_down_button = BUTTON_DIR_UP_Read(); 
    
    if (!all_legs_button && !motors_down_button) {
        *current_state = IDLE;
    }
    
    ENABLE_FRONT_MOTORS_Write(1);
    ENABLE_REAR_MOTORS_Write(1);
    
    // TODO: Add motor functionality for raising all legs here
    //  - I think this should be executing in a loop that is broken when either enabling buttons are unclicked
}

void handle_lower_legs_state(State *current_state) {
    /*
    Handles the LOWER_LEGS state, where all legs of the walker should be lowered together. If we are nearing the bottom,
    the pulses for the motors should slow down, and motors should only activate if they are not trying to pass the lower limit.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    uint8 all_legs_button = BUTTON_MOTOR_EN_Read();
    uint8 motors_down_button = BUTTON_DIR_DOWN_Read();
    
    if (!all_legs_button && !motors_down_button) {
        *current_state = IDLE;
    }
    
    ENABLE_FRONT_MOTORS_Write(1);
    ENABLE_REAR_MOTORS_Write(1);
    
    // TODO: Add motor functionality here for lowering all legs here
    //  - I think this should be executing in a loop that is broken when either enabling buttons are unclicked
}

void handle_raise_seat_state(State *current_state) {
    /*
    Handles the RAISE_SEAT state, where only the back two motors should be activated at once.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    uint8 tilt_seat_button = BUTTON_TILT_EN_Read();
    // TODO: Check to make sure that the seat is tilted down when the rear legs raise up
    uint8 raise_rear_legs_button = BUTTON_DIR_UP_Read();
    
    if (!tilt_seat_button && !raise_rear_legs_button) {
        *current_state = IDLE;
    }
    
    ENABLE_FRONT_MOTORS_Write(0);
    ENABLE_REAR_MOTORS_Write(1);
    
    // TODO: Add motor functionality here for lowering all legs here
    //  - I think this should be executing in a loop that is broken when either enabling buttons are unclicked
    //  - for raising just the rear legs, you only need to send a pwm signal through the rear pwm pin and only set 
    //    directions for those motors
}

void handle_lower_seat_state(State *current_state) {
    /*
    Handles the LOWER_SEAT state, where only the back two motors should be activated at once.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    uint8 tilt_seat_button = BUTTON_TILT_EN_Read();
    // TODO: Check to make sure that the seat is tilted up when the rear legs lower
    uint8 raise_rear_legs_button = BUTTON_DIR_UP_Read();
    
    if (!tilt_seat_button && !raise_rear_legs_button) {
        *current_state = IDLE;
    }
    
    ENABLE_FRONT_MOTORS_Write(0);
    ENABLE_REAR_MOTORS_Write(1);
    
    // TODO: Add motor functionality here for lowering all legs here
    //  - I think this should be executing in a loop that is broken when either enabling buttons are unclicked
    //  - for lowering just the rear legs, you only need to send a pwm signal through the rear pwm pin and only set 
    //    directions for those motors
}

void handle_panic_state(State *current_state) {
    /*
    Handle the PANIC state. This is triggered by the IMU, and can only be transitioned away from if the pitch and roll
    from the IMU is within a safe range. We do not care about yaw.
    
    Args:
        current_state (State *) - pointer to the current state, can be modified directly for state transitioning
    */
    bool are_you_still_on_the_ground = check_imu(current_state);
    
    if (!are_you_still_on_the_ground) {
        *current_state = IDLE;
    }
}

void are_you_there_imu() {
    uint32 errS;
    uint8 rdBuff[6];
    uint8 euler_angles = 0x1A;
    I2C_0_Start();
    
    // when you give the write buffer function a register address, it does not treat it as a write operation
    // and instead as a regiter pointer update
    I2C_0_I2CMasterWriteBuf(0x28, &euler_angles, 1, I2C_0_I2C_MODE_NO_STOP);
    while (!(I2C_0_mstrStatus & I2C_0_I2C_MSTAT_WR_CMPLT));
    
    // waits for I2C communication to complete
    while((I2C_0_mstrStatus & I2C_0_I2C_MSTAT_RD_CMPLT) == 0);
    errS = I2C_0_I2CMasterReadBuf(0x28, rdBuff, 6, I2C_0_I2C_MODE_REPEAT_START);
    
    //UART_0_Start();
    
    //for (int i = 0; i < 6; i++) {
    //    printf("0x%02X ", (uint8)rdBuff[i]);
    //}
    int16_t heading = (int16_t)((rdBuff[1] << 8) | rdBuff[0]) / 16;
    
    //if (heading > 180) {
    //    LED_0_Write(~LED_0_Read());
    //}
    
    if (errS == I2C_0_I2C_MSTR_NO_ERROR) {
        LED_0_Write(0);
    } else {
        // Error occurred
        LED_0_Write(~LED_0_Read());
        CyDelay(500);
    }
}

int main(void)
{
    State current_state = IDLE;
    // I2C_0_Init();
    // I2C_0_Enable();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    while(1) {  
        switch (current_state) {
            case SLEEP:
                handle_sleep_state();
                break;

            case IDLE:
                for (int i = 0; i < 5; i++) {
                    LED_0_Write(~LED_0_Read());
                    CyDelay(500);
                }
                //are_you_there_imu();
                handle_idle_state(&current_state);
                break;
                
            case RAISE_LEGS:
                handle_raise_legs_state(&current_state);
                break;
                
            case LOWER_LEGS:
                handle_lower_legs_state(&current_state);
                break;
                
            case RAISE_SEAT:
                handle_raise_seat_state(&current_state);
                break;
                
            case LOWER_SEAT:
                handle_lower_seat_state(&current_state);
                break;
                
            case PANIC:
                handle_panic_state(&current_state);
                break;
        }
        
    }
    
}

/* [] END OF FILE */
