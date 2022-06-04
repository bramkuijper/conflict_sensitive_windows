# Parent-offspring conflict over sensitive windows: individual-based simulations

## How to compile these simulations?
Ideally, you have installed a UNIX-like toolchain through MSYS2 or cygwin on windows or use mac os (with xcode-devtools) or linux.

## Compiling the thing
We assume you have `cmake` installed. After having done a `gh repo clone bramkuijper/conflict_sensitive_windows` we do the following to compile the code. Firt we 
go to the directory containing the source code:
```
cd conflict_sensitive_windows/src/ibm
```
Then, if this is the first time you will run `cmake` on this code, tell it the following:
```
cmake -S . -B build
```
with this, we tell `cmake` that the source code is in the current dir (`-S .`)
while the executables should be built into a subdirectory called `build` (`-B build`).

Finally, we tell `cmake` to compile the thing:
```
cmake --build build
```
If everything went well, we should now find an executable `Weaning_duration` within the `build/` directory, one can find it out by doing:
```
find build -iname "Weaning_duration"
```
if this returns `build/Weaning_duration` our executable has indeed been built. Now we can run the executable by doing:
```
build/Weaning_duration
```
and within the build directory you should find a file like `sim_sensitive_window` containing the results.


