#pragma once


# ifdef IR_PLATFORM_WINDOWS
       #ifdef IR_BUILD_DLL
            #define IRIS_API __declspec(dllexport)
        
       #else  
            #define IRIS_API __declspec(dllimport)

       #endif
#else 
     #error Iris Engine only supports Windows for now

#endif
#define BIT(x) (1 <<x )



