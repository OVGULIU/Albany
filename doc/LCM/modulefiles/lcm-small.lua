whatis("LCM small build type")

setenv("BUILD_TYPE", "small")
setenv("BUILD_STRING", "MINSIZEREL")
setenv("LCM_FPE_SWITCH", "OFF")
setenv("LCM_DENORMAL_SWITCH", "ON")
setenv("LCM_CXX_FLAGS", "-msse3 -DNDEBUG")
