## Memory Map

| Address Range | Description |
|---------------|-------------|
| `0100-01FF` | Stack |
| `0000-3FFF` | RAM |
| | **Read timing:**<br>- Maximum access time: **70 ns** from address valid ^ `CS` (A15, low) ^ `OE` (A14, low)<br>--> At **1 MHz**, **5 V**, there are **960 ns** available before data is needed |
| | **Write timing:**<br>- Ensure `CS` (A15) v `WE` (`R/W`) go **low after** the address is valid<br>--> Tie `CS` to `PHI2`<br>- Ensure `CS` v `WE` return **high before** the address changes |
| `6000-600F` | I/O (`65C22 VIA`) |
| `8000-FFFF` | ROM |
| `FFFC-FFFD` | Reset Vector |

### Address Layout

```text
────────────────────────────────
0000 
0100-01FF   Stack
1000
2000
3000
4000
             RAM (0000-3FFF)
────────────────────────────────
5000
6000-600F   I/O (65C22 VIA)
7000
────────────────────────────────
8000
9000
A000
B000
C000
D000
E000
F000
FFFC-FFFD   Reset Vector
             ROM (8000-FFFF)
────────────────────────────────────
