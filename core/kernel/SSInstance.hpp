#pragma once
#include "3rdparty/shadowsocks-uvw/src/SSThread.hpp"
#include "QvPluginProcessor.hpp"
#include "common/CommonHelpers.hpp"
#include "utils/HttpProxy.hpp"
namespace SSPlugin
{
    class SSKernelInstance : public Qv2rayPlugin::QvPluginKernel
    {
      public:
        explicit SSKernelInstance(QObject *parent = nullptr);
        bool StartKernel() override;
        bool StopKernel() override;
        void SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings) override;

      private:
        int socks_local_port;
        int http_local_port;
        bool enable_udp;
        QString listen_address;
        ShadowSocksServerObject outbound;
        std::unique_ptr<Qv2rayPlugin::Utils::HttpProxy> httpProxy;
        std::unique_ptr<SSThread> ssrThread;
    };
} // namespace SSRPlugin
