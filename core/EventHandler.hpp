#pragma once
#include "QvPluginProcessor.hpp"

class SSPluginEventHandler : public Qv2rayPlugin::QvPluginEventHandler
{
  public:
    SSPluginEventHandler(QObject *parent = nullptr);
    // SSR Plugin does not receive any events.
};
