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
