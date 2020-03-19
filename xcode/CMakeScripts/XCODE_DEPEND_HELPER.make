# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.CGL.Debug:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Debug/libCGL.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Debug/libCGL.a


PostBuild.glew.Debug:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Debug/libglew.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Debug/libglew.a


PostBuild.glfw.Debug:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Debug/libglfw3.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Debug/libglfw3.a


PostBuild.pathtracer.Debug:
PostBuild.CGL.Debug: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Debug/pathtracer
PostBuild.glew.Debug: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Debug/pathtracer
PostBuild.glfw.Debug: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Debug/pathtracer
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Debug/pathtracer:\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Debug/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Debug/libglew.a\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Debug/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Debug/pathtracer


PostBuild.CGL.Release:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Release/libCGL.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Release/libCGL.a


PostBuild.glew.Release:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Release/libglew.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Release/libglew.a


PostBuild.glfw.Release:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Release/libglfw3.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Release/libglfw3.a


PostBuild.pathtracer.Release:
PostBuild.CGL.Release: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Release/pathtracer
PostBuild.glew.Release: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Release/pathtracer
PostBuild.glfw.Release: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Release/pathtracer
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Release/pathtracer:\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Release/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Release/libglew.a\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Release/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/Release/pathtracer


PostBuild.CGL.MinSizeRel:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/MinSizeRel/libCGL.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/MinSizeRel/libCGL.a


PostBuild.glew.MinSizeRel:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/MinSizeRel/libglew.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/MinSizeRel/libglew.a


PostBuild.glfw.MinSizeRel:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a


PostBuild.pathtracer.MinSizeRel:
PostBuild.CGL.MinSizeRel: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/MinSizeRel/pathtracer
PostBuild.glew.MinSizeRel: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/MinSizeRel/pathtracer
PostBuild.glfw.MinSizeRel: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/MinSizeRel/pathtracer
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/MinSizeRel/pathtracer:\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/MinSizeRel/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/MinSizeRel/libglew.a\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/MinSizeRel/pathtracer


PostBuild.CGL.RelWithDebInfo:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/RelWithDebInfo/libCGL.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/RelWithDebInfo/libCGL.a


PostBuild.glew.RelWithDebInfo:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a


PostBuild.glfw.RelWithDebInfo:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a


PostBuild.pathtracer.RelWithDebInfo:
PostBuild.CGL.RelWithDebInfo: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/RelWithDebInfo/pathtracer
PostBuild.glew.RelWithDebInfo: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/RelWithDebInfo/pathtracer
PostBuild.glfw.RelWithDebInfo: /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/RelWithDebInfo/pathtracer
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/RelWithDebInfo/pathtracer:\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/RelWithDebInfo/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a\
	/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/RelWithDebInfo/pathtracer




# For each target create a dummy ruleso the target does not have to exist
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Debug/libCGL.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/MinSizeRel/libCGL.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/RelWithDebInfo/libCGL.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/Release/libCGL.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Debug/libglew.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/MinSizeRel/libglew.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glew/Release/libglew.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Debug/libglfw3.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a:
/Users/ziyezhong/desktop/CS284/p3-1-pathtracer-sp20-ZiyeZhong/xcode/CGL/deps/glfw/src/Release/libglfw3.a:
/usr/local/lib/libfreetype.dylib:
