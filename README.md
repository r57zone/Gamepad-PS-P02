[![EN](https://user-images.githubusercontent.com/9499881/33184537-7be87e86-d096-11e7-89bb-f3286f752bc6.png)](https://github.com/r57zone/Gamepad-PS-P02/) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/r57zone/Gamepad-PS-P02/blob/master/README.RU.md) 
# Gamepad PS-P02
![](https://user-images.githubusercontent.com/9499881/127786126-91f82dbf-7a86-4ded-879c-6bf8f777e57f.jpg)

A repository with utilities and studies of the PS-P02 controller. This gamepad is a clone of DualShock 4, similar to DualSense. With a simple wired connection to a PC, the controller connects in Xbox gamepad mode, but when sending certain packets, it starts working in DualShock 4 mode. It would be great to find out and repeat these packets.

## Control of the light bar
You can control the light bar of this controller with using the **P02Customizer** utility. The controller still works in the Xbox gamepad mode, but with a modified light bar.


Turning on the light bar (fix it):
>P02Customizer.exe -e


Turning off the light bar:
>P02Customizer.exe -d


Changing the color of the light bar:
>P02Customizer.exe 0 255 255
(in RGB format 0-255, 0-255, 0-255)


You can also use the batch files included in the package.



**[Download](https://github.com/r57zone/Gamepad-PS-P02/releases)**

## What we managed to find out
When connecting the controller to the PC, it expects some packets and if these packets are not received, then it starts working in the Xbox gamepad mode.



If the game Days Gone or CyberPunk 2077 is running and the controller is reconnected to the PC, then PS-P02 starts working in DualShock 4 mode (the gyroscope and touch panel work). The lightbar is turned on by a USB package with P02Customizer. [PS Now](https://www.playstation.com/en-us/ps-now/ps-now-on-pc/) it also activates this mode, even without authorization.



I recorded all the packets sent by the game to the controller and tried to repeat them, but it didn't work out, I only managed to reconnect the controller in DualShock 3 mode. Recording USB packets, as well as developments can be found in the [Researches](https://github.com/r57zone/Gamepad-PS-P02/tree/master/Researches) folder.



The controller can also work in the Nintendo Pro controller mode, I was able to call this mode simply by restarting the computer.

## Goals
1. ~~Disable and change the light bar;~~
2. ~~Connecting in DualShock 3 mode;~~
3. **Connect the controller in DualShock 4 mode;**
4. Connecting in the Nintendo Switch mode;

## Feedback
`r57zone[at]gmail.com`