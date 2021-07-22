#include "SSSettingsWidget.hpp"
#include <QFileDialog>

void SSSettingsWidget::SetSettings(const QJsonObject &content) {
    setting.loadJson(content);

    pfxPathEdit->setText(setting.default_plugin_prefix);
}

QJsonObject SSSettingsWidget::GetSettings() {
    return setting.toJson();
}

void SSSettingsWidget::on_pfxPathPushButton_clicked() {
    auto filename = QFileDialog::getExistingDirectory(this, tr("Default Plugin Path"), {});

    if (!filename.isEmpty()) {
        setting.default_plugin_prefix = filename;
        pfxPathEdit->setText(filename);
    }
}

void SSSettingsWidget::on_pfxPathEdit_textEdited(const QString &arg1) {
    setting.default_plugin_prefix = arg1;
}
