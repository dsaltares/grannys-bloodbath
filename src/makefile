# Rutas
MOTOR_DIR := engine

# Ejecutable
EXE := grannys-bloodbath
EXEWIN := grannys-bloodbath.exe

# Ficheros fuente del juego
SRC := main.cpp

# Ficheros fuente del motor.
SRC_MOTOR := sound.o image.o font.o music.o parser.o logger.o scene.o\
		scenemngr.o application.o keyboard.o fpsmngr.o\
		resourcemngr.o scene.o story.o boxedtext.o game.o\
		enemy.o animation.o level.o hud.o granny.o actor.o\
		collisionmngr.o menu.o option.o zombie.o dog.o bullet.o \
		item.o actorfactory.o specialscene.o fat.o boss.o spider.o
		
# motor_dir + fuentes
SRC_DIR_MOTOR := $(foreach src, $(SRC_MOTOR),$(MOTOR_DIR)/$(src) )

# Objetos
OBJS := $(SRC:%.cpp=%.o)
OBJS_MOTOR := $(SRC_DIR_MOTOR:%.cpp=%.o)

OPTIMIZACION := 0

# Compilador y las opciones 
CXX = c++ 
CXXFLAGS = -pedantic -Wall -pipe -ggdb -D"TIXML_USE_TICPP" -I$(MOTOR_DIR) -O$(OPTIMIZACION)
LDFLAGS =  -L$(MOTOR_DIR)/ticpp -lticpp -lSDL -ggdb -lSDL_ttf -lSDL_mixer -lSDL_image
LDWINFLAGS = -L$(MOTOR_DIR)/ticpp -lticppwin -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

# Config para make
all: $(EXE)
win32: $(EXEWIN)

# Obtención del ejecutable 
$(EXE): $(OBJS) $(OBJS_MOTOR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEWIN): $(OBJS) $(OBJS_MOTOR)
	$(CXX) -o $@ $^ $(LDWINFLAGS)

# Limpieza
clean: 
	 $(RM) $(EXE) $(OBJS) $(OBJS_MOTOR) *~ -rf

clean-win32:
	del $(EXEWIN) *.o .\motor\*.o *~

