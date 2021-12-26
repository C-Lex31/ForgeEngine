#pragma once


# ifdef IR_PLATFORM_WINDOWS
# if IR_DYNAMIC_LINK
       #ifdef IR_BUILD_DLL
            #define IRIS_API __declspec(dllexport)
        
       #else  
            #define IRIS_API __declspec(dllimport)

       #endif
#else
       #define IRIS_API
#endif
#else 
     #error Iris Engine only supports Windows for now

#endif
#define BIT(x) (1 <<x )

#define IR_BIND_EVENT_FN(fn) std::bind(&fn, this ,std::placeholders::_1 )



