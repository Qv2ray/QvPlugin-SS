#pragma once
#include "QvPluginProcessor.hpp"

class SSPluginEventHandler : public Qv2rayPlugin::PluginEventHandler
{
  public:
    SSPluginEventHandler();
    // SSR Plugin does not receive any events.
};
