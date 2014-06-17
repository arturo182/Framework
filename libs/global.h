#ifndef LIB_GLOBAL_H
#define LIB_GLOBAL_H

#include <QObject>

#if defined(LIBRARY)
#  define LIB_EXPORT Q_DECL_EXPORT
#else
#  define LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB_GLOBAL_H
