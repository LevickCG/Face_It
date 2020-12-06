#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class global_var
{
public:
    global_var();
};

extern const QString access_token;
extern const QString user_add;
extern const QString search;
extern const QString face_delete;
extern const QString user_update;

#endif // GLOBAL_VAR_H


//This class is designed to use the previously defined variables, like url
