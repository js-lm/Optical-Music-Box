#pragma once

#include <pico/stdlib.h>
#include <pico/time.h>

#include "aliases.hpp"

#ifdef DEBUG
    #define DEBUG_PRINT(format, ...) \
        do{ \
            printf(format, ##__VA_ARGS__); \
            printf("\n"); \
        } while(false);

    #define DEBUG_PRINT_IF_CHANGED(format, ...) \
        do{ \
            static char lastMessage[256]{}; \
            char currentMessage[256]; \
            snprintf(currentMessage, sizeof(currentMessage), format, ##__VA_ARGS__); \
            if(strcmp(lastMessage, currentMessage) != 0){ \
                printf("%s\n", currentMessage); \
                strncpy(lastMessage, currentMessage, sizeof(lastMessage) - 1); \
            } \
        } while(false);

    #define DEBUG_PRINT_TIMED(intervalMs, format, ...) \
        do{ \
            units::TimestampUs currentTime{time_us_64()}; \
            static units::TimestampUs lastPrintTime{currentTime}; \
            units::Ms elapsedMs{static_cast<units::Ms>((currentTime - lastPrintTime) / 1000.0f)}; \
            if(elapsedMs >= intervalMs){ \
                printf(format, ##__VA_ARGS__); \
                printf("\n"); \
                lastPrintTime = currentTime; \
            } \
        } while(false);
#else
    #define DEBUG_PRINT(format, ...) do{} while(false);
    #define DEBUG_PRINT_IF_CHANGED(format, ...) do{} while(false);
    #define DEBUG_PRINT_TIMED(intervalMs, format, ...) do{} while(false);
#endif