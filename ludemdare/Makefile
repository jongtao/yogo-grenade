BUILD = build/
SOURCE = src/
OBJS := $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o,$(wildcard $(SOURCE)*.cpp))

CC = g++
OPTS = -Wall -g -ansi

# The first LIBS is static. The second LIBS is dynamic. Choose ONE.
LIBS = `pkg-config --libs --static allegro-static-5 allegro_image-static-5\
 allegro_audio-static-5 allegro_acodec-static-5 allegro_font-static-5 allegro_ttf-static-5` -lpng
#LIBS = -lallegro -lallegro_image -lallegro_audio -lallegro_acodec

game: $(OBJS)
	$(CC) -o $@ $(OBJS) $(OPTS) $(LIBS)

$(BUILD)main.o: $(patsubst %,$(SOURCE)%, main.cpp init.h constants.h game.h\
)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)init.o: $(patsubst %,$(SOURCE)%,init.cpp init.h constants.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)input.o: $(patsubst %,$(SOURCE)%,input.cpp input.h constants.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)game.o: $(patsubst %,$(SOURCE)%,game.cpp game.h input.h render.h\
mapdata.h gamedata.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)render.o: $(patsubst %,$(SOURCE)%,render.cpp render.h init.h\
constants.h input.h mapdata.h gamedata.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)mapdata.o: $(patsubst %,$(SOURCE)%,mapdata.cpp mapdata.h init.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)gamedata.o: $(patsubst %,$(SOURCE)%,gamedata.cpp gamedata.h physics.h\
mapdata.h constants.h input.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)physics.o: $(patsubst %,$(SOURCE)%,physics.cpp physics.h mapdata.h\
constants.h)
	$(CC) -o $@ -c $(OPTS) $<
$(BUILD)audio.o: $(patsubst %,$(SOURCE)%,audio.cpp audio.h init.h)
	$(CC) -o $@ -c $(OPTS) $<

.PHONY: clean

clean:
	rm -rf $(OBJS)
