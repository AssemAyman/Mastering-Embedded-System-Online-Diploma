## Switching from Privileged access level to Unprivileged access level and vice versa
![image](https://github.com/AssemAyman/Mastering-Embedded-System-Online-Diploma/assets/107751300/0a39da2f-eae9-4c26-903a-6e1b69a6e769)

After rest, the CPU is in thread mode and Privileged access level. 

We will change the access level to Unprivileged using the **SWITCH_CPU_AccessLevel** function. 

Next, we need to return to the Privileged access level again. To do that we need to modify the **CONTRO**L register.

We must be in handler mode as its access level is always Privileged and the **CONTRO**L register can be modified only in the privileged access level.

### Press [here](https://drive.google.com/file/d/1TCm-6ll4yzsSuzXYHovyUsQyFlV_NC3f/view?usp=drive_link) to see the simulation video.
