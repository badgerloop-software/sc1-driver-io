QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backendprocesses.cpp \
        main.cpp \
        DataProcessor/DataGen.cpp \
        DataProcessor/DataUnpacker.cpp \
        embedded/drivers/src/i2c.cpp \
        embedded/drivers/src/serial.cpp \
        embedded/drivers/src/gpio.cpp \
        embedded/devices/src/ads1219.cpp \
        embedded/devices/src/ina3221.cpp \
        embedded/devices/src/tca6416.cpp \
        embedded/controlsWrapper.cpp

RESOURCES += qml.qrc \
    UI/Images/images.qrc \
    UI/fonts/fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    #android/AndroidManifest.xml \
    #android/AndroidManifest.xml \
    #android/build.gradle \
    #android/build.gradle \
    #android/gradle.properties \
    #android/gradle.properties \
    #android/gradle/.DS_Store \
    #android/gradle/.DS_Store \
    #android/gradle/wrapper/gradle-wrapper.jar \
    #android/gradle/wrapper/gradle-wrapper.jar \
    #android/gradle/wrapper/gradle-wrapper.properties \
    #android/gradle/wrapper/gradle-wrapper.properties \
    #android/gradlew \
    #android/gradlew \
    #android/gradlew.bat \
    #android/gradlew.bat \
    #android/res/values/libs.xml \
    #android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

HEADERS += \
    DataProcessor/DataUnpacker.h \
    DataProcessor/DataGen.h \
    backendprocesses.h \
    embedded/drivers/include/i2c.h \
    embedded/drivers/include/i2c-dev.h \
    embedded/drivers/include/serial.h \
    embedded/drivers/include/gpio.h \
    embedded/devices/include/ads1219.h \
    embedded/devices/include/ina3221.h \
    embedded/devices/include/tca6416.h \
    embedded/controlsWrapper.h
