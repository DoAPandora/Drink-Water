#include "main.hpp"
#include "scotland2/shared/modloader.h"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelSelectionNavigationController.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "bsml/shared/BSML.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Vector2.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

using namespace BSML;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace GlobalNamespace;

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

TMPro::TextMeshProUGUI* text;

// Called at the early stages of game loading
DRINK_WATER_EXPORT void setup(CModInfo* info) {
  *info = modInfo.to_c();

  INFO("Completed setup!");
}

MAKE_HOOK_MATCH(ResultsViewController_DidActivate, &ResultsViewController::DidActivate, void,
    ResultsViewController* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    ResultsViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    INFO("Level Completed!");

    if(firstActivation){
     text = BSML::Lite::CreateText(self->get_transform(), "Remember to drink water!", {0, 0}, {50, 10});
     text->set_fontSize(10.0f);
     text->get_transform()->set_localPosition({ 15.0f, 0.0f, 0.0f });

    } else {

    }
}

MAKE_HOOK_MATCH(LevelSelectionNavigationController_DidActivate, &LevelSelectionNavigationController::DidActivate, void,
    LevelSelectionNavigationController* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
        LevelSelectionNavigationController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        INFO("Level Selection Opened");

    if(firstActivation){
        text = BSML::Lite::CreateText(self->get_transform(), "Remember to touch grass!");

        text->get_transform()->set_localPosition({ 53.0f, -40.5f, 0.0f });
    } else {

    }
}
 

       
// Called later on in the game loading - a good time to install function hooks
DRINK_WATER_EXPORT void late_load() {
  il2cpp_functions::Init();
  BSML::Init();

INFO("Successfully installed UI!");

    INFO("Installing hooks...");
    INSTALL_HOOK(Logger, ResultsViewController_DidActivate);
    INSTALL_HOOK(Logger, LevelSelectionNavigationController_DidActivate);
    INFO("Installed all hooks!");
}
