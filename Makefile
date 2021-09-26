
SOURCES += main.cpp CharacterSet.cpp
SOURCES += external/discord-rpc/src/connection_win.cpp external/discord-rpc/src/discord_register_win.cpp external/discord-rpc/src/discord_rpc.cpp external/discord-rpc/src/rpc_connection.cpp external/discord-rpc/src/serialization.cpp
INCFLAGS += -Iexternal/discord-rpc/include -Iexternal/rapidjson/include
LDLIBS += -lpsapi -ladvapi32
PROJECT_BASENAME = krdiscordrpc

RC_LEGALCOPYRIGHT ?= Copyright (C) 2021-2021 Julian Uy; See details of license at license.txt, or the source code location.

include external/ncbind/Rules.lib.make
