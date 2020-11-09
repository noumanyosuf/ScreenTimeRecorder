#ifndef GLOBALEXPORT_SERVICE_H
#define GLOBALEXPORT_SERVICE_H

#include <QtCore/qglobal.h>

#if defined(SERVICE_LIBRARY)
#   define SERVICE_EXPORT Q_DECL_EXPORT
#else
#   define SERVICE_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBALEXPORT_H
