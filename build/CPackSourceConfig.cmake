# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_APP_VALUE_LEN "1")
SET(CPACK_ARCHIVE_COMPONENT_INSTALL "ON")
SET(CPACK_BINARY_7Z "OFF")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "OFF")
SET(CPACK_BINARY_NSIS "ON")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_PRODUCTBUILD "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "OFF")
SET(CPACK_BINARY_ZIP "ON")
SET(CPACK_BINARY_ZIP "ON")
SET(CPACK_BUILD_SOURCE_DIRS "C:/XycaRend2;C:/XycaRend2/build")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 14 2015")
SET(CPACK_COMPONENTS_ALL "JKAMPCore;JKAMPClient;JKAMPServer;JKASPClient")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_GROUP_JK2SP_BOLD_TITLE "FALSE")
SET(CPACK_COMPONENT_GROUP_JK2SP_DESCRIPTION "Jedi Outcast single player game")
SET(CPACK_COMPONENT_GROUP_JK2SP_DISPLAY_NAME "Jedi Outcast Single Player")
SET(CPACK_COMPONENT_GROUP_JK2SP_EXPANDED "FALSE")
SET(CPACK_COMPONENT_GROUP_JKAMP_BOLD_TITLE "FALSE")
SET(CPACK_COMPONENT_GROUP_JKAMP_DESCRIPTION "Jedi Academy multiplayer game")
SET(CPACK_COMPONENT_GROUP_JKAMP_DISPLAY_NAME "Jedi Academy Multiplayer")
SET(CPACK_COMPONENT_GROUP_JKAMP_EXPANDED "FALSE")
SET(CPACK_COMPONENT_GROUP_JKASP_BOLD_TITLE "FALSE")
SET(CPACK_COMPONENT_GROUP_JKASP_DESCRIPTION "Jedi Academy single player game")
SET(CPACK_COMPONENT_GROUP_JKASP_DISPLAY_NAME "Jedi Academy Single Player")
SET(CPACK_COMPONENT_GROUP_JKASP_EXPANDED "FALSE")
SET(CPACK_COMPONENT_JK2SPCLIENT_DESCRIPTION "Files required to play the Jedi Outcast single player game.")
SET(CPACK_COMPONENT_JK2SPCLIENT_DISPLAY_NAME "Core")
SET(CPACK_COMPONENT_JK2SPCLIENT_GROUP "JK2SP")
SET(CPACK_COMPONENT_JKAMPCLIENT_DESCRIPTION "Files required to play the multiplayer game.")
SET(CPACK_COMPONENT_JKAMPCLIENT_DISPLAY_NAME "Client")
SET(CPACK_COMPONENT_JKAMPCLIENT_GROUP "JKAMP")
SET(CPACK_COMPONENT_JKAMPCORE_DESCRIPTION "Core files shared by the multiplayer client and server executables.")
SET(CPACK_COMPONENT_JKAMPCORE_DISPLAY_NAME "Core")
SET(CPACK_COMPONENT_JKAMPCORE_GROUP "JKAMP")
SET(CPACK_COMPONENT_JKAMPCORE_REQUIRED "TRUE")
SET(CPACK_COMPONENT_JKAMPSERVER_DESCRIPTION "Files required to run a Jedi Academy server.")
SET(CPACK_COMPONENT_JKAMPSERVER_DISPLAY_NAME "Server")
SET(CPACK_COMPONENT_JKAMPSERVER_GROUP "JKAMP")
SET(CPACK_COMPONENT_JKASPCLIENT_DESCRIPTION "Files required to play the Jedi Academy single player game.")
SET(CPACK_COMPONENT_JKASPCLIENT_DISPLAY_NAME "Core")
SET(CPACK_COMPONENT_JKASPCLIENT_GROUP "JKASP")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "7Z;ZIP")
SET(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY "0")
SET(CPACK_INSTALLED_DIRECTORIES "C:/XycaRend2;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "C:/XycaRend2/install")
SET(CPACK_MODULE_PATH "C:/XycaRend2/CMakeModules")
SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
			CreateShortCut '$SMPROGRAMS\\$STARTMENU_FOLDER\\Jedi Academy MP.lnk' \\
				'$INSTDIR\\openjk.x86.exe' \\
				'' \\
				'C:\\XycaRend2\\codemp\\win32\\icon.ico'
			CreateShortCut '$SMPROGRAMS\\$STARTMENU_FOLDER\\Jedi Academy SP.lnk' \\
				'$INSTDIR\\openjk_sp.x86.exe' \\
				'' \\
				'C:\\XycaRend2\\code\\win32\\starwars.ico'")
SET(CPACK_NSIS_DELETE_ICONS_EXTRA "
			Delete '$SMPROGRAMS\\$MUI_TEMP\\Jedi Academy MP.lnk'
			Delete '$SMPROGRAMS\\$MUI_TEMP\\Jedi Academy SP.lnk'")
SET(CPACK_NSIS_DISPLAY_NAME "OpenJK")
SET(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MUI_ICON "C:/XycaRend2/shared/icons/icon.ico")
SET(CPACK_NSIS_MUI_UNIICON "C:/XycaRend2/shared/icons/icon.ico")
SET(CPACK_NSIS_PACKAGE_NAME "OpenJK")
SET(CPACK_NSIS_URL_INFO_ABOUT "http://openjk.org")
SET(CPACK_OUTPUT_CONFIG_FILE "C:/XycaRend2/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "C:/cmake-3.9.4-win64-x64/share/cmake-3.9/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An improved Jedi Academy")
SET(CPACK_PACKAGE_FILE_NAME "OpenJK-1.0.0-Source")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenJK")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "OpenJK")
SET(CPACK_PACKAGE_NAME "OpenJK")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "JACoders")
SET(CPACK_PACKAGE_VERSION "1.0.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RESOURCE_FILE_LICENSE "C:/XycaRend2/LICENSE.txt")
SET(CPACK_RESOURCE_FILE_README "C:/XycaRend2/README.md")
SET(CPACK_RESOURCE_FILE_WELCOME "C:/cmake-3.9.4-win64-x64/share/cmake-3.9/Templates/CPack.GenericWelcome.txt")
SET(CPACK_RPM_PACKAGE_SOURCES "ON")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "ON")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "7Z;ZIP")
SET(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "C:/XycaRend2;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/XycaRend2/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "OpenJK-1.0.0-Source")
SET(CPACK_SOURCE_RPM "")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TOPLEVEL_TAG "win32-Source")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "ON")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "win32")
SET(CPACK_TOPLEVEL_TAG "win32-Source")
SET(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/XycaRend2/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
