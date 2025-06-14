# AmitX

> A hobby OS forged in sleepless nights, wild dreams, and a stubborn refusal to be ordinary.  
> Owly is just one of its many feathers — a quirky language with a hoot.

Welcome to **AmitX**, the operating system you didn’t know you needed but secretly do. This is not just a compiler toolkit or a language playground — it’s a whole ecosystem born from late-night coding frenzies and a touch of math madness.

**What makes AmitX special?**

- A kernel that lives somewhere between your 3 AM epiphanies and the complex plane.  
- A shell that *hoots* instead of echoing — because why be boring?  
- Owly, its own whimsical programming language that compiles down to C, for the brave and caffeinated.  
- Tools and scripts to make building and running your code less painful and more entertaining.

---

## AmitX 0.0.1 Highlights

- The Owly compiler integrated as the official language front-runner, because Owly’s sass fits perfectly.  
- Shell with personality: hoots, clears, and sometimes just stares into the void.  
- Bash scripts that compile Owly code, compile generated C, and even pop open VS Code when you want to show off.  

---

## How to Get Started

Build and run your Owly programs inside AmitX with minimal pain:

```bash
chmod +x owlyc.sh
./owlyc.sh [--verbose] [--nodelete] yourprogram.owly
```

The script rebuilds the Owly compiler, translates Owly into C, compiles the C code, runs it.
Trashes the intermediate C file, use --verbose or -v to see it in VS code.

AmitX also has it's own shell. It welcomes you, hoots and can clear the table:

```bash
chmod +x boot.sh
./boot.sh
```

The shell will boot up, this might take a few seconds.
For the same result you can also run:
`make run`

---

## Requirements
The requirements for the full functionality of AmitX are:

- GCC (to compile C code)
- GTK (to build the shell window and stuff)

```bash
sudo apt update                     #Optional but recommended, libraries might not install if this step is skipped
sudo apt install gcc                #To compile C
sudo apt install libgtk-3-dev       #To create the shell window and its components
```

## Warning
This is hobby OS project and far from complete. Bugs, wierd behaviour and screeching owls are expected.
Please procede with caffiene and caution.

---

## Contribute?
Got ideas, features or bug fixes? Open an issue on the PR.
The Hooter welcomes all noise

---