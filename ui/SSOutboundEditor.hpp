#pragma once

#include "QvGUIPluginInterface.hpp"
#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "ui_SSOutboundEditor.h"

#include <QWidget>

class SSOutboundEditor
    : public Qv2rayPlugin::QvPluginEditor
    , private Ui::SSOutboundEditor
{
    Q_OBJECT

  public:
    explicit SSOutboundEditor(QWidget *parent = nullptr);
    ~SSOutboundEditor();
    //
    void SetHostAddress(const QString &address, int port) override;
    QPair<QString, int> GetHostAddress() const override;
    //
    void SetContent(const QJsonObject &) override;
    const QJsonObject GetContent() const override;
    //
  private slots:
    void on_ssKeyTxt_textEdited(const QString &arg1);
    void on_ssPasswordTxt_textEdited(const QString &arg1);
    void on_ssMethodCombo_currentTextChanged(const QString &arg1);
    void on_ssPluginTxt_textEdited(const QString &arg1);
    void on_ssPluginOptTxt_textEdited(const QString &arg1);

  private:
    ShadowSocksServerObject shadowsocks;
};
