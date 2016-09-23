Target	=	bomberman

SRCS	=	src/main.cpp		\
		src/Graph.cpp		\
		src/Action.cpp		\
		src/AI.cpp		\
		src/Map.cpp		\
		src/Game.cpp		\
		src/Entity.cpp		\
		src/Player.cpp		\
		src/Bot.cpp		\
		src/Item.cpp		\
		src/Pack.cpp		\
		src/Binding.cpp		\
		src/SoundManager.cpp	\
		src/CreateMap.cpp	\
		src/Exception.cpp	\
		src/UserInterface.cpp \
		src/Tools.cpp \
		src/RunGame.cpp

XeffectsSources	=	lib/irrlicht-xeffects/EffectHandler.cpp \
			lib/irrlicht-xeffects/CShaderPre.cpp

OBJS = $(SRCS:.cpp=.o)

IrrlichtHome :=	lib/irrlicht/

USERCXXFLAGS = -O3 -ffast-math
CXX = clang++ -std=c++11
CPPFLAGS = -I$(IrrlichtHome)/include -I/usr/X11R6/include -Iinclude/ -Ilib/SFML-audio/include/ -Ilib/irrlicht-xeffects/ $(USERCPPFLAGS)
CXXFLAGS = $(USERCXXFLAGS)
LDFLAGS = $(USERLDFLAGS)
LDFLAGS += -L$(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht -Llib/bin/. -lsfml-audio -lsfml-system
LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
SYSTEM=Linux
GAME = bomberman
INSTALL_DIR=/opt/bomberman

all: $(GAME)

install:	all
	@if [ `id -u` != 0 ]; then \
		echo "\033[31mYou need to run this command as root\033[0m"; exit 1; \
	else \
		echo "Installing bomberman..."; \
		rm -r $(INSTALL_DIR); \
		mkdir -p $(INSTALL_DIR) && \
		cp -r media music sound font lib bomberman.conf $(GAME) launch $(INSTALL_DIR) && \
		echo '#!/bin/bash' > /usr/bin/bomberman && \
		echo '$(INSTALL_DIR)/launch' >> /usr/bin/bomberman && chmod +x /usr/bin/bomberman && \
		echo "\033[32mInstallation successfull\033[0m"; \
	fi

uninstall:
	$(warning Uninstalling...)
	$(RM) -r $(INSTALL_DIR)
	$(RM) /usr/bin/bomberman

$(GAME):	$(OBJS)
		$(warning Building the game...)
		$(CXX) -o $(GAME) $(OBJS) $(CPPFLAGS) $(CXXFLAGS) $(XeffectsSources) $(LDFLAGS)

clean:
	$(warning Cleaning...)
	$(RM) $(OBJS)
	cd lib/SFML-audio/ ; make clean ; rm -f CMakeCache.txt
	cd $(IrrlichtHome)/source/Irrlicht/ && rm -f libIrrlicht.a && make clean

fclean: clean
	$(warning Cleaning...)
	$(RM) $(GAME)
	cd lib/SFML-audio/ ; make clean ; rm -f CMakeCache.txt;
	cd $(IrrlichtHome)/source/Irrlicht/ && rm -f libIrrlicht.a && make clean

re:	fclean $(GAME)

sfml:
	$(warning Compiling sfml-audio...)
	cd lib/SFML-audio/ ; rm -f CMakeCache.txt ; cmake . ; make sfml-system sfml-audio; cp lib/* ../bin/

irrlicht:
	$(warning Compiling irrlicht...)
	cd $(IrrlichtHome)/source/Irrlicht/ && rm -f libIrrlicht.a && make

.PHONY: all clean sfml irrlicht re fclean
