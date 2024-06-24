#pragma once

// enum Initialization_type {
//     INIFLAG,
//     EXEFLAG,
//     ENDFLAG,
// };

#define E2E_ENUM(name, ...) \
    enum name { __VA_ARGS__ };