#pragma once

// constants that define the window size
#define screenWidth 1750
#define screenHeight 800

// player
#define playerSpeed 2.5f
#define playerDimensions 25.0f
#define playerBorderSize 10.0f

// balls
#define ballRadius 15.0f
#define ballRadiusOutline 10.0f

// interface
#define interfaceBarHeight screenHeight/12

// color (map)
#define mapBackground Color { 161, 165, 247, 255}
#define mapCheckerColor Color { 197, 200, 248, 255 }
#define mapComponentSafeColor Color {152, 248, 143, 255}

// map
#define mapComponentDimensions 50
#define mapHeight (screenHeight - interfaceBarHeight)
#define mapCenterX screenWidth/2
#define mapCenterY (mapHeight)/2
#define mapTitleFontSize 50
#define mapTitleDisplacement 30

// tests
#define testDuration 3

// ghost player
#define ghostPlayerDimensions playerDimensions + playerBorderSize
#define ghostPlayerTransparency 0.20f
#define ghostPlayerColor ColorAlpha(BLACK, ghostPlayerTransparency)
