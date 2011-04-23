#this is for chess game

src=main.c init_screen.c basic_shape.c
para=-o main -Wall

main:$(src)
	gcc $(src) $(para)
clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
run:
	./main
