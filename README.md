# Introduction

# Results and Video Demonstration Links

# Background and Methodology

# Block Diagram
<img width="1067" height="541" alt="blockdiagram3" src="https://github.com/user-attachments/assets/c1cad08f-37a6-441b-bbbf-e556c8894a8b" />

# Pinout
| Function | Pin | Description |
| -------------   | ----------- |
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
