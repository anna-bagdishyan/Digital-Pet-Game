# Introduction
The objective of this project was to design and implement an interactive digital pet game using the Tiva TM4C123G microcontroller and the EduBase board. The goal of the game is to keep the pet alive by maintaining its hunger level through user interaction. A win and lose condition was implemented, where the player must keep the pet alive for a certain period of time to win, while failing to feed it results in the pet’s death. Difficulty levels were implemented and affect how quickly the hunger decreases. This project utilizes multiple peripherals including interrupts, software PWM for heartbeat brightness control, and the seven-segment display for showing remaining survival time. This project demonstrates how multiple peripherals on the TM4C123G microcontroller can be integrated to create an interactive embedded system.

# Background and Methodology
This project applied embedded concepts such as GPIO, periodic interrupts, software PWM, the SysTick timer, the seven-segment display, and the LCD. The digital pet’s hunger level is represented by the four EduBase LEDs on port B (PB0-PB3), which turn off one by one over time based on the selected difficulty. Difficulty selection and refilling the LEDs were handled using the PMOD rotary encoder. The rotary encoder’s button, which is connected to PD2, is used to select the difficulty and later to refill the LEDs. 

A countdown timer was implemented on the seven-segment display using Timer 1A and ensured that the survival timer decremented every one second. The LCD module was also used to display the difficulty options as well as a “Display Pet” option. 

The pet’s heartbeat is represented by the on-board LED on port F (PF1), whose brightness changes depending on the hunger level. Software PWM was implemented using a periodic timer to manually adjust PF1, which allowed the LED’s brightness to decrease as the pet became hungrier.

Several peripherals were used, including GPIO, periodic interrupts, the SysTick timer, software PWM, and the LCD. The player must press the encoder button (PD2, feed button) before all LEDs turn off to keep the pet alive. When the pet is fed, the LEDs are restored and the PWM LED heartbeat brightens. When the player successfully keeps the pet alive long enough, the game enters a winning state, where the timer stops and the four hunger LEDs will flash. If the hunger reaches zero, the LEDs turn off, and the pet is considered dead, which results in the losing state. The seven-segment display on the EduBase board will be used to show the elapsed survival time. 

# Results and Video Demonstration Links
The Digital Pet game was successfully implemented and functions as intended. The game includes an LCD menu, difficulty selection using the PMOD rotary encoder, and a hunger bar implemented using the EduBase LEDs. Each difficulty level shows a unique pet, and the “Display Pet” option shows a pet character that moves across the screen. During gameplay, the encoder button refills the hunger bar, and this function is disabled when all LEDs are off to prevent refilling after the pet’s hunger has fully diminished.

A countdown timer was also implemented using the seven-segment display, and the PF1 LED represents the pet’s heartbeat, with its brightness adjusted based on the pet’s hunger level. The game correctly implements both win and loss conditions, displaying “YOU WIN!” or “YOU LOSE!” on the LCD and flashing the LEDs appropriately.


![win_condition](https://github.com/user-attachments/assets/b0ea390f-5208-416a-a797-69eed7748361)
Figure 1 - Board when the win condition is met

![lose_condition](https://github.com/user-attachments/assets/719184d3-72fc-460b-8199-b99a24447959)
Figure 2 - Board when the lose condition is met


Several challengers were encountered throughout the project. One major issue involved the survival timer, which originally decreased much faster than one second. This happened because the countdown was tied to the speed of the hunger LED decay, causing the timer to go down more quickly on higher difficulty levels where the LED turned off faster. To fix this, Timer 1A was dedicated to the survival timer logic, which allowed the countdown timer to decrement every one second.

Another issue occurred when attempting to use hardware PWM on PF1. The PWM configuration conflicted with the GPIO initialization in our project, which caused the hardware PWM to not work as intended and would not decrease brightness. To resolve this, software PWM was utilized and used a periodic timer to update PF1 manually. This allowed for the LED brightness to vary based on how many hunger LEDs remained lit. 

Below includes a link to view the demonstration video of the Digital Pet Game.

[Demonstration Video Result](https://drive.google.com/file/d/12U9zPKPXAhmqD7Nzn5aGTFloAVdiPIvV/view?usp=sharing)

# Block Diagram
<img width="1067" height="541" alt="blockdiagram3" src="https://github.com/user-attachments/assets/c1cad08f-37a6-441b-bbbf-e556c8894a8b" />

# Pinout
| Function | Pin | Description |
| -------------   | ----------- | ----------- |
| Difficulty Selection Button   | PD2 | This button is used to confirm the difficulty level (easy, medium, hard), which determines the rate at which the hunger level decreases. 
| Feed Button | PD2 | When pressed, the pet’s hunger level is restored to full. This button only functions as a feed button once the difficulty has been selected.
| Hunger LED Bar (4 LEDs) | PB0-PB3 | Configured as GPIO outputs. These four LEDs display the pet’s hunger level, where four LEDs indicate full health, and all LEDs off indicate death.
| Heartbeat LED  | PF1 | Configured as PWM output. The LED displays the pet’s heartbeat, where less hunger bars indicate a dimmer heartbeat.
| Seven-Segment Display   | PB4, PB7, PC7 | Displays remaining survival time in seconds while the pet is alive.

# Components Used
| Components Used | Quantity    |
| -------------   | ----------- |
| Tiva C Series TM4C123G Launchpad  | 1
| EduBase Board   | 1
| USB-A to Micro-USB Cable  | 1
| LEDs   | 5
| Seven-Segment Display   | 1
| Liquid Crystal Display   | 1
| PMOD Rotary Encoder  | 1
