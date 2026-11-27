ADD_LIBRARY(
  Screens INTERFACE)

TARGET_LINK_LIBRARIES(
  Screens
  INTERFACE ScreenAcceleration
            ScreenArrows
            ScreenButtons
            ScreenCounter
            ScreenHour
            ScreenHourglass
            ScreenMario
            ScreenNorth
            ScreenSand
            ScreenShapes
            ScreenSound
            ScreenTemperature
            ScreenText
            ScreenButtonHandler)

ADD_SUBDIRECTORY(Acceleration)
ADD_SUBDIRECTORY(Arrows)
ADD_SUBDIRECTORY(Buttons)
ADD_SUBDIRECTORY(Counter)
ADD_SUBDIRECTORY(Hour)
ADD_SUBDIRECTORY(Hourglass)
ADD_SUBDIRECTORY(Mario)
ADD_SUBDIRECTORY(North)
ADD_SUBDIRECTORY(Sand)
ADD_SUBDIRECTORY(Shapes)
ADD_SUBDIRECTORY(Sound)
ADD_SUBDIRECTORY(Temperature)
ADD_SUBDIRECTORY(Text)
ADD_SUBDIRECTORY(ButtonHandler)
