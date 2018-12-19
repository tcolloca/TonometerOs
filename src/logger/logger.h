/*
 * LOGGER FOR DIFFERENT LEVELS.
 */
#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

typedef enum Level {DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3} Level;

/* Sets the level of the logger. */
void Logger_SetLevel(Level level);

/* Logs a message at DEBUG level. */
void Logger_AtDebug(char* fmt, ...);

/* Logs a message at INFO level. */
void Logger_AtInfo(char* fmt, ...);

/* Logs a message at WARNING level. */
void Logger_AtWarning(char* fmt, ...);

/* Logs a message at ERROR level. */
void Logger_AtError(char* fmt, ...);

#endif  // LOGGER_LOGGER_H_
