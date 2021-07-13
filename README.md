# STM32H735G-DK

This project lets you build and run Stratify OS on the STM32H735G-DK.

To build:

```sh
git clone https://github.com/StratifyLabs/STM32H735G-DK
cd STM32H735G-DK
source profile.sh
cmake -P ./bootstrap.cmake
mkdir cmake_arm
cd cmake_arm
cmake .. -DIS_PULL=ON -GNinja
ninja install
```

