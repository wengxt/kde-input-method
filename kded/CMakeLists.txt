add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})

set(kded_imlauncher_PART_SRCS  imlauncher.cpp )

kde4_add_plugin(kded_imlauncher  ${kded_imlauncher_PART_SRCS})

target_link_libraries(kded_imlauncher  ${KDE4_KIO_LIBS})

install(TARGETS kded_imlauncher  DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES imlauncher.desktop  DESTINATION  ${SERVICES_INSTALL_DIR}/kded )
