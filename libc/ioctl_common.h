#pragma once

#include "types.h"

namespace IOCTL {

    namespace VgaText {
        enum class Code : u32{
            PUT_CHAR = 1,
            MOVE_CURSOR = 2,
            GET_CHAR = 3,
            CLEAR = 4,
        };

        struct Data {
            u8 row {0};
            u8 col {0};
            u16 value {0};
        };

        enum class Errs {
            E_OUT_OF_BOUNDS = 1,
        };

    };

};
