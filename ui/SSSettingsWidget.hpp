#ifndef SSSETTINGSWIDGET_HPP
#define SSSETTINGSWIDGET_HPP

#include "QvGUIPluginInterface.hpp"
#include "common/CommonHelpers.hpp"
#include "ui_SSSettingsWidget.h"

class SSSettingsWidget
        : public Qv2rayPlugin::QvPluginSettingsWidget, private Ui::SSSettingsWidget {
Q_OBJECT

public:
    explicit SSSettingsWidget(QWidget *parent = nullptr) : QvPluginSettingsWidget(parent) {
        setupUi(this);
    }

    void SetSettings(const QJsonObject &content) override;

    QJsonObject GetSettings() override;

private slots:

    void on_pfxPathPushButton_clicked();

    void on_pfxPathEdit_textEdited(const QString &arg1);

private:
    SSPluginSettingObject setting;
};

#endif // SSSETTINGSWIDGET_HPP
