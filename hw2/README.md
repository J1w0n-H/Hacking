# 🧪 HW2: Constant Multiplication and Overflow Debugging

This experiment investigates how C compilers optimize constant multiplications, and how incorrect type usage and architecture differences (32-bit vs 64-bit) can lead to surprising results.

---

## 📌 Summary

- Uses `x * 12` logic, optimized by compiler as `((x + x) + x) << 2`
- Tests include signed/unsigned ints, oversized constants, zero, powers of 2
- Discrepancies observed due to overflow and data type truncation

---

## 🧪 Key Cases

| Case | Input | Expected | 32bit | 64bit |
|------|-------|----------|--------|--------|
| 2    | 12345678910U | 148148146920 | **-12** | 2119258856 |
| 5    | -12345678910 | -148148146920 | **0** | -2119258856 |
| 8    | very large int | huge | **-12** | **-12** |

---

## 🧠 Function Structure

```c
int mulBy12(int x) {
  return ((x + x) + x) << 2;
}
```

---

## 🔍 Findings

- Overflow occurs differently depending on type (`int` vs `unsigned`)
- 32-bit systems wrap around faster due to smaller register size
- 64-bit systems preserve more bits before overflow
- Debugging with `gdb` helped visualize register values at each stage

---

## 📘 Further Reading

- [📝 Blog explanation](See full writeup [here](https://j1w0n.vercel.app/Hacking9))
- [📄 PDF report](./report.pdf)
