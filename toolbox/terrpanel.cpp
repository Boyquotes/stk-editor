#include "toolbox/terrpanel.hpp"
#include "editor.hpp"

TerrPanel* TerrPanel::m_terr_panel = 0;

// ----------------------------------------------------------------------------
void TerrPanel::init()
{
    IGUIEnvironment* gui_env = Editor::getEditor()->getGUIEnv();

    IGUIFont* font = gui_env->getFont(L"font/font2.png");

    m_wndw->setRelativePosition(position2di(0, 50));
    
    gui_env->addStaticText(L"Height Drawer:", rect<s32>(10, 10, 200, 30), 
                           false, false, m_wndw, -1, false);

    gui_env->addStaticText(L"Radius:", rect<s32>(15, 40, 100, 60),
                           false, false, m_wndw, -1, false)->setOverrideFont(font);

    m_h_radius = gui_env->addScrollBar(true, rect<s32>(100, 45, 240, 55),
        m_wndw, H_RADIUS);
    m_h_radius->setMin(1);
    m_h_radius->setMax(100);
    m_h_radius->setSmallStep(1);
    m_h_radius->setLargeStep(10);
    m_h_radius->setPos(60);

    gui_env->addStaticText(L"Intensity:", rect<s32>(15, 70, 100, 90),
                           false, false, m_wndw, -1, false)->setOverrideFont(font);

    m_h_intensity = gui_env->addScrollBar(true, rect<s32>(100, 75, 240, 85),
        m_wndw, H_INTENSITY);
    m_h_intensity->setMin(-100);
    m_h_intensity->setMax(100);
    m_h_intensity->setSmallStep(1);
    m_h_intensity->setLargeStep(10);
    m_h_intensity->setPos(10);

    gui_env->addStaticText(L"Edge:", rect<s32>(15, 130, 100, 150),
                           false, false, m_wndw, -1, false)->setOverrideFont(font);

    m_active_edge_frame = gui_env->addImage(rect<s32>(100, 125, 140, 165), m_wndw);
    m_active_edge_frame->setImage(Editor::loadImg("img/frame.png"));

    IGUIButton* b1 = gui_env->addButton(rect<s32>(105, 130, 135, 160),  m_wndw, H_EDGE_1);
    IGUIButton* b2 = gui_env->addButton(rect<s32>(155, 130, 185, 160), m_wndw, H_EDGE_2);
    IGUIButton* b3 = gui_env->addButton(rect<s32>(205, 130, 235, 160), m_wndw, H_EDGE_3);
    b1->setImage(Editor::loadImg("img/edge1.png"));
    b2->setImage(Editor::loadImg("img/edge2.png"));
    b3->setImage(Editor::loadImg("img/edge3.png"));

    m_tmod.ID = 0;
    m_tmod.countdown = -1;
    m_tmod.edge_type = 1;
    refreshTerrModData();

} // init

// ----------------------------------------------------------------------------
TerrPanel* TerrPanel::getTerrPanel(IGUIWindow* wndw)
{
    if (m_terr_panel != 0) return m_terr_panel;

    m_terr_panel = new TerrPanel();
    m_terr_panel->m_wndw = wndw;
    m_terr_panel->init();
    return m_terr_panel;
} // getTerrPanel

// ----------------------------------------------------------------------------
void TerrPanel::btnDown(int btn)
{
    switch (btn)
    {
    case H_EDGE_1:
        m_tmod.edge_type = 1;
        m_active_edge_frame->setRelativePosition(position2di(100, 125));
        break;
    case H_EDGE_2:
        m_tmod.edge_type = 2;
        m_active_edge_frame->setRelativePosition(position2di(150, 125));
        break;
    case H_EDGE_3:
        m_tmod.edge_type = 3;
        m_active_edge_frame->setRelativePosition(position2di(200, 125));
        break;
    }
} // btnDown

// ----------------------------------------------------------------------------
void TerrPanel::refreshTerrModData()
{
    m_tmod.radius = m_h_radius->getPos() / 10.0f;
    m_tmod.dh     = m_h_intensity->getPos() / 10.0f;
}
