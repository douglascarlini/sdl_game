CC = g++
SRC_DIR = src
DLL_DIR = bin
OBJ_NAME = main
BUILD_DIR = build
CFLAGS = -std=c++11
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Engine/*.cpp)  $(wildcard $(SRC_DIR)/Engine/ECS/*.cpp) $(wildcard $(SRC_DIR)/Game/*.cpp)

# MacOS
FRAMEWORK_DIR_MAC = -F/Library/Frameworks -framework SDL2 -F/Library/Frameworks -framework SDL2_image -F/Library/Frameworks -framework SDL2_mixer  -F/Library/Frameworks -framework SDL2_ttf
INCLUDE_PATHS_MAC = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers

# Windows
INCLUDE_PATHS_WIN = -IC:\dev\SDL2\include\SDL2 -IC:\dev\SDL2_image\include\SDL2 -IC:\dev\SDL2_ttf\include\SDL2
LIBRARY_PATHS_WIN = -LC:\dev\SDL2\lib -LC:\dev\SDL2_image\lib -LC:\dev\SDL2_ttf\lib
LIBRARY_LINKS_WIN = -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

mac:
	$(CC) $(CFLAGS) $(INCLUDE_PATHS_MAC) $(FRAMEWORK_DIR_MAC) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

win:
	$(CC) $(CFLAGS) -Wl,-subsystem,windows $(SRC_FILES) $(INCLUDE_PATHS_WIN) $(LIBRARY_PATHS_WIN) $(LIBRARY_LINKS_WIN) -o $(BUILD_DIR)/$(OBJ_NAME).exe
	copy /y $(DLL_DIR)\*.dll $(BUILD_DIR)
