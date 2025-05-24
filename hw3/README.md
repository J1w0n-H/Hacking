# 🧪 HW3: Memory Allocation Patterns of Compiler

This project analyzes how different kinds of variables are placed in memory depending on type, initialization, scope, and architecture. It also explores overflow behavior.

---

## 📌 Summary

- Explores how variables are arranged in memory: stack, heap, data, and text segment
- Compares multiple systems (32-bit Linux, 64-bit Linux, macOS)
- Demonstrates overflow via both stack smashing and heap overwrite
- Debugging with `gdb` used to confirm actual memory layout

---

## 🧪 Case Overview

| Case | Focus |
|------|-------|
| 1 | Initialized vs Uninitialized |
| 2 | Global vs Static vs Local vs Heap |
| 3 | int vs long long |
| 4 | Structure vs Constant vs Array |
| 5 | Function Parameters |
| 6 | Stack/Heap Overflow simulation |

---

## 🧠 Key Insights

- Initialized global/static → `.data`, Uninitialized → `.bss`
- Heap variables allocated upwards, stack variables grow downwards
- macOS has reversed order for local variables compared to Linux
- Overflow can lead to memory corruption, CVEs

---

## 📘 Files

- `address_layout.c` and variants
- Overflow example using `malloc` and stack buffer
- PDF report: [`report.pdf`](./report.pdf)

---

## 📗 Blog Explanation

See the full write-up [here](https://j1w0n.vercel.app/Hacking10)
