# Washing Machine Simulator using PIC16F877A

A simulation project implemented during my Embedded Systems Internship at EMERTXE, showcasing the real-time operation of a washing machine using MPLAB X, XC8, and PicSimLab.

---

## 📌 Overview

This project simulates the functionality of a washing machine using the PIC16F877A microcontroller, programmed in Embedded C. It implements common features such as power ON, wash program selection, water level configuration, door status monitoring, countdown timer, and buzzer alerts.

---

## 🎯 Goals of the Internship

- Understand real-time embedded systems development
- Work with microcontroller-based simulation
- Learn toolchains (MPLAB X, XC8 Compiler, PicSimLab)
- Implement a real-world project using structured Embedded C

---

## 🛠️ Project Requirements Implemented

- Power ON animation using Key 5
- 12 different washing programs
- 5 water level modes
- Door lock status check
- Start, pause, and complete wash cycle
- Function phases: wash, rinse, spin
- Countdown timer
- Buzzer and fan simulation
- LCD output using CLCD interface
- Final program completion alert

---

## 📐 Block Diagram

User Input (Keypad)
↓
PIC16F877A Microcontroller → LCD Display
↓ ↓
Buzzer, Fan, LED outputs Door switch check


---

## ⚙️ Tools and Technologies Used

- MPLAB X IDE
- XC8 Compiler
- PicSimLab Simulator
- Embedded C Programming
- Git & GitHub for version control

---

## 📁 Folder Structure

Washing-Machine-Simulator-PIC16F877A/
├── src/ → .c source files
├── include/ → .h header files
├── hex/ → compiled .hex for simulation
├── nbproject/ → MPLAB project config
├── dist/ → auto-generated build output
├── Makefile
├── README.md


---

## ▶️ How to Run (Simulate)

1. Open the project in **MPLAB X IDE**
2. Compile using **XC8 Compiler**
3. Locate the `.hex` file in `hex/` folder
4. Open **PicSimLab**
5. Load the `.hex` and run the simulation

---

## 📺 Project Demo

🎥   https://youtu.be/__8AzJUuo_c

---

## 🙌 Acknowledgments

- Thanks to **EMERTXE** for providing structured training.
- Inspired by various YouTube simulations and GitHub examples.
- Special thanks to GitHub Copilot, ChatGPT & the open-source community.

---

## 📬 Contact

If you have any questions or want to collaborate:

**GitHub:** [@spriyanshi180](https://github.com/spriyanshi180)  
**LinkedIn:** http://www.linkedin.com/in/spriyanshi180
**Email:** spriyanshi180@gmail.com

---

⭐️ Don’t forget to star this repo if you found it helpful!
