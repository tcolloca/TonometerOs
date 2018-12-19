/*
 * LOGGER FOR DIFFERENT LEVELS.
 */
#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

typedef enum Level {FINEST = 1, FINER = 2, FINE = 3, DEBUG = 4,
										INFO = 5, WARNING = 6, ERROR = 7, LEVEL_UNSET = 0} Level;

/* Sets the level of the logger. */
void Logger_SetLevel(Level level);

/* Logs a message at FINEST level. */
void Logger_AtFinest(char* fmt, ...);

/* Logs a message at FINER level. */
void Logger_AtFiner(char* fmt, ...);

/* Logs a message at FINE level. */
void Logger_AtFine(char* fmt, ...);

/* Logs a message at DEBUG level. */
void Logger_AtDebug(char* fmt, ...);

/* Logs a message at INFO level. */
void Logger_AtInfo(char* fmt, ...);

/* Logs a message at WARNING level. */
void Logger_AtWarning(char* fmt, ...);

/* Logs a message at ERROR level. */
void Logger_AtError(char* fmt, ...);

#endif  // LOGGER_LOGGER_H_
