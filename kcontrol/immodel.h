#ifndef IMMODEL_H
#define IMMODEL_H

#include <QAbstractItemModel>
#include <KDesktopFile>

enum {
    InternalNameRole = 0x39ef6345
};


struct IMData {
    QString name;
    QString internalName;
    QString exec;
    QString restartArgument;
    QString gtkIMModule;
    QString gtkIMModuleLibrary;
    QString qtIMModule;
    QString qtIMModuleLibrary;
    QString xmodifiers;
};

class IMModel : public QAbstractListModel {
    Q_OBJECT
    void load();
public:
    explicit IMModel(QObject* parent = 0);
    virtual ~IMModel();
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int indexByName(const QString& name);
    const IMData& imData(const QString& name) const;

private:
    QMap<QString, int> m_imindex;
    QList<IMData> m_imdata;
};

#endif // IMMODEL_H
