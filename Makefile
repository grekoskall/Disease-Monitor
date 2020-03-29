dm:
	@echo "Compile Disease Monitor...";
	g++ -I ./Header\ Files/ ./Source\ Files/l_item.cpp ./Source\ Files/trees.cpp ./Source\ Files/hashtable.cpp ./Source\ Files/linked_list.cpp ./Source\ Files/record.cpp ./Source\ Files/date.cpp ./Source\ Files/main.cpp -o ./runner
