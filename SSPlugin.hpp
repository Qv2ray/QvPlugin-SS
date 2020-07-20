#pragma once

#include "QvPluginInterface.hpp"
#include "core/EventHandler.hpp"
#include "core/Serializer.hpp"
#include "core/kernel/SSInstance.hpp"

#include <QObject>
#include <QtPlugin>

class QLabel;
using namespace Qv2rayPlugin;
namespace SSPlugin
{
    class QvSSPlugin
        : public QObject
        , Qv2rayInterface
    {
        Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
        Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
        Q_OBJECT
      public:
        //
        // Basic metainfo of this plugin
        const QvPluginMetadata GetMetadata() const override
        {
            auto x = QvPluginMetadata{
                "SS Plugin",                         //
                "Qv2ray Development Group",           //
                "qvplugin_ss",                       //
                "Support SS SIP003 connections in Qv2ray.", //
                QIcon(":/qv2ray.png"),                //
                {},                                   //
                { SPECIAL_TYPE_KERNEL,                //
                  SPECIAL_TYPE_SERIALIZOR }           //
            };
            x.KernelOutboundCapabilities = { { "ShadowSocks-sip003", "shadowsocks-sip003" } };
            return x;
        }
        //
        std::unique_ptr<QWidget> GetSettingsWidget() override;
        std::unique_ptr<QvPluginEditor> GetEditorWidget(UI_TYPE) override;
        std::unique_ptr<QvPluginKernel> CreateKernel() override;
        std::shared_ptr<QvPluginSerializer> GetSerializer() override;
        std::shared_ptr<QvPluginEventHandler> GetEventHandler() override;
        //
        bool UpdateSettings(const QJsonObject &) override;
        bool Initialize(const QString &, const QJsonObject &) override;
        const QJsonObject GetSettngs() override;
        //
      signals:
        void PluginLog(const QString &) const override;
        void PluginErrorMessageBox(const QString &) const override;

      private:
        QJsonObject settings;
        std::shared_ptr<SSPluginEventHandler> eventHandler;
        std::shared_ptr<SSSerializer> serializer;
    };
} // namespace SSRPlugin
