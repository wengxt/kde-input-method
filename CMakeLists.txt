project(kde-input-method)

find_package(KDE4 REQUIRED)

include_directories(${QT4_INCLUDES} ${KDE4_INCLUDES})
add_definitions(${QT4_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(kded)
add_subdirectory(inputmethod)

add_subdirectory(kcontrol)

add_subdirectory(helper)
