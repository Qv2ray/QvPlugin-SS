#include "SSPlugin.hpp"

#include "core/Serializer.hpp"
#include "ui/GUIInterface.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

bool QvSSPlugin::InitializePlugin(const QString &, const QJsonObject &_settings)
{
    emit PluginLog("Initialize plugin.");
    this->settings = _settings;
    eventHandler = std::make_shared<SSPluginEventHandler>();
    outboundHandler = std::make_shared<SSSerializer>();
    guiInterface = new ShadowsocksPluginGUIInterface();
    kernelInterface = std::make_shared<SSKernelInterface>();
    return true;
}
