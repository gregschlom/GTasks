#ifndef GTASKS_EXPORT_H
#define GTASKS_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef GTASKS_EXPORT
# if defined(GTASKS_STATIC_LIB)        // No export/import for static libraries
#  define GTASKS_EXPORT
# elif defined(MAKE_GTASKS_LIB)        // We are building this library
#  define GTASKS_EXPORT Q_DECL_EXPORT
# else                                 // We are using this library
#  define GTASKS_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // GTASKS_EXPORT_H
