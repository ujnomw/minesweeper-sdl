#pragma once
#include "Engine_DO/EntityManager.h"

namespace SwitchButton
{
using namespace Entity;
struct InitParams
{
    EntityId id;
    EntityManager& em;
};
extern void init(InitParams& i_params);
}  // namespace SwitchButton