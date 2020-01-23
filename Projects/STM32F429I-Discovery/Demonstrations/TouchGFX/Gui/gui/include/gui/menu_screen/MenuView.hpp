/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  


#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>
#include <gui/menu_screen/Tile.hpp>
#include <gui/menu_screen/LiveDataDisplayTile.hpp>
#include <gui/menu_screen/HomeAutomationTile.hpp>
#include <gui/menu_screen/AnimatedGraphicsTile.hpp>
#include <gui/menu_screen/ChromArtTile.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>

class MenuView : public View<MenuPresenter>
{
public:

    MenuView();

    virtual ~MenuView() { }

    virtual void setupScreen();
    virtual void tearDownScreen();

    void addRoomToHomeAutomationTile(RoomTemperatureInfo& room);
    void initializeTiles();

private:
    static const int TILE_OFFSET = 17;

    Image backgroundTop;
    Image backgroundBottom;

    Tile<LiveDataDisplayTile> liveDataDisplayTile;
    Tile<HomeAutomationTile> homeAutomationTile;
    Tile<AnimatedGraphicsTile> animatedGraphicsTile;
    Tile<ChromArtTile> chromArtTile;

    Callback<MenuView, const AbstractButton&> onButtonPressed;

    void buttonPressedhandler(const AbstractButton& button);
};

#endif // MENU_VIEW_HPP
