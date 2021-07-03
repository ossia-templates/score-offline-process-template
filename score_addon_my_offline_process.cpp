#include "score_addon_my_offline_process.hpp"

#include <score/plugins/FactorySetup.hpp>

#include <MyOfflineProcess/MyOfflineProcessFactory.hpp>

score_addon_my_offline_process::score_addon_my_offline_process() { }

score_addon_my_offline_process::~score_addon_my_offline_process() { }

std::vector<std::unique_ptr<score::InterfaceBase>>
score_addon_my_offline_process::factories(
    const score::ApplicationContext& ctx,
    const score::InterfaceKey& key) const
{
  return instantiate_factories<
      score::ApplicationContext,
      FW<Process::OfflineAction, 
         MyOfflineProcess::GainDoubler>>(ctx, key);
}

#include <score/plugins/PluginInstances.hpp>
SCORE_EXPORT_PLUGIN(score_addon_my_offline_process)
