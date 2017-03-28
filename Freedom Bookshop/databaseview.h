#ifndef DATABASEVIEW_H
#define DATABASEVIEW_H
#include <QString>

class DatabaseView
{
private:
    QString filename;
public:
    DatabaseView();
    ~DatabaseView();
    QString GetFilename();
};

#endif // DATABASEVIEW_H
