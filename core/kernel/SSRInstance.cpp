
#include "3rdparty/shadowsocks-uvw/src/SSThread.hpp"
#include "SSInstance.hpp"
#include "common/CommonHelpers.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <memory>

namespace SSPlugin
{
    SSKernelInstance::SSKernelInstance(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
    {
    }

    void SSKernelInstance::SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings)
    {
        this->listen_address = options[KERNEL_LISTEN_ADDRESS].toString();
        socks_local_port = options[KERNEL_SOCKS_ENABLED].toBool() ? options[KERNEL_SOCKS_PORT].toInt() : 0;
        http_local_port = options[KERNEL_HTTP_ENABLED].toBool() ? options[KERNEL_HTTP_PORT].toInt() : 0;
        enable_udp = options[KERNEL_SOCKS_UDP_ENABLED].toBool();
        outbound.loadJson(settings);
    }

    bool SSKernelInstance::StartKernel()
    {
        if (socks_local_port == 0 && http_local_port == 0)
        {
            emit OnKernelCrashed("Both HTTP and SOCKS are not enabled");
            return false;
        }
        // If the socks has been disabled
        if (socks_local_port == 0)
            socks_local_port = http_local_port + 100;
        auto remotePort = outbound.port;
        auto remote_host = outbound.address.toStdString();
        auto method = outbound.method.toStdString();
        auto password = outbound.password.toStdString();
        auto key = outbound.key.toStdString();
        auto plugin= outbound.plugin.toStdString();
        auto plugin_opts= outbound.plugin_options.toStdString();
        auto mode = static_cast<SSThread::SSR_WORK_MODE>(enable_udp);
        ssrThread = std::make_unique<SSThread>(socks_local_port,             //
                                                remotePort,                   //
                                                60000, 1500, mode,            //
                                                listen_address.toStdString(), //
                                                remote_host,                  //
                                                method,                       //
                                                password,                     //
                                                plugin,                     //
                                                plugin_opts,
                                                key);
        ssrThread->connect(ssrThread.get(), &SSThread::onSSRThreadLog, this, &SSKernelInstance::OnKernelLogAvailable);
        ssrThread->connect(ssrThread.get(), &SSThread::OnDataReady, this, &SSKernelInstance::OnKernelStatsAvailable);
        ssrThread->start();
        if (http_local_port != 0)
        {
            httpProxy = std::make_unique<Qv2rayPlugin::Utils::HttpProxy>();
            httpProxy->httpListen(QHostAddress{ listen_address }, http_local_port, socks_local_port);
        }
        return true;
    }

    bool SSKernelInstance::StopKernel()
    {
        ssrThread.reset();
        httpProxy.reset();
        ssrThread = nullptr;
        httpProxy = nullptr;
        return true;
    }

} // namespace SSRPlugin
