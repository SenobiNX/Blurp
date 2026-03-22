#include "hk/diag/diag.h"
#include "hk/types.h"

// extern "C" hk_noreturn void* malloc(size) {
//     HK_ABORT("Attempted to allocate (malloc)");

// }
// extern "C" hk_noreturn void* aligned_alloc(size, size) {
//     HK_ABORT("Attempted to allocate (aligned_alloc)");
// }
// extern "C" hk_noreturn void free(void*) {
//     HK_ABORT("Attempted to free (free)");
// // }
// namespace std::__format_spec {
//     hk_noreturn _LIBCPP_HIDE_FROM_ABI void __throw_invalid_type_format_error() {
//         __builtin_trap();
//     }
//     hk_noreturn _LIBCPP_HIDE_FROM_ABI void __throw_invalid_option_format_error() {
//         __builtin_trap();
//     }
// } // namespace std::__format_spec
