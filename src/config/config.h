/*
 * CONFIG FILE
 */
#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#define LOGGER_LEVEL   INFO

#define MEASUREMENTS_COUNT 100

#define DELTA_ERROR    5

#define SEARCH_PRESSURE 115000
#define MAX_PRESSURE    (SEARCH_PRESSURE + 300)

#define IR_LED_PORT       'A'
#define IR_LED_PIN         4

#define IR_RECEIVER_PORT  'F'
#define IR_RECEIVER_PIN    0

#define AIR_PUMP_PORT     'C'
#define AIR_PUMP_PIN       0

#define VALVE_PORT        'D'
#define VALVE_PIN          6

#define MPX_SENSOR_PORT   'F'
#define MPX_SENSOR_PIN     2

#define AIR_DENSITY 1.293
#define AIR_SPEED   121.65

//#define MAX_PRESSURE    125300
//#define SEARCH_PRESSURE 125000
//#define AIR_SPEED   195.57

#endif  // CONFIG_CONFIG_H_
