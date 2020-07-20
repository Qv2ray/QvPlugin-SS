#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
namespace SSPlugin
{
    struct ShadowSocksServerObject
    {
        QString address;
        QString method;
        QString password;
        QString plugin;
        QString plugin_options;
        QString key;
        QString remarks; // Unused
        QString group;   // Unused
        int port;
        ShadowSocksServerObject()
            : address("0.0.0.0"), method("chacha20-ietf-poly1305"), password(""), plugin(""), plugin_options(""), key(""), 
              remarks(""), group(""), port(0)
        {
        }
#define _X_(json, key, type) this->key = json[#key].to##type()
        void loadJson(const QJsonObject &o)
        {
            _X_(o, address, String);
            _X_(o, method, String);
            _X_(o, password, String);
            _X_(o, plugin, String);
            _X_(o, plugin_options, String);
            _X_(o, key, String);
            _X_(o, remarks, String);
            _X_(o, group, String);
            _X_(o, port, Int);
        }
#undef _X_
        [[nodiscard]] static ShadowSocksServerObject fromJson(const QJsonObject &o)
        {
            ShadowSocksServerObject out;
            out.loadJson(o);
            return out;
        }
#define _X_(json, key) json[#key] = key
        QJsonObject toJson() const
        {
            QJsonObject out;
            _X_(out, address);
            _X_(out, method);
            _X_(out, password);
            _X_(out, plugin);
            _X_(out, plugin_options);
            _X_(out, key);
            _X_(out, remarks);
            _X_(out, group);
            _X_(out, port);
            return out;
        }
#undef _X_
    };

    QString SafeBase64Decode(QString string);
    QString SafeBase64Encode(const QString &string, bool trim = true);
} // namespace SSRPlugin
