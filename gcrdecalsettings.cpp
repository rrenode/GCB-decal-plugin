#include "pch.h"
#include "gcrdecals.h"

void gcrdecals::RenderSettings() {
    ImGui::TextUnformatted("Plugin developed to make activating GCB Decals Easier. Contact `im_rob` on Discord for support.");

    if (ImGui::Button("Install Decals")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("GcrDecalInstall");
            });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Installs Decals");
    }
    if (ImGui::Button("Activate GCB Octane")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("ActivateOctane");
            cvarManager->executeCommand("gcb_cur_body \"Oct\"");
            });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Activates Default GCB Octane");
    }
    if (ImGui::Button("Activate GCB Fennec")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("ActivateFennec");
            cvarManager->executeCommand("gcb_cur_body \"Fen\"");
            });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Activates Default GCB Octane");
    }
    if (ImGui::Button("Activate GCB Dominus")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("ActivateDominus");
            cvarManager->executeCommand("gcb_cur_body \"Dom\"");
            });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Activates Default GCB Dominus");
    }

       
    std::string currentCar = cvarManager->getCvar("gcb_cur_body").getStringValue();
    const char* items[] = { "Home (Black)", "Away (White)" };
    static int item_current_idx = 0;
    const char* current_item = items[item_current_idx];

    if (ImGui::BeginCombo("Blue Team Decal", current_item))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (current_item == items[n]);
            if (ImGui::Selectable(items[n], is_selected))
            {
                current_item = items[n];
                item_current_idx = n;

                // Update the CVar based on the current car and selected item
                std::string model = "GCBOctane"; // Default to Octane
                if (currentCar == "Fen") {
                    model = "GCBFennec";
                }
                else if (currentCar == "Dom") {
                    model = "GCBDominus";
                }

                std::string team = "Home";
                if (item_current_idx == 0) { // Home (Black)
                    team = "Home";
                }
                else { // Away (White)
                    team = "Away";
                }

                std::string cvarValue = model + team;

                cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_blue \"" + cvarValue + "\"");
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    std::string o_currentCar = cvarManager->getCvar("gcb_cur_body").getStringValue();
    const char* o_items[] = {"Away (White)", "Home (Black)"};
    static int o_item_current_idx = 0;
    const char* o_current_item = o_items[o_item_current_idx];

    if (ImGui::BeginCombo("Orange Team Decal", o_current_item))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (o_current_item == o_items[n]);
            if (ImGui::Selectable(o_items[n], is_selected))
            {
                o_current_item = o_items[n];
                o_item_current_idx = n;

                // Update the CVar based on the current car and selected item
                std::string model = "GCBOctane"; // Default to Octane
                if (o_currentCar == "Fen") {
                    model = "GCBFennec";
                }
                else if (o_currentCar == "Dom") {
                    model = "GCBDominus";
                }

                std::string team = "Away";
                if (o_item_current_idx == 0) { // Away (White)
                    team = "Away";
                }
                else { // Home (Black)
                    team = "Home";
                }

                std::string cvarValue = model + team;

                cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_orange \"" + cvarValue + "\"");
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}