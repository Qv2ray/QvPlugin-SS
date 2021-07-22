#pragma once

#include "QvPluginInterface.hpp"
#include "core/EventHandler.hpp"
#include "core/Serializer.hpp"

#include <QObject>
#include <QtPlugin>

class QLabel;
using namespace Qv2rayPlugin;
class QvSSPlugin
    : public QObject, public Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{
            "Shadowsocks SIP003 Plugin",        //
            "Qv2ray Development Group",         //
            "qvplugin_ss",                      //
            "Add SS SIP003 support for Qv2ray", //
            "v1.0.0",                           //
            "Qv2ray/QvPlugin-SS",               //
            { COMPONENT_GUI,                    //
              COMPONENT_KERNEL,                 //
              COMPONENT_OUTBOUND_HANDLER },     //
            UPDATE_GITHUB_RELEASE               //
        };
    }
    bool InitializePlugin(const QString &, const QJsonObject &) override;

  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &, const QString &) const override;
};
