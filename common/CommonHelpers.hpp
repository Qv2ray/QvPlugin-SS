#pragma once

#include "3rdparty/QJsonStruct/QJsonStruct.hpp"

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
    {
        method = "chacha20-ietf-poly1305";
        address = "0.0.0.0";
        port = 0;
    }
    JSONSTRUCT_REGISTER(ShadowSocksServerObject, F(address, method, password, plugin, plugin_options, key, remarks, group, port))
};

QString SafeBase64Decode(QString string);
QString SafeBase64Encode(const QString &string, bool trim = true);
