#pragma once

#include <memory>

# ifdef FR_PLATFORM_WINDOWS
# if FR_DYNAMIC_LINK
       #ifdef FR_BUILD_DLL
            #define FORGE_API __declspec(dllexport)
        
       #else  
            #define FORGE_API __declspec(dllimport)

       #endif
#else
       #define FORGE_API
#endif
#else 
     #error Forge Engine only supports Windows for now

#endif
#define BIT(x) (1 <<x )


#define FR_BIND_EVENT_FN(fn) std::bind(&fn, this ,std::placeholders::_1 )

#define FR_ENABLE_ASSERTS
#define FR_DEBUGBREAK();
#define FR_EXPAND_MACRO(x) x
#define FR_STRINGIFY_MACRO(x) #x

#define FString std::string
namespace Forge
{
    template<typename T>
    using FScope = std::unique_ptr<T>;
    template<typename T>
    using FRef = std::shared_ptr<T>;
}
#include "core/log/log.h"
#include "core/log/assertion.h"
