# 🔐 ENPM691: Hacking of C Programs and Unix Binaries (Fall 2024)

> This repository contains all 12 assignments for ENPM691, fully documented with code, debugger output, and step-by-step analysis.  
> Each writeup follows a structured journal-style format, blending cybersecurity experiments with compiler and OS-level insight.

---

## 📚 Assignment Overview

| HW | Title | Focus Topic | Link |
|----|-------|-------------|------|
| 1  | Variable Alignment Analyzer | Variable size, stack alignment, endian | [📄 HW1](./hw1/README.md) |
| 2  | Shift vs Multiply | Constant multiplication optimization | [📄 HW2](./hw2/README.md) |
| 3  | Variable Layout Debugging | Stack offsets, address layout | [📄 HW3](./hw3/README.md) |
| 4  | GDB Scripting & pwndbg | PwnDbg automation & code navigation | [📄 HW4](./hw4/README.md) |
| 5  | Return Pointer Override | Stack smashing, function hijack | [📄 HW5](./hw5/README.md) |
| 6  | SU Shell Exploit | Classic stack buffer overflow → shell | [📄 HW6](./hw6/README.md) |
| 7  | Printf Format Hijack | Function pointer overwrite via printf | [📄 HW7](./hw7/README.md) |
| 8  | GOT Hijacking Shell | PLT/GOT overwrite to launch shell | [📄 HW8](./hw8/README.md) |
| 9  | GOT Resolution Analysis | PLT -> GOT update tracing | [📄 HW9](./hw9/README.md) |
|10  | Heap Chunk Manipulation | Malloc/free exploitation | [📄 HW10](./hw10/README.md) |
|11  | Heap Pointer Hijack 1 | Hijack struct/heap pointers | [📄 HW11](./hw11/README.md) |
|12  | Heap Pointer Hijack 2 | Detailed heap exploit analysis | [📄 HW12](./hw12/README.md) |

---

## 🧠 Format

Each report follows a standardized journal paper structure:

- **Abstract:** summary of goal and findings  
- **Introduction:** problem setup and goals  
- **Methodology:** how the attack was tested  
- **Results:** debugger output and data  
- **Discussion:** what it means, how it works  
- **Appendix:** source code and extra notes

> 📌 *All reports are written in LaTeX and include clean, well-commented code.*

---

## 🔗 External Resources

- 📝 Full blog explanations: [My Writeup Series](https://J1w0n.vercel.app/Hacking1)  
- 📘 Course: [ENPM691 @ UMD]
- 🛠️ Tools used: `pwndbg`, `objdump`, `GDB`, `gcc`, `clang`, `hexdump`, `xxd`

---

## 📁 Directory Structure
 ```
.
├── hw1/
│ ├── README.md
│ ├── report.pdf
│ └── src/
├── hw2/
├── ...
└── hw12/

 ```
---

## ✅ Author

**Jiwon Hwang**  
Cybersecurity M.Eng, University of Maryland  
📧 jhwang97@umd.edu  
🔗 [LinkedIn](https://linkedin.com/in/J1w0n) | [Blog](https://J1w0n.vercel.app)

---

## 📌 Notice on Course Materials

This project was completed as part of **ENPM691: Hacking of C Programs and Unix Binaries** (Fall 2024), University of Maryland.  
The source code and writeup are original works created by the author as part of coursework.

All course slides, lecture notes, and assignments are copyrighted by the course instructor and the University.  
No official solutions or verbatim copies of course materials are shared in this repository.

If you are a student currently enrolled in the course, please avoid copying this work and follow your academic integrity policies.

