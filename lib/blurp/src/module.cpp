#include "hk/init/module.h"
#include "blurp/init.h"
#include "hk/hook/InstrUtil.h"
#include "hk/ro/ElfUtil.h"
#include "hk/ro/ModuleHeader.h"
#include "hk/svc/api.h"
#include "hk/svc/types.h"
#include "hk/types.h"

namespace blurp::init {

    static void relocateSelf(ptr moduleBase, const Elf_Dyn* dynamic) {
        const auto data = hk::ro::parseDynamic(moduleBase, dynamic);

        data.forEachRel([&](const Elf_Rel& entry) {
            Elf_Addr* ptr = cast<Elf_Addr*>(moduleBase + entry.r_offset);
            *ptr += moduleBase;
        });

        data.forEachRela([&](const Elf_Rela& entry) {
            Elf_Addr* ptr = cast<Elf_Addr*>(moduleBase + entry.r_offset);
            *ptr = moduleBase + entry.r_addend;
        });
    }

    asm(R"(
        .global __module_entry__
        .global _ZN5blurp4init5startEmm
        __module_entry__:
            cbz x0, _ZN5blurp4init5startEmm
            mov w0, #0xf801
            b _ZN2hk3svc19ReturnFromExceptionENS_6ResultE
    )");

    void start(ptr, ptr) {
        ptr moduleBase = HK_UNWRAP(([]() hk_alwaysinline -> hk::ValueOrResult<ptr> {
            ptr addr;
            __asm("adr %[result], __module_start__" : [result] "=r"(addr));

            // us
            auto [info, page] = HK_TRY(hk::svc::QueryMemory(addr));
            return ptr(info.base_address);
        })());

        struct {
            hk::hook::Instr bInstr;
            u32 offset;
        } const* const offs = cast<decltype(offs)>(moduleBase);

        const hk::ro::ModuleHeader* header = cast<const hk::ro::ModuleHeader*>(moduleBase + offs->offset);
        const Elf_Dyn* dynamic = cast<const Elf_Dyn*>(ptr(header) + header->dynamicOffset);

        u8* bssStart = cast<u8*>(ptr(header) + header->bssOffset);
        const size bssSize = header->bssEndOffset - header->bssOffset;

        memset(bssStart, 0, bssSize);

        relocateSelf(moduleBase, dynamic);
        hk::init::callInitializers();

        static hk::svc::ThreadType sMainThreadType = {};
        hk::svc::getTLS()->nnsdkThread = &sMainThreadType;
        strncpy(sMainThreadType.threadName, "MainThread", sizeof(sMainThreadType.threadName));

        hk::Result result = main();
        hk::svc::Break(hk::svc::BreakReason_User, &result, sizeof(result));
        hk::svc::ExitProcess();
    }
}
