all: 
	cd SP; make all
	$(MAKE) SPCalculator
SPCalculator: SPList.o SPListElement.o main.o hashTable.o TreeNode.o calculator.o build.o expressionOfTree.o#Extends dependency list
	gcc -std=c99 -g -Wall -Werror -pedantic-errors  SPList.o SPListElement.o main.o hashTable.o TreeNode.o calculator.o build.o expressionOfTree.o -o SPCalculator 

main.o: main.c calculator.h expressionOfTree.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c main.c
	
TreeNode.o: TreeNode.c TreeNode.h errorMessages.h
	gcc -std=c99 -g -Wall -Werror -pedantic-errors -c TreeNode.c

expressionOfTree.o: expressionOfTree.c expressionOfTree.h TreeNode.h
	gcc -std=c99 -g -Wall -Werror -pedantic-errors -c expressionOfTree.c
	
build.o: build.c build.h TreeNode.h hashTable.h
	gcc -std=c99 -g -Wall -Werror -pedantic-errors -c build.c

calculator.o: calculator.c calculator.h build.h
	gcc -std=c99 -g -Wall -Werror -pedantic-errors -c calculator.c

hashTable.o : hashTable.c hashTable.h SPList.h SPListElement.h errorMessages.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c hashTable.c

SPList.o: SPList.c SPList.h SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPList.c

SPListElement.o: SPListElement.c SPListElement.h
	gcc -std=c99 -Wall -Werror -pedantic-errors -c SPListElement.c 
	
clean:
	cd SP; make clean
	rm -fr SPList.o SPListElement.o main.o hashTable.o TreeNode.o calculator.o build.o#Extend to remove other object files you created.
	