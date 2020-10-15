#pragma once
#include "3rdparty/shadowsocks-uvw/src/SSThread.hpp"
#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "utils/HttpProxy.hpp"

using namespace Qv2rayPlugin;

class SSKernelInstance : public PluginKernel
{
  public:
    explicit SSKernelInstance(QObject *parent = nullptr);
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
};

class SSKernelInterface : public PluginKernelInterface
{
    std::unique_ptr<PluginKernel> CreateKernel() const
    {
        return std::make_unique<SSKernelInstance>();
    }
    QList<QString> GetKernelProtocols() const
    {
        return { "shadowsocks-sip003" };
    }
};
