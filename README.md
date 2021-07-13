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

To create an application SDK for this 

