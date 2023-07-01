#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
#env = Environment(tools=['clangxx'])
#env = Environment(CXX = 'clang++',
#                  CXXFLAGS = '-std=c++17 -stdlib=libc++',
#                  LINKFLAGS = '-stdlib=libc++')
env.Append(CPPPATH=["src/"])
env.Append(CCFLAGS=['-g', '-Wextra', '-fdeclspec', '-fpermissive', '-I./src/include', '-I./src/models', '-I./src/procedural', '-I./src/datetime', '-I./src/jsoncpp', '-I./src/random', '-I./src/noise', '-I./src/gamelayer/models', '-I./src/gamelayer/enums', '-I./src/gamelayer/include', '-I./src/gamelayer/signalRHelper', '-I./src/gamelayer/utilities', '-I./src/gamelayer/framework', '-I./src/gamelayer/service'])
env.Append(LINKFLAGS=['-L./src/libs', '-lgd', '-lmicrosoft-signalr', '-pthread']) # '-lnoise'
#env = Environment(CXX = 'clang++',
#CXXFLAGS = '-std=c++11 -stdlib=libc++',
sources = Glob("src/*.cpp")
sources.extend(Glob("src/models/*.cpp"))
sources.extend(Glob("src/procedural/*.cpp"))
sources.extend(Glob("src/datetime/*.cpp"))
sources.extend(Glob("src/jsoncpp/*.cpp"))
sources.extend(Glob("src/random/*.cpp"))
sources.extend(Glob("src/noise/*.cpp"))
sources.extend(Glob("src/noise/model/*.cpp"))
sources.extend(Glob("src/noise/module/*.cpp"))
sources.extend(Glob("src/gamelayer/models/*.cpp"))
sources.extend(Glob("src/gamelayer/framework/*.cpp"))
sources.extend(Glob("src/gamelayer/service/*.cpp"))
sources.extend(Glob("src/gamelayer/utilities/*.cpp"))
sources.extend(Glob("src/gamelayer/signalRHelper/*.cpp"))

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "bin/libgdnative-nomadblst.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "bin/libgdnative-nomadblst{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
