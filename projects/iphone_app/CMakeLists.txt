cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

set(PROJ_NAME "IPhoneApp")

project (${PROJ_NAME})

# Needs to be checked after project init
if( CMAKE_SYSTEM_NAME STREQUAL "Darwin" )
  set( NOM_PLATFORM_OSX true )

  # Setup the SDK selection for backwards compatibility
  if( NOM_BUILD_IOS )
    message( STATUS "Targeting iOS" )

    # Override this platform and tell CMake to cross compile to iOS.
    SET( CMAKE_CROSSCOMPILING TRUE )
    SET( CMAKE_SYSTEM_NAME "Darwin" )
    SET( CMAKE_SYSTEM_PROCESSOR "arm" )

    # Setup the valid architectures.
    set( CMAKE_OSX_ARCHITECTURES "${ARCHS_STANDARD_32_BIT}" )
    # SET( CMAKE_OSX_ARCHITECTURES "${ARCHS_UNIVERSAL_IPHONE_OS}" )

    # Allow simulator and deploy.
    SET( CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator" )

    set( SDKVER "7.1" )
    set( DEVROOT "/Applications/Developer/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer" )
    set( SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk" )

    IF( EXISTS ${SDKROOT} )
      # FIXME:
      #
      # SET( CMAKE_OSX_SYSROOT "${SDKROOT}" )
      # set( CMAKE_OSX_DEPLOYMENT_TARGET "${SDKVER}" )
      # set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -miphoneos-version-min=${SDKVER}" )

      # FIXME: we cannot enable this until *after* the project has been built
      # the first time, otherwise CMake freaks out about not being able to use
      # clang to build. This setting sets the Base SDK to the latest iOS build.
      #
      # If we do not have this set, we must manually set the SDK each time the
      # project file is regenerated.
      #
      # See also: http://www.ogre3d.org/forums/viewtopic.php?f=4&t=73613
      #
      # See also: CMake error message: "The C compiler
      # "/Applications/Developer/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
      # is not able to compile a simple test program.
      #
      # SET( CMAKE_OSX_SYSROOT "iphoneos" )
    else()
      message( FATAL_ERROR "Error: iOS SDK ${SDKVER} not found at: ${SDKROOT}" )
    endif()

  elseif( NOM_PLATFORM_OSX )
    set( SDKVER "11.3" ) # FIXME: This should be OS X v10.7
    set( DEVROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer" )
    set( SDKROOT "${DEVROOT}/SDKs/MacOSX${SDKVER}.sdk" )

    if( EXISTS ${SDKROOT} )
      set( CMAKE_OSX_SYSROOT "${SDKROOT}" )
      set( CMAKE_OSX_DEPLOYMENT_TARGET "${SDKVER}" )
      set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=${SDKVER}" )
    else()
      message( FATAL_ERROR "Error: Mac OS X SDK ${SDKVER} not found at: ${SDKROOT}" )
    endif()
  endif( NOM_BUILD_IOS )

  # libc++ requires OSX v10.7+
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )

  if ( CMAKE_GENERATOR STREQUAL "Xcode" )
    set ( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11" )
    set ( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++" )
  endif ( CMAKE_GENERATOR STREQUAL "Xcode" )

  if( NOM_BUILD_IOS )
    message( STATUS "Platform: iOS" )
  else( NOT NOM_BUILD_IOS )
    message( STATUS "Platform: Darwin (Mac OS X)" )
  endif( NOM_BUILD_IOS )

endif( CMAKE_SYSTEM_NAME STREQUAL "Darwin" )

# IF(APPLE)
#   set(CMAKE_OSX_SYSROOT iphoneos8.1)
#   set(CMAKE_OSX_ARCHITECTURES "armv7;arm64;x86_64")
#   set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
# ENDIF(APPLE)

set(CMAKE_SYSTEM_NAME IOS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../engine/src)

# Gather list of header and source files for compilation
file(GLOB_RECURSE MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp)

# Build project, give it a name and includes list of file to be compiled
add_executable(${PROJ_NAME} ${MAIN_FILE} ${CPP_FILES} ${HPP_FILES})

target_include_directories (${PROJ_NAME} 
    PUBLIC ${SFML_INCLUDE_DIR}
)

if( NOM_BUILD_IOS )
SET_TARGET_PROPERTIES (
    ${PROJECT_NAME}
    PROPERTIES
    XCODE_ATTRIBUTE_SDKROOT
    "iphoneos"
)

SET_TARGET_PROPERTIES (
    ${PROJECT_NAME}
    PROPERTIES
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY
    "iPhone Developer: Jeffrey Carpenter"
)
endif( NOM_BUILD_IOS )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message("ENV{LIB_PATH}: $ENV{LIB_PATH}")
message("{PROJECT_BINARY_DIR}: ${PROJECT_BINARY_DIR}")
add_custom_command(
    TARGET ${PROJ_NAME} POST_BUILD
    COMMAND cp -rf
        $ENV{LIB_PATH}
        ${PROJECT_BINARY_DIR}
)

target_link_libraries (${PROJ_NAME} engine)

