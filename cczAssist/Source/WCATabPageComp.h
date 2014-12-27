/*
  ==============================================================================

    WCA: Weapon Clothes Assistants

  ==============================================================================
*/
#ifndef WCA_TAB_PAGE_COMPONENT_H_INCLUDED
#define WCA_TAB_PAGE_COMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "cczAssistConfig.h"
#include "cczAssistLibLoader.h"
#include "InputStringConverter.h"
#include "memModRecComp.h"

namespace UILC = UILayoutConverter;

using InputStringConverter::convertinputtoulong;
using InputStringConverter::convertinputbytes;

class WCAListListener{
public:
    virtual ~WCAListListener()  {}
    virtual void onSelectedRowChanged(int rowSelected) = 0;

};

class WCAListModel : public ListBoxModel
    , public Component
{
public:
    WCAListModel()
        : listener(nullptr)
    {

    }

    ~WCAListModel()
    {

    }

    void initListData()
    {
        getItems(true);
    }

    int getNumRows()
    {
        if (items.empty())
        {
            getItems(false);
        }
        return items.size();
    }

    ItemDetail getItemDetail(int rowNum)
    {
        return items.at(rowNum);
    }

    void selectedRowsChanged(int lastRowSelected)
    {
        if (nullptr != listener)
        {
            listener->onSelectedRowChanged(lastRowSelected);
        }
    }

    void paintListBoxItem (int rowNumber,
        Graphics& g,
        int width, int height,
        bool rowIsSelected)
    {
        if (rowIsSelected)
            g.fillAll (findColour (TextEditor::highlightColourId));

        ItemDetail id = items[rowNumber];
        std::vector<char> szName;
        for (int i = 0; i < 17; ++i)
        {
            szName.push_back(id.szName[i]);
        }
        g.drawText(InputStringConverter::ConvertGBKToUtf8Str(szName), 
            juce::Rectangle<float>(1.0, 1.0, width, height),
            Justification::centredLeft);
        
    }

    void setListListener(WCAListListener* wcaLln)
    {
        listener = wcaLln;
    }

private:
    void getItems(bool bRepeat = false)
    {
        items = cczAssistLibLoader::getInstance()->GetCczItems(bRepeat);
    }

private:
    WCAListListener*        listener;
    std::vector<ItemDetail> items;
};

class WCATabPageComp   : public Component
    , public ButtonListener
    , public TextEditorListener
    , public WCAListListener
    , public ChangeListener
{
public:
    //==============================================================================
    WCATabPageComp()
    {
        lstModel.setListListener(this);
        lstWCA.setModel(&lstModel);
        lstWCA.setMultipleSelectionEnabled(false);
        lstWCA.selectRow(0);
        
        lbl_WCAName.setText(UILC::Get_UI_Text("cczWCA_Label_WCAName"), dontSendNotification);
        lbl_WCAName.setJustificationType(Justification::centredRight);
        lbl_PicNum.setText(UILC::Get_UI_Text("cczWCA_Label_PicNum"), dontSendNotification);
        lbl_PicNum.setJustificationType(Justification::centredRight);
        lbl_Price.setText(UILC::Get_UI_Text("cczWCA_Label_Price"), dontSendNotification);
        lbl_Price.setJustificationType(Justification::centredRight);
        lbl_EffectName.setText(UILC::Get_UI_Text("cczWCA_Label_EffectName"), dontSendNotification);
        lbl_EffectName.setJustificationType(Justification::centredRight);
        lbl_EffectVal.setText(UILC::Get_UI_Text("cczWCA_Label_EffectVal"), dontSendNotification);
        lbl_EffectVal.setJustificationType(Justification::centredRight);
        lbl_TypeName.setText(UILC::Get_UI_Text("cczWCA_Label_TypeName"), dontSendNotification);
        lbl_TypeName.setJustificationType(Justification::centredRight);
        lbl_OriginVal.setText(UILC::Get_UI_Text("cczWCA_Label_OriginVal"), dontSendNotification);
        lbl_OriginVal.setJustificationType(Justification::centredRight);
        lbl_LvDelta.setText(UILC::Get_UI_Text("cczWCA_Label_LvDelta"), dontSendNotification);
        lbl_LvDelta.setJustificationType(Justification::centredRight);

        UILC::Set_Comp_Size(&lstWCA, "UL_WCA_lstbox_WCAMain");
        UILC::Set_Comp_Size(&lbl_WCAName, "UL_WCA_lbl_WCAName");
        UILC::Set_Comp_Size(&lbl_PicNum, "UL_WCA_lbl_PicNum");
        UILC::Set_Comp_Size(&lbl_Price, "UL_WCA_lbl_Price");
        UILC::Set_Comp_Size(&lbl_EffectName, "UL_WCA_lbl_EffectName");
        UILC::Set_Comp_Size(&lbl_EffectVal, "UL_WCA_lbl_EffectVal");
        UILC::Set_Comp_Size(&lbl_TypeName, "UL_WCA_lbl_TypeName");
        UILC::Set_Comp_Size(&lbl_OriginVal, "UL_WCA_lbl_OriginVal");
        UILC::Set_Comp_Size(&lbl_LvDelta, "UL_WCA_lbl_LvDelta");

        lbl_Price__Val.setEditable(true);
        StringArray st;
        for (int i = 0; i < 78; ++i)
        {
            st.add(String(kItemProperName[i].c_str()));
        }
        combo_EffectNVal.addItemList(st, 1);
//         combo_EffectVVal.setText("100", dontSendNotification);
        //combo_EffectVVal.addItem("30", -1);
        StringArray stType;
        for (int i = 0; i < 18; ++i)
        {
            stType.add(String(kItemProperName[i].c_str()));
        }
        combo_TypeNamVal.addItemList(stType, 1);
        lbl_OriginVVal.setText("100", dontSendNotification);
        lbl_OriginVVal.setEditable(true);
        lbl_LvDelt_Val.setText("100", dontSendNotification);
        lbl_LvDelt_Val.setEditable(true);

        UILC::Set_Comp_Size(&lbl_WCANam_Val, "UL_WCA_lbl_WCANam_Val");
        UILC::Set_Comp_Size(&lbl_PicNum_Val, "UL_WCA_lbl_PicNum_Val");
        UILC::Set_Comp_Size(&lbl_Price__Val, "UL_WCA_lbl_Price__Val");
        UILC::Set_Comp_Size(&combo_EffectNVal, "UL_WCA_lbl_EffectNVal");
        UILC::Set_Comp_Size(&combo_EffectVVal, "UL_WCA_lbl_EffectVVal");
        UILC::Set_Comp_Size(&combo_TypeNamVal, "UL_WCA_lbl_TypeNamVal");
        UILC::Set_Comp_Size(&lbl_OriginVVal, "UL_WCA_lbl_OriginVVal");
        UILC::Set_Comp_Size(&lbl_LvDelt_Val, "UL_WCA_lbl_LvDelt_Val");

        addAndMakeVisible(lstWCA);
        addAndMakeVisible(lbl_WCAName);
        addAndMakeVisible(lbl_PicNum);
        addAndMakeVisible(lbl_Price);
        addAndMakeVisible(lbl_EffectName);
        addAndMakeVisible(lbl_EffectVal);
        addAndMakeVisible(lbl_TypeName);
        addAndMakeVisible(lbl_OriginVal);
        addAndMakeVisible(lbl_LvDelta);

        addAndMakeVisible(lbl_WCANam_Val);
        addAndMakeVisible(lbl_PicNum_Val);
        addAndMakeVisible(lbl_Price__Val);
        addAndMakeVisible(combo_EffectNVal);
        addAndMakeVisible(combo_EffectVVal);
        addAndMakeVisible(combo_TypeNamVal);
        addAndMakeVisible(lbl_OriginVVal);
        addAndMakeVisible(lbl_LvDelt_Val);
    }

    ~WCATabPageComp()
    {
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colour (0xffeeddff));

        g.setFont (Font (16.0f));
        g.setColour (Colours::black);
    }

    void resized()
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        UILC::Set_Comp_Pos(&lstWCA, "UL_WCA_lstbox_WCAMain");
        UILC::Set_Comp_Pos(&lbl_WCAName, "UL_WCA_lbl_WCAName");
        UILC::Set_Comp_Pos(&lbl_PicNum,"UL_WCA_lbl_PicNum");
        UILC::Set_Comp_Pos(&lbl_Price, "UL_WCA_lbl_Price");
        UILC::Set_Comp_Pos(&lbl_EffectName, "UL_WCA_lbl_EffectName");
        UILC::Set_Comp_Pos(&lbl_EffectVal, "UL_WCA_lbl_EffectVal");
        UILC::Set_Comp_Pos(&lbl_TypeName, "UL_WCA_lbl_TypeName");
        UILC::Set_Comp_Pos(&lbl_OriginVal, "UL_WCA_lbl_OriginVal");
        UILC::Set_Comp_Pos(&lbl_LvDelta, "UL_WCA_lbl_LvDelta");

        UILC::Set_Comp_Pos(&lbl_WCANam_Val, "UL_WCA_lbl_WCANam_Val");
        UILC::Set_Comp_Pos(&lbl_PicNum_Val, "UL_WCA_lbl_PicNum_Val");
        UILC::Set_Comp_Pos(&lbl_Price__Val, "UL_WCA_lbl_Price__Val");
        UILC::Set_Comp_Pos(&combo_EffectNVal, "UL_WCA_lbl_EffectNVal");
        UILC::Set_Comp_Pos(&combo_EffectVVal, "UL_WCA_lbl_EffectVVal");
        UILC::Set_Comp_Pos(&combo_TypeNamVal, "UL_WCA_lbl_TypeNamVal");
        UILC::Set_Comp_Pos(&lbl_OriginVVal, "UL_WCA_lbl_OriginVVal");
        UILC::Set_Comp_Pos(&lbl_LvDelt_Val, "UL_WCA_lbl_LvDelt_Val");
    }

    void initData()
    {
        lstModel.initListData();
        int lstSelect = lstWCA.getSelectedRow();
        lstWCA.updateContent();
        lstWCA.selectRow(lstSelect);
        onSelectedRowChanged(lstSelect);
    }

    void buttonClicked(Button* btnThatClicked)
    {
    }

    void textEditorTextChanged (TextEditor& edt)
    {

    }

    void onSelectedRowChanged(int rowSelected)
    {
        if (rowSelected < 0 || rowSelected >= lstModel.getNumRows())
        {
            LOG(String("Wrong selected Row id: ") + String(rowSelected));
            return;
        }
        ItemDetail selItem = lstModel.getItemDetail(rowSelected);
        lbl_WCANam_Val.setText(InputStringConverter::ConvertGBKToUtf8Str(selItem.szName, 
            17), dontSendNotification);
        lbl_PicNum_Val.setText(String(selItem.byIcon), dontSendNotification);
        lbl_Price__Val.setText(selItem.byPrice == 255 ? 
            UILC::Get_UI_Text("cczWCA_Text_NoPrice")
            : String(selItem.byPrice * 100), dontSendNotification);
        if (selItem.byType < 18)
        {
            // ���
            if (selItem.byType % 2 == 0)
            {
                combo_EffectNVal.setSelectedId(combo_EffectNVal.getNumItems());
                combo_EffectVVal.setSelectedId(-1);
                combo_EffectVVal.setEnabled(false);
            }
            else
            {
                combo_EffectNVal.setSelectedItemIndex(selItem.bySpEffect);
                combo_EffectVVal.setSelectedItemIndex(selItem.bySpValue); // TODO:��Ϊ����
                combo_EffectVVal.setEnabled(true);
            }
            combo_TypeNamVal.setEnabled(true);
            combo_TypeNamVal.setSelectedItemIndex(selItem.byType);
            lbl_OriginVVal.setText(String(selItem.byLvOne), dontSendNotification);
            lbl_LvDelt_Val.setText(String(selItem.byLvInc), dontSendNotification);
        }
        else
        {
            // ����
            combo_EffectNVal.setSelectedItemIndex(selItem.byAstSpEff);
            combo_EffectVVal.setSelectedItemIndex(selItem.byAstSpValue); // TODO:��Ϊ����
            combo_EffectVVal.setEnabled(true);
            combo_TypeNamVal.setSelectedId(-1);
            combo_TypeNamVal.setEnabled(false);
            lbl_OriginVVal.setText(String::empty, dontSendNotification);
            lbl_LvDelt_Val.setText(String::empty, dontSendNotification);
        }
    }

    void changeListenerCallback(ChangeBroadcaster* source)
    {
        MainTabComponent* mainTab = (MainTabComponent*) source;
        if (mainTab->isCczRunning())
        {
            Sleep(3000);
            initData();
        }
    }

private:
    ListBox      lstWCA;
    WCAListModel lstModel;

    Label       lbl_WCAName;
    Label       lbl_PicNum;
    Label       lbl_Price;
    Label       lbl_EffectName;
    Label       lbl_EffectVal;
    Label       lbl_TypeName;
    Label       lbl_OriginVal;
    Label       lbl_LvDelta;

    Label       lbl_WCANam_Val;
    Label       lbl_PicNum_Val;
    Label       lbl_Price__Val;
    ComboBox    combo_EffectNVal;
    ComboBox    combo_EffectVVal;
    ComboBox    combo_TypeNamVal;
    Label       lbl_OriginVVal;
    Label       lbl_LvDelt_Val;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WCATabPageComp)
};

#endif WCA_TAB_PAGE_COMPONENT_H_INCLUDED
