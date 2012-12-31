#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

#include <KStandardDirs>
#include <KGlobal>
int main(int argc, char* argv[])
{
    if (argc < 2)
        return 1;

    QCoreApplication app(argc, argv);

    foreach(const QString& s, app.libraryPaths()) {
        QFileInfo info(QString("%1/inputmethods/%2").arg(s).arg(argv[1]));
        if (info.exists()) {
            return 0;
        }
    }
    return 1;
}
