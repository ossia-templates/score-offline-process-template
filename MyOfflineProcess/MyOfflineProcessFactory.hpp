#pragma once
#include <Process/OfflineAction/OfflineAction.hpp>

namespace MyOfflineProcess
{

class GainDoubler final : public Process::OfflineAction
{
  SCORE_CONCRETE("00000000-0000-0000-0000-000000000000")

  QString title() const noexcept override;
  UuidKey<Process::ProcessModel> target() const noexcept override;
  void apply(Process::ProcessModel& proc, const score::DocumentContext&) override;
};
}