include("/home/ryabi/my_apps/qt/vs_code_qt/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/vs_code_qt-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/ryabi/my_apps/qt/vs_code_qt/build/vs_code_qt"
    GENERATE_QT_CONF
)
