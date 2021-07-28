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

The above will create a file called `SDK/STM32H735G-DK-SDK.<bin|exe>`. Add this file to your Github release add this file to your github release.


Install the bootloader with key signing:

```
sl os.install:path=STM32H735G-DK,publickey=162ZEPiD33bF1T8diV0t,build=boot_debug,dest=host@/Volumes/DIS_H735IG,key,rekey
```

Install the OS in flash:

```
sl os.install:build=debug,signkey=162ZEPiD33bF1T8diV0t,signkeypassword=4AC673981E969BBC9C33933800960A7F57EC0F9036CAABB2E1CF09402E9B391E,flashpath=/dev/auth_flash
```
