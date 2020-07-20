#include "SSPlugin.hpp"
#include "core/Serializer.hpp"
#include "ui/SSROutboundEditor.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>
namespace SSPlugin
{
    std::unique_ptr<QvPluginKernel> QvSSPlugin::CreateKernel()
    {
        return std::make_unique<SSKernelInstance>();
    }

    std::shared_ptr<QvPluginSerializer> QvSSPlugin::GetSerializer()
    {
        return serializer;
    }

    bool QvSSPlugin::UpdateSettings(const QJsonObject &conf)
    {
        settings = conf;
        return true;
    }

    bool QvSSPlugin::Initialize(const QString &, const QJsonObject &settings)
    {
        emit PluginLog("Initialize plugin.");
        this->settings = settings;
        eventHandler = std::make_shared<SSPluginEventHandler>(this);
        serializer = std::make_shared<SSSerializer>(this);
        return true;
    }

    const QJsonObject QvSSPlugin::GetSettngs()
    {
        emit PluginLog("Getting plugin settings.");
        return settings;
    }

    std::shared_ptr<QvPluginEventHandler> QvSSPlugin::GetEventHandler()
    {
        return eventHandler;
    }

    std::unique_ptr<QWidget> QvSSPlugin::GetSettingsWidget()
    {
        return nullptr;
    }

    std::unique_ptr<QvPluginEditor> QvSSPlugin::GetEditorWidget(UI_TYPE type)
    {
        switch (type)
        {
            case UI_TYPE_INBOUND_EDITOR:
            case UI_TYPE_GROUP_EDITOR: break;
            case UI_TYPE_OUTBOUND_EDITOR:
            {
                return std::make_unique<SSOutboundEditor>();
            }
        }
        return nullptr;
    }
} // namespace SSRPlugin
