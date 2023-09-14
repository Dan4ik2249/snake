all: snake_v3.c
	@echo "Build"
	@gcc snake_v3.c -o star.exe -lncurses -ltinfo
clean:
	@echo "Clear project"
	@rm -f *.exe
