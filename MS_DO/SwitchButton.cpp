#include "SwitchButton.h"

#include "Engine_DO/Entity.h"
#include "Engine_DO/Image.h"
#include "Globals.h"
namespace SwitchButton
{
static Size switchButtonSize{Config::FLAG_COUNTER_WIDTH,
                             Config::FOOTER_HEIGHT - Config::PADDING};

void init(InitParams& i_params)
{
    createImage(i_params.em, i_params.id, Config::REFRESH_IMAGE);
    auto switchButtonIdx = i_params.em.idsToIndexes[i_params.id];
    i_params.em.sizes[switchButtonIdx] = switchButtonSize;
}
}  // namespace SwitchButton