mess : ./mess/c/mess.o ./mess/c/read_key.o ./mess/c/read_line.o ./mess/c/window_control.o ./mess/c/init.o ./mess/c/file_info.o ./mess/c/display.o
	gcc -o mess ./mess/c/mess.o ./mess/c/read_key.o ./mess/c/read_line.o ./mess/c/window_control.o ./mess/c/init.o ./mess/c/file_info.o ./mess/c/display.o
./mess/c/mess.o : ./mess/c/mess.c
	gcc -c ./mess/c/mess.c -o ./mess/c/mess.o
./mess/c/read_key.o : ./mess/c/read_key.c
	gcc -c ./mess/c/read_key.c -o ./mess/c/read_key.o
./mess/c/read_line.o : ./mess/c/read_line.c
	gcc -c ./mess/c/read_line.c -o ./mess/c/read_line.o
./mess/c/window_control.o : ./mess/c/window_control.c
	gcc -c ./mess/c/window_control.c -o ./mess/c/window_control.o
./mess/c/init.o : ./mess/c/init.c
	gcc -c ./mess/c/init.c -o ./mess/c/init.o
./mess/c/file_info.o : ./mess/c/file_info.c
	gcc -c ./mess/c/file_info.c -o ./mess/c/file_info.o
./mess/c/display.o : ./mess/c/display.c
	gcc -c ./mess/c/display.c -o ./mess/c/display.o
clean :
	rm ./mess/c/mess.o ./mess/c/read_key.o ./mess/c/read_line.o ./mess/c/window_control.o ./mess/c/init.o ./mess/c/file_info.o ./mess/c/display.o
