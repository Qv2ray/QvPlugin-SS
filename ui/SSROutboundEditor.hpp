#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "ui_SSROutboundEditor.h"

#include <QWidget>

namespace SSPlugin
{
    class SSOutboundEditor
        : public Qv2rayPlugin::QvPluginEditor
        , private Ui::SSROutboundEditor
    {
        Q_OBJECT

      public:
        explicit SSOutboundEditor(QWidget *parent = nullptr);
        ~SSOutboundEditor();
        void SetHostInfo(const QString &address, int port) override;
        void SetContent(const QJsonObject &) override;
        QPair<QString, int> GetHostInfo() const override;
        const QJsonObject GetContent() const override;
        //
        void SwitchOutbound(const QString &) override{};
        QList<Qv2rayPlugin::QvPluginOutboundProtocolObject> OutboundCapabilities() const override
        {
            return { { "ShadowSocks-sip003", "shadowsocks-sip003" } };
        }
      private slots:
        void on_ssKeyTxt_textEdited(const QString &arg1);
        void on_ssPasswordTxt_textEdited(const QString &arg1);
        void on_ssMethodCombo_currentTextChanged(const QString &arg1);
        void on_ssPluginTxt_textEdited(const QString &arg1);
        void on_ssPluginOptTxt_textEdited(const QString &arg1);

      private:
        ShadowSocksServerObject shadowsocks;
    };

} // namespace SSPlugin
