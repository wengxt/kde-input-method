#include <QFile>
#include <QDir>

#include <KPluginFactory>
#include <KStandardDirs>
#include <KDesktopFile>

#include "kcm_imchooser.h"
#include "immodel.h"
#include "ui_imchooser.h"

K_PLUGIN_FACTORY(KCMIMChooserFactory,
        registerPlugin<KCMIMChooser>();
        )
K_EXPORT_PLUGIN(KCMIMChooserFactory("kcm_imchooser"))

KCMIMChooser::KCMIMChooser(QWidget* parent, const QVariantList& args): KCModule(KCMIMChooserFactory::componentData(), parent, args)
    ,m_ui(new Ui::IMChooser)
    ,m_config(KSharedConfig::openConfig("imlauncherrc", KConfig::SimpleConfig))
{
    KGlobal::dirs()->addResourceType("inputmethods", "data", "inputmethods");
    m_ui->setupUi(this);
    m_model = new IMModel(this);
    m_ui->comboBox->setModel(m_model);

    connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));
}

KCMIMChooser::~KCMIMChooser()
{
    delete m_ui;
}

void KCMIMChooser::load()
{
    KConfigGroup group(m_config, "IMLauncher");
    QString defaultIM = group.readEntry<QString>("DefaultIM", "none");
    m_ui->comboBox->setCurrentIndex(m_model->indexByName(defaultIM));
}

void KCMIMChooser::save()
{
    KConfigGroup group(m_config, "IMLauncher");
    QString profile = m_model->data(m_model->index(m_ui->comboBox->currentIndex()), InternalNameRole).toString();
    group.writeEntry<QString>("DefaultIM", profile);
}

void KCMIMChooser::defaults()
{
    m_ui->comboBox->setCurrentIndex(m_model->indexByName("none"));
}
