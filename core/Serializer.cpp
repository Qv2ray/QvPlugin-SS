#include "Serializer.hpp"

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
namespace SSPlugin
{
    const QPair<QString, QJsonObject> SSSerializer::DeserializeOutbound(const QString &ssUri, QString *alias, QString *errMessage) const
    {
        ShadowSocksServerObject server;
        QString d_name;

        // auto ssUri = _ssUri.toStdString();
        if (ssUri.length() < 5)
        {
            *errMessage = QObject::tr("SS URI is too short");
        }

        auto uri = ssUri.mid(5);
        auto hashPos = uri.lastIndexOf("#");

        if (hashPos >= 0)
        {
            // Get the name/remark
            d_name = uri.mid(uri.lastIndexOf("#") + 1);
            uri.truncate(hashPos);
        }

        auto atPos = uri.indexOf('@');

        if (atPos < 0)
        {
            // Old URI scheme
            QString decoded = QByteArray::fromBase64(uri.toUtf8(), QByteArray::Base64Option::OmitTrailingEquals);
            auto colonPos = decoded.indexOf(':');

            if (colonPos < 0)
            {
                *errMessage = QObject::tr("Can't find the colon separator between method and password");
            }

            server.method = decoded.left(colonPos);
            decoded.remove(0, colonPos + 1);
            atPos = decoded.lastIndexOf('@');

            if (atPos < 0)
            {
                *errMessage = QObject::tr("Can't find the at separator between password and hostname");
            }

            server.password = decoded.mid(0, atPos);
            decoded.remove(0, atPos + 1);
            colonPos = decoded.lastIndexOf(':');

            if (colonPos < 0)
            {
                *errMessage = QObject::tr("Can't find the colon separator between hostname and port");
            }

            server.address = decoded.mid(0, colonPos);
            server.port = decoded.mid(colonPos + 1).toInt();
        }
        else
        {
            // SIP002 URI scheme
            auto ssQUrl = QUrl::fromUserInput(uri);
            server.address = ssQUrl.host();
            server.port = ssQUrl.port();
            const auto userInfo = SafeBase64Decode(ssQUrl.userName());
            const auto userInfoSp = userInfo.indexOf(':');
            //

            if (userInfoSp < 0)
            {
                *errMessage = QObject::tr("Can't find the colon separator between method and password");
                return {};
            }

            const auto method = userInfo.mid(0, userInfoSp);
            server.method = method;
            server.password = userInfo.mid(userInfoSp + 1);
            if(ssQUrl.hasQuery())
            {
                auto query=QUrlQuery{ssQUrl.query(QUrl::FullyDecoded)};
                auto res=query.queryItemValue("plugin");
                if(!res.isEmpty())
                {
                   server.plugin=res.section(';',0,0);
                   server.plugin_options=res.section(';',1);
                }
            }
        }

        d_name = QUrl::fromPercentEncoding(d_name.toUtf8());
        *alias =
                    alias->isEmpty()                                                                                                                  //
                        ?                                                                                                                             //
                        (d_name.isEmpty() ? server.address + server.port + server.group + server.method + server.password : d_name) //
                        :                                                                                                                             //
                        *alias + "_" + d_name;                                                                                                        //
        *alias = alias->trimmed();
        if (alias->isEmpty())
        {
            *alias = "SS Connection";
        }
        return { "shadowsocks-sip003", server.toJson()};
    }

    const QString SSSerializer::SerializeOutbound(const QString &protocol,  //
                                                   const QString &alias,     //
                                                   const QString &groupName, //
                                                   const QJsonObject &object) const
    {
        Q_UNUSED(protocol)
        auto server = ShadowSocksServerObject::fromJson(object);
        auto myAlias = QUrl::toPercentEncoding(alias);
        auto isSip002 = server.plugin.isEmpty();
        if (isSip002)
        {
            const auto plainUserInfo = server.method + ":" + server.password;
            const auto userinfo = plainUserInfo.toUtf8().toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
            return "ss://" + userinfo + "@" + server.address + ":" + QString::number(server.port) + "/#" + myAlias;
        }
        else
        {
            QString ssUri = server.method + ":" + server.password + "@" + server.address + ":" + QString::number(server.port);
            QString plugin_part=server.plugin;
            if(!server.plugin_options.isEmpty())
                plugin_part+=";"+server.plugin_options;
            plugin_part=QUrl::toPercentEncoding(plugin_part);
            return "ss://" + ssUri.toUtf8().toBase64(QByteArray::Base64Option::OmitTrailingEquals) + "/?plugin="+plugin_part+"#" + myAlias;
        }
    }
} // namespace SSRPlugin
