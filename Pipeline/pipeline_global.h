#ifndef PIPELINE_GLOBAL_H
#define PIPELINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PIPELINE_LIBRARY)
#  define PIPELINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PIPELINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PIPELINE_GLOBAL_H
