set Path=%ARM_GCC_TOOLCHAIN%
export Path

start "libsam" /d"system\libsim\build_gcc" /max "cd"
start "libarduino" /d"cores\arduino\build_gcc" /max "cd"
rem start "libvariant Arduino Due U" /d"variants\silabs_acb_x\build_gcc" /max "cd"
start "libvariant Silabs ACB X" /d"variants\silabs_acb_x\build_gcc" /max "cd"
rem start "libvariant ADK2" /d"..\..\google\sam\variants\adk2\build_gcc" /max "cd"
rem start "libvariant SIM3X-EK" /d"..\..\atmel\sam\variants\sam3x_ek\build_gcc" /max "cd"
start "test" /d"cores\arduino\validation_usb_host\build_gcc" /max "cd"
