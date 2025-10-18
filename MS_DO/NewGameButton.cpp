#include "NewGameButton.h"

#include "Engine_DO/EntityManager.h"
#include "Engine_DO/Text.h"
#include "Globals.h"
namespace NewGameButton
{
constexpr inline Size size{Config::NEW_GAME_BUTTON_WIDTH,
                           Config::FOOTER_HEIGHT - Config::PADDING};
std::string wording = "NEW GAME";
void init(InitParams& params)
{
    auto id = params.id;
    auto& em = params.em;

    createText(em, id, wording, {0, 0, 0, 255}, 20, size);
}

}  // namespace NewGameButton