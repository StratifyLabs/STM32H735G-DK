# STM32H735G-DK

This project lets you build and run Stratify OS on the STM32H735G-DK.

To build:

```sh
git clone https://github.com/StratifyLabs/STM32H735G-DK
cd STM32H735G-DK
cmake -P ./bootstrap.cmake
# If needed login to sl and run cmake -P ./bootstrap.cmake again
source profile.sh
cd cmake_arm
cmake .. -DIS_PULL=ON -GNinja
ninja
```

To create an application SDK for this project:

```sh
cd cmake_arm
ninja install
cd ..
sl os.pack:name=STM32H735G-DK-SDK
```

The above will create a file called `SDK/STM32H735G-DK-SDK.<bin|exe>`. Add this file to your Github release to allow users to download the SDK.



## Withouth Kernel Signing

Install the bootloader without key signing:

```bash
sl --prepareBootloader
```

Then copy the output binary to the mbed drive.

> This uses `/Volumes/DIS_H735IG` which is the MacOS path to the mbed drive. Please adjust accordingly for Windows and Linux.

```bash
cp tmp/STM32H735G-DK_build_boot_debug.bin /Volumes/DIS_H735IG
```

Then install the OS using:

```bash
sl --installDebugOs
```

You can then run the sample `FileBrowser` application using:

```bash
sl --runFileBrowser
```
