
#ifndef __Sensor_SROM_H__ 
#define __Sensor_SROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Type.h"

#ifdef __Sensor_SROM_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif


#define Sensor_SROM_TABLE_SIZE 3070
#define LASERCURRENTSETTINGTABLEXSIZE 2
#define LASERCURRENTSSTTINGTABLEYSIZE 256

INTERFACE const U8 Sensor_SROM_Table[Sensor_SROM_TABLE_SIZE]; 
INTERFACE const U8 LASER_CURRENT_SETTING_TABLE[LASERCURRENTSSTTINGTABLEYSIZE][LASERCURRENTSETTINGTABLEXSIZE];

#undef INTERFACE
#ifdef __cplusplus
}
#endif
#endif /*__Sensor_SROM_91_H__  */

