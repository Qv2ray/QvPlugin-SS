#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"

#include <QList>
using namespace Qv2rayPlugin;

QJsonObject GenerateShadowSocksROUT(QList<ShadowSocksServerObject> servers);
class SSSerializer : public Qv2rayPlugin::PluginOutboundHandler
{
  public:
    explicit SSSerializer() : Qv2rayPlugin::PluginOutboundHandler(){};
    const QString SerializeOutbound(const QString &protocol,  //
                                    const QString &alias,     //
                                    const QString &groupName, //
                                    const QJsonObject &object) const override;
    const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const override;
    const Qv2rayPlugin::OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override
    {
        Qv2rayPlugin::OutboundInfoObject result;
        result[INFO_PROTOCOL] = protocol;

        if (protocol == "shadowsocks-sip003")
        {
            auto r = ShadowSocksServerObject::fromJson(outbound);
            result[INFO_SERVER] = r.address;
            result[INFO_PORT] = r.port;
        }
        return result;
    }
    const QList<QString> SupportedLinkPrefixes() const override
    {
        return { "ss://" };
    };
    const QList<QString> SupportedProtocols() const override
    {
        return { "shadowsocks-sip003" };
    }
};
