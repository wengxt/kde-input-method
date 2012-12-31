include_directories(${CMAKE_CURRENT_BINARY_DIR})
########### next target ###############

set(kcm_imchooser_SRCS
    kcm_imchooser.cpp
    immodel.cpp
    )

kde4_add_ui_files(kcm_imchooser_SRCS imchooser.ui)

kde4_add_plugin(kcm_imchooser ${kcm_imchooser_SRCS})


target_link_libraries(kcm_imchooser  ${KDE4_KIO_LIBS})

install(TARGETS kcm_imchooser  DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES imchooser.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )


