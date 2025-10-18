#include "DifficultyLabel.h"

#include "Engine_DO/EntityManager.h"
#include "Engine_DO/Text.h"
#include "Globals.h"
namespace DifficultyLabel
{
constexpr inline Size size{Config::DIFFICULTY_LABEL_WIDTH,
                           Config::FOOTER_HEIGHT - Config::PADDING};
std::string wording = "LEVEL: ";
void init(InitParams& i_params)
{
    auto id = i_params.id;
    auto& em = i_params.em;
    auto levelStr = wording + i_params.i_level;

    createText(em, id, levelStr, {0, 0, 0, 255}, 20, size);
}
}  // namespace DifficultyLabel