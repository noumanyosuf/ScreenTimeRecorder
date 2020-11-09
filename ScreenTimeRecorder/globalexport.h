#ifndef GLOBALEXPORT_RECORDER_H
#define GLOBALEXPORT_RECORDER_H

#include <QtCore/qglobal.h>

#if defined(SCREEN_TIME_LIBRARY)
#   define SCREEN_TIME_EXPORT Q_DECL_EXPORT
#else
#   define SCREEN_TIME_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBALEXPORT_H
