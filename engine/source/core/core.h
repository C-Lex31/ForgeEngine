#pragma once


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



