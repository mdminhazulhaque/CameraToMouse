QT       += core gui
TARGET   = CameraToMouse
#CONFIG   -= console
#CONFIG   += app_bundle
#TEMPLATE = app
SOURCES  += main.cpp
LIBS     += \
-lopencv_core\
-lopencv_highgui\
-lopencv_imgproc\
-lopencv_objdetect\
-lopencv_photo\
-lopencv_video
