# Simple Smart Home system
The project is simple smart home device which can control basic home devices like lights in 
room, LED tapes. System consist master device (Mobile phone with Bluetooth and android OS) which 
controls slave devices using Bluetooth device (HC-05).
Mobile phone uses free android application that allows to send Bluetooth commands to 
Bluetooth receiver. BT receiver sends messages using UART to ATmega328PB slave devices, those 
devices control end point equipment.


![image](https://user-images.githubusercontent.com/38226349/157455053-fffb2681-535e-48d0-9866-7b4fb9c4cb44.png)
