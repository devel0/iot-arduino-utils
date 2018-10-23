# iot-arduino-utils

arduino utils

## prerequisites

- [vscode arduino](https://github.com/devel0/knowledge/blob/master/electronics/vscode-arduino.md)

## features

- save precious flash and ram when using serial debugging

## install

```sh
cd ~/Arduino/libraries
ln -s <path>/iot-arduino-utils
```

## usage

- edit [DebugMacros.h](arduino-utils/DebugMacros.h) to define `SERIAL_SPEED` or define `SEARCHATHING_DISABLE` to disable serial debugging


```c++
#include <DPrint.h>
#include <Util.h>
```

## references

- [SearchAThing.Arduino.Utils](https://github.com/SearchAThing-old1/SearchAThing.Arduino.Utils/tree/4cf806e9297652ae639bfaca4244a2742fd26a79#dprint)
