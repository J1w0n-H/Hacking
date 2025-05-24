# 🧪 Variable Size and Alignment Analyzer

This project explores how variable alignment and padding work in C, and how they differ across systems and compilers.

## ✅ Features

- Tests alignment of `char`, `int`, `float`, `double`, `long double`, etc.
- Works on 32-bit and 64-bit architectures
- Prints variable addresses and compares alignment
- Demonstrates struct padding and memory layout inconsistencies

## 🖥️ Tested On

- System A: Ubuntu 16.04 (32-bit, x86)
- System B: macOS 13.6 (64-bit, x86_64)

## 📂 Directory Structure

```
.
├── README.md
├── src/
│   ├── main1_Value.c
│   ├── main2_Tabular.c
│   ├── main3_Random.c
│   ├── main4_Long.c
├── Results/
│   ├── hw1_page_1.png
│   ├── hw1_page_2.png
```

## 📌 Sample Output

```
a: 0xffffd4f0
b: 0xffffd4f2
c: 0xffffd4f4
f: 0xffffd4f8
```

## 🧠 What We Learned

- Alignment and padding rules vary across architectures
- `long double` is 12 bytes on x86 (System A), 16 bytes on x86_64 (System B)
- Variable declaration order may not match memory layout
- ASLR, compiler optimizations, and padding affect memory security

## 📘 Full Writeup

See full blog explanation [here](https://J1w0n.vercel.app/Hacking8)
