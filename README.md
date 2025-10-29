# bhesh 💫
🐚 A random shell that nobody cares about.

## Table of Contents 📚
- [About](#about)
- [Installation](#installation)

---

## About 🧾

__bhesh__ is a simple shell written in C, the purpose of this creation is merely for personal practice purposes and experience to learn and enhance the repository owner's skills and prepare for future workloads. It is a humble small shell that you may configure or play with in however way you prefer.

## Installation ⚒️
Due to that __bhesh__ is not associated in any linux repository, you may have to manually build it from source or use the pre-compiled binaries on Release tag (It may not be available for the time being). To install __bhesh__ on your personal computer, you need to execute certain commands:

### Manual Installation ⚙️
[!IMPORTANT] Make sure your have `Git` installed on your PC
```
git clone https://github.com/bhenzyldave/bhesh.git
```
[!IMPORTANT] Make sure you have `Cmake` installed on your system.
Then, make sure you are in the __../bhesh__ folder as copied and run:
```
cmake -S . -B build
cmake --build build
```
After this, the binary file should be stored on `./build` where `.` is the current directory where the cloned repository is located. Hence, you can now test it by:
```
build/bhesh
# Or if it doesn't work
./build/bhesh
```
Then, you now have the compiled version of `bhesh` on your PC! You may configure it however you like on `src` & `headers` then just recompile it again using cmake.