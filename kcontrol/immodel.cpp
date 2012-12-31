#include <QDebug>

#include <KGlobal>
#include <KStandardDirs>
#include <KLocalizedString>
#include <KConfigGroup>
#include "immodel.h"

IMModel::IMModel(QObject* parent): QAbstractListModel(parent)
{
    load();
}

void IMModel::load()
{
    beginResetModel();
    m_imindex.clear();
    m_imdata.clear();
    IMData noneData;
    noneData.name = i18n("None");
    noneData.internalName = "none";
    noneData.exec = "";
    noneData.restartArgument = "";
    m_imindex["none"] = m_imdata.size();
    m_imdata << noneData;
    QStringList list = KGlobal::dirs()->findAllResources( "inputmethods", QString(), KStandardDirs::NoDuplicates );
    QRegExp reg( ".*/([^/\\.]*)\\.desktop$" );
    foreach(const QString& imfile, list) {
        KDesktopFile file(imfile);
        if (file.noDisplay())
            continue;
        if (!file.tryExec())
            continue;

        QString name = file.readName();
        if( name.isEmpty())
            continue;
        if( !reg.exactMatch( imfile ))
            continue;
        QString internalName = reg.cap( 1 );
        if (m_imindex.contains(internalName))
            continue;
        IMData data;
        data.name = name;
        data.internalName = internalName;
        data.gtkIMModule = file.desktopGroup().readEntry("X-KDE-GtkIMModule");
        data.gtkIMModuleLibrary = file.desktopGroup().readEntry("X-KDE-GtkIMModuleLibrary");
        data.qtIMModule = file.desktopGroup().readEntry("X-KDE-QtIMModule");
        data.qtIMModuleLibrary = file.desktopGroup().readEntry("X-KDE-QtIMModuleLibrary");
        data.xmodifiers = file.desktopGroup().readEntry("X-KDE-XModifiers");
        m_imindex[data.internalName] = m_imdata.size();
        m_imdata << data;
    }
    endResetModel();
}

QVariant IMModel::data(const QModelIndex& index, int role) const
{
    if (index.row() > m_imdata.size())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole:
            return m_imdata[index.row()].name;
        case InternalNameRole:
            return m_imdata[index.row()].internalName;
    }
    return QVariant();
}

int IMModel::indexByName(const QString& name)
{
    if (!m_imindex.contains(name)) {
        return 0;
    }
    return m_imindex[name];
}

const IMData& IMModel::imData(const QString& name) const
{
    return m_imdata[m_imindex[name]];
}

int IMModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_imdata.size();
}

IMModel::~IMModel()
{

}
