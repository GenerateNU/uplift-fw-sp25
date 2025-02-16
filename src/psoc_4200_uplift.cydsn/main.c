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

uint8 *i2c_read_transaction(uint32 slave_address, uint8 read_slave_register, uint8 *copy_to, uint32 size) {
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
    
    return copy_to;
}

// watchdog timer or real time clock for sleep state to wake it back up based on watchdog interrupts or go to sleep after an amount of time
void handle_sleep_state() {

}

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

void i2c_scan() {
    
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
        // No error, device is present
        LED_0_Write(0);
    } else {
        // Error occurred, device is not responding
        LED_0_Write(~LED_0_Read());
        CyDelay(500);
    }
    
}

int main(void)
{
    State currentState = IDLE;
    // I2C_0_Init();
    // I2C_0_Enable();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    while(1) {  
        switch (currentState) {
            case SLEEP:
                handle_sleep_state();
                break;

            case IDLE:
                LED_0_Write(1);
    
                CyDelay(1000);
                are_you_there_imu();
                //handle_idle_state();
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
        
    }
    
}

/* [] END OF FILE */
