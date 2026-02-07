# 5-DOF Robotic Arm Controlled via MATLAB GUI

A prototype **5 Degrees of Freedom (5-DOF) robotic arm** controlled using an Arduino microcontroller and a **MATLAB-based Graphical User Interface (GUI)**.  
The system enables real-time manual control, motion recording, and motion playback, making it suitable for robotics learning, experimentation, and future expansion.

---

## 📌 Project Overview

This project presents the design and implementation of a **servo-driven robotic arm** with five independent axes of motion.  
The control system is divided between:
- **Arduino** for low-level servo control
- **MATLAB GUI** for high-level user interaction and motion management

Although developed as a **prototype**, the system is designed to be scalable and can be extended with advanced robotics techniques such as kinematics and trajectory planning.

---

## 🤖 Mechanical & Actuation Details

- **Degrees of Freedom:** 5
- **Servo Motors:**
  - 3 × SG90 Micro Servo Motors
  - 3 × MG996 High Torque Servo Motors
- **End Effector:** Servo-driven gripper
- **Motion Range:**
  - Joints: `0° – 180°`
  - Gripper: `5° – 90°`

---

## 🧩 Degrees of Freedom (DOF Description)

1. **Base Rotation**  
   Rotational movement around the vertical axis, enabling left and right rotation of the arm.  
   Angle range: `0° – 180°`

2. **Shoulder Joint**  
   Controls vertical lifting and lowering of the arm, providing primary positioning.  
   Angle range: `0° – 180°`

3. **Elbow Joint**  
   Enables extension and retraction of the arm to reach different positions.  
   Angle range: `0° – 180°`

4. **Wrist Joint**  
   Controls the orientation of the end effector for fine positioning.  
   Angle range: `0° – 180°`

5. **Gripper (End Effector)**  
   Servo-controlled gripper used for object grasping.  
   Angle range: `5° – 90°`

---

## 🧠 Control System Architecture

- **Microcontroller:** Arduino Uno  
- **Control Interface:** MATLAB GUI  
- **Communication Method:** Serial communication  
- **Servo Control:** Arduino Servo Library  

The MATLAB GUI allows the user to:
- Manually control each joint
- Execute movements in real time
- Record motion sequences
- Replay recorded motions accurately

---

## ⚙️ Features

- ✔ Independent control of all 5 joints
- ✔ MATLAB-based graphical user interface
- ✔ Motion recording and playback
- ✔ Adjustable servo angle limits
- ✔ Modular and extendable system design
- ✔ Suitable for robotics education and prototyping

---

## 🛠️ Technologies Used

- Arduino (C/C++)
- MATLAB GUI (App Designer / GUIDE)
- Arduino Servo Library
- Serial Communication

---

## 🔌 Microcontroller Compatibility

The project is currently implemented using **Arduino Uno**, however the control logic is **board-independent** and can be easily adapted to other Arduino-compatible boards such as:

- Arduino Mega  
- Arduino Nano  
- Arduino Due  
- Any compatible microcontroller supporting servo control and serial communication  

This flexibility allows seamless hardware upgrades in future versions.

---

## 🚀 How to Run the Project

### 1️⃣ Arduino Side
1. Open the Arduino source code.
2. Connect all servo motors to their assigned pins.
3. Upload the code to the Arduino board.

### 2️⃣ MATLAB Side
1. Open the MATLAB GUI file.
2. Select the correct COM port.
3. Run the GUI.
4. Use the interface to control joints, record motions, and replay them.

---

## 📷 Demo
\Docs\images\robotic_arm_demo.png

---

## 🔮 Future Improvements

This project is designed for future expansion, including but not limited to:
- Forward and Inverse Kinematics
- Trajectory planning and interpolation
- PID-based joint control
- Autonomous task execution
- Vision-based control integration
- ROS compatibility

---

## 📄 Project Status

- 🔹 Prototype  
- 🔹 Educational & Experimental  
- 🔹 Not intended for industrial deployment  

---

## 📜 License

This project is released under the **MIT License** and is open for learning and development.
