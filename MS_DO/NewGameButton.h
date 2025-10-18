#pragma once
#include "Engine_DO/Entity.h"

namespace NewGameButton
{
using namespace Entity;
struct InitParams
{
    EntityId id;
    EntityManager& em;
};
extern void init(InitParams&);
}  // namespace NewGameButton