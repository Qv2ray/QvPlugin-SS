#pragma once
#include "3rdparty/shadowsocks-uvw/src/SSThread.hpp"
#include "QvPluginProcessor.hpp"
#include "SSPlugin.hpp"
#include "common/CommonHelpers.hpp"
#include "utils/HttpProxy.hpp"

using namespace Qv2rayPlugin;

class SSKernelInstance : public PluginKernel
{
  public:
    explicit SSKernelInstance(QvSSPlugin *_parent) : parent(_parent) {}
    bool StartKernel() override;
    bool StopKernel() override;
    void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &options, const QJsonObject &settings) override;
    QString GetKernelName() const override
    {
        return "SIP003";
    }

  private:
    int socks_local_port;
    int http_local_port;
    bool enable_udp;
    QString listen_address;
    ShadowSocksServerObject outbound;
    std::unique_ptr<Qv2rayPlugin::Utils::HttpProxy> httpProxy;
    std::unique_ptr<SSThread> ssrThread;
    QvSSPlugin *parent;
};

class SSKernelInterface : public PluginKernelInterface {
public:
    explicit SSKernelInterface(QvSSPlugin *_parent) : parent(_parent) {}

    std::unique_ptr<PluginKernel> CreateKernel() const final {
        return std::make_unique<SSKernelInstance>(parent);
    }

    QList<QString> GetKernelProtocols() const final {
        return {"shadowsocks-sip003"};
    }

private:
    QvSSPlugin *parent;
};
