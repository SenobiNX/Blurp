#include "hk/init/module.h"
#include "hk/ro/ModuleHeader.h"
#include "rtld/RoModule.h"

#ifndef MODULE_NAME
#error no module name was set!
#endif

extern "C" {
extern hk::ro::ModuleHeader __mod0;
section(.rodata.modulename) extern __attribute__((weak)) const hk::init::ModuleName<STR(MODULE_NAME) ".nss"> hkModuleName;
section(.bss.rtldmodule) __attribute__((weak)) nn::ro::detail::RoModule hkRtldModule;
section(.rodata.modulename) __attribute__((weak)) const hk::init::ModuleName<STR(MODULE_NAME) ".nss"> hkModuleName;
}
