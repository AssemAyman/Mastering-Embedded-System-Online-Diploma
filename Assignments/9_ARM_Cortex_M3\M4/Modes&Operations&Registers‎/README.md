## In this lab, we discuss Cortex M3 core registers, modes, states, and privilege levels.
In this lab, We configured PB9 (EXTI9) as an external interrupt pin at the rising edge.
At the reset state, the CPU  is in thread mode, privileged level, MSP, IRQ = 0. After the interrupt, the CPU enters Handler mode, privileged level, MSP, IRQ = 39, as we observe in this picture.

![Screenshot 2024-04-12 014123 PNG](https://github.com/AssemAyman/Mastering-Embedded-System-Online-Diploma/assets/107751300/9548dfeb-28d0-462e-bdd5-c020909844ca)
