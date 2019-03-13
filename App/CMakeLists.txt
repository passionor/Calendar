set(HEAD_FILES
    DlgAbout/DlgAbout.h 
    MainWindow.h 
    FrmUpdater.h 
    DlgOption.h)
set(SOURCE_FILES
    DlgAbout/DlgAbout.cpp 
    main.cpp 
    MainWindow.cpp 
    FrmUpdater.cpp 
    DlgOption.cpp)
set(SOURCE_UI_FILES
    DlgAbout/DlgAbout.ui
    MainWindow.ui
    FrmUpdater.ui
    DlgOption.ui)
SET(RCC_FILES
    ${CMAKE_SOURCE_DIR}/Src/Resource/Resource.qrc
    )
if(ANDROID)
    SET(RCC_FILES ${RCC_FILES} ${CMAKE_BINARY_DIR}/translations.qrc)
endif()
set(OTHER_FILES AppIcon.ico)

add_definitions(-DBUILD_VERSION="${BUILD_VERSION}")
add_definitions(-DBUILD_ARCH="${BUILD_ARCH}")
add_definitions(-DBUILD_PLATFORM="${BUILD_PLATFORM}")

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()
add_executable(${PROJECT_NAME}App ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES} AppIcon.rc ${RCC_FILES})
SET(APP_LIBS ${PROJECT_NAME} ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME}App ${APP_LIBS})
target_include_directories(${PROJECT_NAME}App PUBLIC "${CMAKE_SOURCE_DIR}/Src" "${CMAKE_BINARY_DIR}")
# Install target
INSTALL(TARGETS ${PROJECT_NAME}App
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
    
# Install other files
INSTALL(FILES ${OTHER_FILES} DESTINATION ".")

IF(WIN32)
    SET(RUNTIME_FILE "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}App${CMAKE_EXECUTABLE_SUFFIX}")
    IF(CMAKE_BUILD_TYPE MATCHES Release AND MINGW)
        #windeployqt 分发时，是根据是否 strip 来判断是否是 DEBUG 版本,而用mingw编译时,qt没有自动 strip
        add_custom_command(TARGET ${PROJECT_NAME}App POST_BUILD
            COMMAND strip "$<TARGET_FILE:${PROJECT_NAME}App>"
            )
    ENDIF()

    #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中  
    add_custom_command(TARGET ${PROJECT_NAME}App POST_BUILD
        COMMAND "${QT_INSTALL_DIR}/bin/windeployqt"
        --compiler-runtime
        --verbose 7
        "$<TARGET_FILE:${PROJECT_NAME}App>"
        )
    INSTALL(DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}App>/" DESTINATION "${CMAKE_INSTALL_BINDIR}")
    
ENDIF(WIN32)

#IF(ANDROID)
#    GENERATED_DEPLOYMENT_SETTINGS()
#    find_program(ANT NAMES ant) # PATHS  "/usr/bin")
#    MESSAGE("ant:${ANT}\n")

#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/libRabbitIm.so ${CMAKE_BINARY_DIR}/android-build/libs/${ANDROID_ABI}/libRabbitIm.so
#        #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中
#        COMMAND "${QT_INSTALL_DIR}/bin/androiddeployqt"
#            --input ${CMAKE_BINARY_DIR}/android-libRabbitIm.so-deployment-settings.json
#            --output ${CMAKE_BINARY_DIR}/android-build
#            --verbose
#            #--ant /usr/bin/ant
#            #--jdk $ENV{JAVA_HOME}
#    )
#ENDIF(ANDROID)
