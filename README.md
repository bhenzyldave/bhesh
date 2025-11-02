# bhesh v0.5.0 💫
🐚 A random shell that nobody cares about.

## Table of Contents 📚
- [About](#about)
- [Installation](#installation)

---

## About 🧾

__bhesh__ is a shell written in C. Its whole purpose is to help you communicate with your operating system through common shell commands! :D

## Installation ⚒️
Since __bhesh__ is not associated in any linux repository, you may have to manually build it from source or use the pre-compiled binaries on the Release tags (It may not be available for the time being). To install __bhesh__ on your personal computer, you need to execute certain commands:

### Manual Installation ⚙️
##### Make sure you have `Git` installed on your PC
```
git clone https://github.com/bhenzyldave/bhesh.git
```
##### Make sure you have `Cmake` installed on your system. `cmake --version`
Then, make sure you are in the __../bhesh__ folder as copied and run:
```
// Linux or MacOS (UNIX)
chmod +x ./build.sh
./build.sh
```
After this, the binary file should be stored in `./build`, where `.` is the current directory in which the cloned repository is located. Hence, you can now run it by:
```
// Linux or MacOS (UNIX)
build/bhesh

// Optional (Linux)
chmod +x ./run.sh
./run.sh
```
Then, you now have the compiled version of `bhesh` on your PC! You may configure it however you like on `src` & `headers`, then recompile it using CMake.
#
If you're lovin' it, feel free to add it to your PATH and just run `bhesh` to enter in your terminal or completely switch to __bhesh__! :D
```
// PATH (Option #1)
nano .<your_current_shell>rc
// Then write the following to the last line: 
export PATH="$PATH:your/build/bhesh/path"

// You can now freely enter bhesh however you 
// like and even recompile it with new changes!
bhesh

// MAIN 🔥 (Option #2)
chsh "$(which bhesh)"
// Or (If you haven't added it on PATH)
chsh "$(your/build/bhesh/path)"
```
[!NOTE] > Windows is not yet compatible with this shell, but it will be in the near future.
