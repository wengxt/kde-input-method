
#ifndef KCM_IMCHOOSER_H
#define KCM_IMCHOOSER_H

#include <KCModule>
#include <KSharedConfig>

class IMModel;
namespace Ui {
class IMChooser;
}


class KCMIMChooser : public KCModule
{
    Q_OBJECT
public:
    explicit KCMIMChooser(QWidget* parent = 0, const QVariantList& args = QVariantList());
    virtual ~KCMIMChooser();

    void load();
    void save();
    void defaults();

private:
    void loadInputMethods();
    Ui::IMChooser* m_ui;
    IMModel* m_model;
    KSharedConfig::Ptr m_config;
};

#endif // KCM_IMCHOOSER_H
