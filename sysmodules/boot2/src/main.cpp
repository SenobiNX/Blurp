#include "blurp/init.h"
#include "hk/Result.h"
#include "hk/diag/diag.h"
#include "hk/util/FixedString.h"
#include "hk/services/fsp/fileSystem.h"
#include "hk/services/fsp/service.h"
#include "hk/services/ldr.h"
#include "hk/services/ncm/programLocation.h"
#include "hk/services/pm.h"
// #include "hk/services/settings/system.h"
#include "hk/services/sm.h"
#include "hk/svc/api.h"
#include "hk/svc/types.h"
#include "hk/util/Span.h"
#include "hk/util/Storage.h"

// namespace blurp::boot2 {
//     hk::util::Storage<hk::fsp::IFileSystem> sdCard;
//     hk::Result initialize() {
//         HK_UNWRAP(hk::sm::ServiceManager::initialize());

//         HK_UNWRAP(hk::fsp::FileSystemProxy::initialize());
//         // sdCard.create(HK_TRY(hk::fsp::FileSystemProxy::instance()->openSdCardFileSystem()));
//         // // const char str[] = "hello from boot2";
//         // // sdCard.get()->createFile("boot2.txt", sizeof(str), 0);
//         // // sdCard.get()->openFile("boot2.txt", sizeof(str), 0);

//         HK_UNWRAP(hk::pm::ProcessManagerForShell::initialize());
//         HK_UNWRAP(hk::pm::ProcessManagerBootMode::initialize());
//         HK_UNWRAP(hk::settings::SystemSettings::initialize());
//         // HK_UNWRAP(hk::ldr::LoaderProcessManagerInfo::initialize());

//         return hk::ResultSuccess();
//     }

//     void finalize() {
//         hk::settings::SystemSettings::deleteInstance();
//     }

//     void launchProgram(hk::ncm::ProgramLocation location) {
//         // auto shell = hk::pm::ProcessManagerForShell::instance();

//         // shell->launchProgram(hk::pm::LaunchFlags_DisableAslr, hk::ncm::ProgramLocation())
//     }

//     hk::Result postBoot() {
//         if (false) { // IsMaintenanceMode() - check settings and gpio
//             hk::pm::ProcessManagerBootMode::instance()->setMaintenanceMode();
//         }

//         // launchProgram(hk::ncm::dmntGen2);
//         // launchProgram(hk::ncm::tma);

//         return hk::ResultSuccess();
//     }
// }

hk::Result blurp::main() {
    // hk::diag::logLine("heloo");
    // HK_ABORT_UNLESS_R(boot2::initialize());
    hk::util::FixedString<16> awesome("hello world %d", 16);
    hk::util::FixedString<16> pawsome = awesome;
    // for (int i = 0; i < 5; i++) {
    //     auto enabled = HK_UNWRAP(hk::settings::SystemSettings::instance()->getSettingsItemValue<bool, false>("atmosphere", "enable_standalone_gdbstub"));
    //     hk::diag::logLine("enabled: %d", enabled);
    // }

    // for (int i = 0; i < 5; i++) {
    //     auto str = HK_UNWRAP(hk::settings::SystemSettings::instance()->getSettingsItemValue<0x80>("lm", "sd_card_log_output_directory"));
    //     str.add(0);
    //     hk::diag::logLine("my cool log output dir: %s", (char*)str.begin());
    // }

    // blurp::boot2::finalize();

    // hk::diag::logLine("done!");
    hk::svc::ExitProcess();
}
