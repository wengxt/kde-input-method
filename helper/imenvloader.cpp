#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

#include <KStandardDirs>
#include <KGlobal>
#include <KDesktopFile>
#include <KSharedConfig>
#include <KConfigGroup>
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    KSharedConfig::Ptr config = KSharedConfig::openConfig("imlauncherrc", KConfig::SimpleConfig);
    KConfigGroup group(config, "IMLauncher");
    QString defaultIM = group.readEntry<QString>("DefaultIM", "none");
    QTextStream qout(stdout);

    if (defaultIM == "none")
        return 0;

    KGlobal::dirs()->addResourceType("inputmethods", "data", "inputmethods");
    QString desktopFile = KGlobal::dirs()->findResource("inputmethods", defaultIM.append(".desktop"));
    if (desktopFile.isEmpty())
        return 0;

    KDesktopFile file(desktopFile);
    if (!file.tryExec())
        return 0;

    QString gtkIMModule, gtkIMModuleLibrary, qtIMModule, qtIMModuleLibrary, xmodifiers;
    gtkIMModule = file.desktopGroup().readEntry("X-KDE-GtkIMModule");
    gtkIMModuleLibrary = file.desktopGroup().readEntry("X-KDE-GtkIMModuleLibrary");
    qtIMModule = file.desktopGroup().readEntry("X-KDE-QtIMModule");
    qtIMModuleLibrary = file.desktopGroup().readEntry("X-KDE-QtIMModuleLibrary");
    xmodifiers = file.desktopGroup().readEntry("X-KDE-XModifiers");

    if (!gtkIMModule.isEmpty() && !gtkIMModuleLibrary.isEmpty()) {
        qout << "_GTK_IM_MODULE_LIBRARY='" << gtkIMModuleLibrary << "'" << endl;
        qout << "_GTK_IM_MODULE='" << gtkIMModule << "'" << endl;
    } else {
        qout << "unset _GTK_IM_MODULE_LIBRARY" << endl;
        qout << "unset _GTK_IM_MODULE" << endl;
    }
    if (!qtIMModule.isEmpty() && !qtIMModuleLibrary.isEmpty()) {
        qout << "_QT_IM_MODULE_LIBRARY='" << qtIMModuleLibrary << "'" << endl;
        qout << "_QT_IM_MODULE='" << qtIMModule << "'" << endl;
    } else {
        qout << "unset _QT_IM_MODULE_LIBRARY" << endl;
        qout << "unset _QT_IM_MODULE" << endl;
    }
    if (!xmodifiers.isEmpty()) {
        qout << "_XMODIFIERS='" << xmodifiers << "'" << endl;
    } else {
        qout << "unset _XMODIFIERS" << endl;
    }
    return 0;
}
