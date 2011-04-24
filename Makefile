#this is for chess game

src=main.c init_screen.c basic_shape.c print_board.c mouse_op.c chess_op.c
para=-o main -Wall

main:$(src)
	gcc $(src) $(para)
clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
run:
	./main
