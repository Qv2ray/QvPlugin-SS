#include "QvGUIPluginInterface.hpp"
#include "SSOutboundEditor.hpp"

using namespace Qv2rayPlugin;

class ShadowsocksPluginGUIInterface : public Qv2rayPlugin::PluginGUIInterface
{
    QIcon Icon() const
    {
        return QIcon(":/qv2ray.png");
    }
    QList<PluginGuiComponentType> GetComponents() const
    {
        return { GUI_COMPONENT_OUTBOUND_EDITOR };
    }
    std::unique_ptr<QvPluginSettingsWidget> createSettingsWidgets() const
    {
        return {};
    }
    QList<typed_plugin_editor> createInboundEditors() const
    {
        return {};
    }
    QList<typed_plugin_editor> createOutboundEditors() const
    {
        return { MakeEditorInfoPair<SSOutboundEditor>("shadowsocks-sip003", "Shadowsocks-SIP003") };
    }
    std::unique_ptr<QvPluginMainWindowWidget> createMainWindowWidget() const
    {
        return {};
    }
};
