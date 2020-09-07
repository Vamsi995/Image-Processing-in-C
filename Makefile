LIBDIR := lib
OBJDIR := obj
EXEDIR := bin

EXE := $(EXEDIR)/Iprocess
LIBS := $(addprefix $(LIBDIR)/,libmatrixmath.a libtransformation.a)
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard include/*.h)
OBJS := $(addprefix $(OBJDIR)/,$(patsubst src/%.c,%.o,$(SRCS)))

vpath %.c src
vpath %.h include



# all: $(EXE)
# 	@echo "Finished Successfully"

.PHONY: build	
build: obj/main.o liba | $(EXEDIR)
	gcc -o $(EXE) -I include $< -L lib -lmatrixmath -ltransformation -lm

$(OBJDIR)/%.o: src/%.c matrix.h transformation.h | $(OBJDIR)
	gcc -o $@ -c -I include $<
	
# $(LIBDIR)/libmatrixmath.a: obj/matrix.o include/matrix.h include/transformation.h | $(LIBDIR)
# 	ar rcs $@ $^

# $(LIBDIR)/libtransformation.a: obj/transformation.o obj/matrix.o include/matrix.h include/transformation.h | $(LIBDIR) 
# 	ar rcs $@ $^

.PHONY: liba
liba: obj/matrix.o obj/transformation.o include/matrix.h include/transformation.h | $(LIBDIR)
	ar rcs $(LIBDIR)/libmatrixmath.a obj/matrix.o include/matrix.h include/transformation.h
	ar rcs $(LIBDIR)/libtransformation.a $^



$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)


.PHONY: run
run:
	./bin/Iprocess Images/input.ppm run

.PHONY: T1
T1:
	./bin/Iprocess Images/input.ppm T1


.PHONY: T2
T2:
	./bin/Iprocess Images/input.ppm T2


.PHONY: clean
clean:
	rm -rf $(EXEDIR) $(OBJDIR) $(LIBDIR)
