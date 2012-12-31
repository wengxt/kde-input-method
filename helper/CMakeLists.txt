add_executable(qtimmoduledetector qtimmoduledetector.cpp)
add_executable(imenvloader imenvloader.cpp)

target_link_libraries(qtimmoduledetector ${KDE4_KIO_LIBS})
target_link_libraries(imenvloader ${KDE4_KIO_LIBS})

install(TARGETS qtimmoduledetector DESTINATION ${LIBEXEC_INSTALL_DIR})
install(TARGETS imenvloader DESTINATION ${LIBEXEC_INSTALL_DIR})
install(FILES gtkimmoduledetector.sh RENAME gtkimmoduledetector DESTINATION ${LIBEXEC_INSTALL_DIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(FILES setimenv.sh DESTINATION ${LIBEXEC_INSTALL_DIR})
