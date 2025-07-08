# CHANGELOG.md  
_The timeline of dreams, bugs, and caffeine-fueled progress._

---

## [0.0.1] — *“Awake and Booting”*  
*Release date: 2025-06-14*

The very first public hoot. She’s alive. She boots. She hoots. And she compiles C like it’s nobody’s business.

---

### Added

- **Owly Compiler**  
  - Translates `.owly` files into proper, honest C code.  
  - Supports `func` declarations, `main`, `print`, and even **C-style for loops**.  
  - Output so clean, C compilers smile politely.  

- **Owly Shell Integration**  
  - A shell interface that hoots back when spoken to.  
  - Supports `hoot`, `clear`, and looking aesthetic while doing it.  

- **CLI Compilation Script**  
  - Run your Owly code in one command: `./owlyc.sh test.owly`  
  - Add `--verbose` to watch the generated C in VS Code.  
  - Add `--nodelete` if you’re a file hoarder, this does not delet the generated C code.  

- **Boot Script (`boot.sh`)**  
  - Kicks off the AmitX shell environment.  
  - Uses `make run` behind the scenes like a sneaky raccoon.  
  - Or use `./boot.sh`, same result, hopefully!
---

### Tools

- **Basic Makefile**  
  - Abstracts the build and run steps.  
  - `make run` launches the shell with all its shiny GTK glory.  

- **C project structure**  
  - Structured enough to fool people into thinking it’s organized.  
  - Separate headers for `amitx_info.h` and shell GUI.

---

### Known Oddities

- The shell might take a second to launch. She’s waking up, let her vibe.  
- Owly *will* judge your function order if you define before declaring. She compiles it anyway.  
- No user management, process isolation, or real kernel tasks — **yet**.
- Kernel might not work, largely because it doesn't exist yet.

---

### Roadmap Hints

- Support for pipes in the shell (hoot | grep 'danger')  
- A filesystem (probably called `hootfs`, let’s be real)  
- Owly: string manipulation, conditionals, pyfor loops maybe  
- Syntax for declaring variables without sacrificing your soul  

## [0.1.0] — *“Ring 0 Royalty”*
*Release date: 2025-07-08*

This is it. The kernel exists. It boots, interrupts, ticks, and even *sleeps*.
No emulator magic — just pure hardware hugs.

---
### Added

- **The Kernel**
  - It's real. It's C. It's got assembly in all the right places.
  - Lives in the noble `src/`, birthed by bootloaders, welcomed by GRUB.
  - Prints, divides by zero (on purpose), and recovers with *grace*.
- **GDT + IDT Setup**
  - Who needs user space? We're comfy in ring 0.
  - Installed and loaded like legends.
  - Custom interrupt handlers make your CPU say: "yes, chef".

- **ISR + Timer interrupts (PIT at 100 Hz)**
  -IRQ0 fires. We catch it. `tick_count++`  
  - Remapped and ready for action — no more PIC noise.  
  - Added `isr_stub.S` with handcrafted `cli`, `pusha`, `iret` like it’s the '90s.

- **Sleep function**
  - Sleeps for real seconds using timer ticks.
  - No more fake delays — this nap is hardware-approved.
  - Debug prints included, because if an interrupt fires and no one logs it, did it really happen?

---

### Tools

- **How to Build and boot?**
```sh
cd AmitX/Kernel
chmod +x boo.sh
./boo.sh
```
The kernel will build and boot in QEMU automatically.

---

### Know oddities
- Timer interrupts used to fire only once — it’s fine now, it's debugged away with rage and love
- When testing the ISRs , make sure that the mistakes you made on purpose are volatile, GCC is too kind sometimes.
- `sleep()` was spiritually broken before ticks were fully understood.
- No keyboard input — sleeping beauty awaits her princess IRQ1.

---

### Roadmap Hints

- Keyboard input handler (IRQ1 party)  
- Paging, because memory management is sexy  
- Multitasking (even if it’s fake at first)  
- Fancy `screen_puts_at()` so we can print in style  
- Owly code that can call into kernel land