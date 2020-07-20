#pragma once

#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"

#include <QList>
namespace SSPlugin
{
    QJsonObject GenerateShadowSocksROUT(QList<ShadowSocksServerObject> servers);
    class SSSerializer : public Qv2rayPlugin::QvPluginSerializer
    {
        Q_OBJECT
      public:
        explicit SSSerializer(QObject *parent = nullptr) : Qv2rayPlugin::QvPluginSerializer(parent){};
        const QString SerializeOutbound(const QString &protocol,  //
                                        const QString &alias,     //
                                        const QString &groupName, //
                                        const QJsonObject &object) const override;
        const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const override;
        const Qv2rayPlugin::QvPluginOutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override
        {
            if (protocol == "shadowsocks-sip003")
            {
                auto r = ShadowSocksServerObject::fromJson(outbound);
                return Qv2rayPlugin::QvPluginOutboundInfoObject{ r.address, "shadowsocks-sip003", r.port };
            }
            else
            {
                return {};
            }
        }
        const QList<QString> ShareLinkPrefixes() const override
        {
            return { "ss://" };
        };
        const QList<QString> OutboundProtocols() const override
        {
            return { "shadowsocks-sip003" };
        }
    };
}; // namespace SSRPlugin
