/*
  ==============================================================================

    SaveControlPanelComp.h
    Created: 8 Jan 2015 21:031:30

  ==============================================================================
*/

#ifndef CCZ_SAVE_CONTROL_PANEL_COMPONENT_HEADER
#define CCZ_SAVE_CONTROL_PANEL_COMPONENT_HEADER

#include "JuceHeader.h"
#include "cczAssistLibLoader.h"
#include "InputStringConverter.h"
#include "cczAssistConfig.h"

using UILayoutConverter::Set_Comp_Pos;
using UILayoutConverter::Set_Comp_Size;
using UILayoutConverter::Get_UI_Text;

//==============================================================================
/*
*/
class SaveControlPanelComp 
    : public Component
    , public ButtonListener
{
public:    
    enum SavePanelDirection{ SPD_Vertical, SPD_Horizion};

public:
    SaveControlPanelComp(SavePanelDirection sd = SPD_Vertical)
        : bSetWhenStartup(true)
        , spdDirection(sd)
        , spListener(nullptr)
    {
        btn_WriteIn.setButtonText(Get_UI_Text("cczAssistMain_Text_WriteIn"));
        btn_Restore.setButtonText(Get_UI_Text("cczAssistMain_Text_Restore"));
        btn_Refresh.setButtonText(Get_UI_Text("cczAssistMain_Text_Refresh"));
        chkbx_SetWhenStartup.setButtonText(Get_UI_Text("cczSavePanel_chkbx_StartupEvalid"));
        chkbx_SetWhenStartup.setToggleState(true, sendNotification);
        btn_WriteIn.addListener(this);
        btn_Restore.addListener(this);
        btn_Refresh.addListener(this);
        chkbx_SetWhenStartup.addListener(this);
        if (spdDirection == SPD_Vertical)
        {
            Set_Comp_Size(&btn_WriteIn, "UL_SavePanel_btn_WriteIn");
            Set_Comp_Size(&btn_Restore, "UL_SavePanel_btn_Restore");
            Set_Comp_Size(&btn_Refresh, "UL_SavePanel_btn_Refresh");
            Set_Comp_Size(&chkbx_SetWhenStartup, "UL_SavePanel_chkbx_StartupEvalid");
        }
        else
        {
            Set_Comp_Size(&btn_WriteIn, "UL_SavePanel_btn_WriteIn_H");
            Set_Comp_Size(&btn_Restore, "UL_SavePanel_btn_Restore_H");
            Set_Comp_Size(&btn_Refresh, "UL_SavePanel_btn_Refresh_H");
            Set_Comp_Size(&chkbx_SetWhenStartup, "UL_SavePanel_chkbx_StartupEvalid_H");
        }

        addAndMakeVisible(btn_WriteIn);
        addAndMakeVisible(btn_Restore);
        addAndMakeVisible(btn_Refresh);
        addAndMakeVisible(chkbx_SetWhenStartup);
    }
    ~SaveControlPanelComp(){}

    void paint(Graphics& g)
    {
//         g.setColour (Colours::grey);
//         g.drawRect (getLocalBounds(), 1);
    }

    void resized()
    {
        if (spdDirection == SPD_Vertical)
        {
            Set_Comp_Pos(&chkbx_SetWhenStartup, "UL_SavePanel_chkbx_StartupEvalid");
            Set_Comp_Pos(&btn_WriteIn, "UL_SavePanel_btn_WriteIn");
            Set_Comp_Pos(&btn_Restore, "UL_SavePanel_btn_Restore");
            Set_Comp_Pos(&btn_Refresh, "UL_SavePanel_btn_Refresh");
        }
        else
        {
            Set_Comp_Pos(&chkbx_SetWhenStartup, "UL_SavePanel_chkbx_StartupEvalid_H");
            Set_Comp_Pos(&btn_WriteIn, "UL_SavePanel_btn_WriteIn_H");
            Set_Comp_Pos(&btn_Restore, "UL_SavePanel_btn_Restore_H");
            Set_Comp_Pos(&btn_Refresh, "UL_SavePanel_btn_Refresh_H");
        }
    }

    void buttonClicked(Button* btnThatClicked)
    {
        if (btnThatClicked == &chkbx_SetWhenStartup)
        {
            setWhenStartUp(chkbx_SetWhenStartup.getToggleState());
            if (spListener != nullptr)
            {
                spListener->OnEvalidCheckedChange(chkbx_SetWhenStartup.getToggleState());
            }
        }
        else if (spListener != nullptr)
        {
            if (btnThatClicked == &btn_Refresh)
            {
                spListener->OnSavePanelRefresh();
            }
            else if (btnThatClicked == &btn_Restore)
            {
                spListener->OnSavePanelRestore();
            }
            else if (btnThatClicked == &btn_WriteIn)
            {
                spListener->OnSavePanelWrite();
            }
        }
    }

    void setWhenStartUp(bool bSet) {bSetWhenStartup = bSet; }
    bool isSetWhenStartUp() { return bSetWhenStartup; }

    class SavePanelListener{
    public:
        SavePanelListener(){}
        virtual ~SavePanelListener(){}
        virtual void OnSavePanelWrite() = 0;
        virtual void OnSavePanelRestore() = 0;
        virtual void OnSavePanelRefresh() = 0;
        virtual void OnEvalidCheckedChange(bool) = 0;
    };

    void setSavePanelListener(SavePanelListener* p) { spListener = p; }

private:
    bool                bSetWhenStartup;
    SavePanelDirection  spdDirection;

private:
    ToggleButton        chkbx_SetWhenStartup;
    TextButton          btn_WriteIn;
    TextButton          btn_Restore;
    TextButton          btn_Refresh;
    SavePanelListener*  spListener;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaveControlPanelComp)

};

typedef SaveControlPanelComp::SavePanelListener SavePanelListener;

#endif  // CCZ_SAVE_CONTROL_PANEL_COMPONENT_HEADER
