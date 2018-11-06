/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 6
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		11/14/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:
*******************************************************************************/

#include "Memblock.h"
#include "Assign6.h"

int main() {
	initialize_avail();
	print_avail();
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void initialize_avail(){
	// First empty block starting at 3MB and 1MB in size
	Memblock new_block(3*MB, 1*MB);
	avail.push_back(new_block);
	// Second empty block 2MB
	new_block.update((new_block.get_end()), 2*MB);
	avail.push_back(new_block);
	// Third empty block 2MB
	new_block.update((new_block.get_end()), 2*MB);
	avail.push_back(new_block);
	// Fourth empty block 4MB
	new_block.update((new_block.get_end()), 4*MB);
	avail.push_back(new_block);
	// Fifth empty block 4MB
	new_block.update((new_block.get_end()), 4*MB);
	avail.push_back(new_block);
}

void print_avail(){
	list<Memblock>::iterator it = avail.begin();
	size_t total = 0;
	while(it != avail.end()){
		total += it->get_size();
		cout << "Starting address: " << it->get_start()
			<< ", size: " << it->get_size() << endl;
		it++;
	}
	cout << "Total size of available memory space: "
		<< (float)((total * 100)/MB)/100 << "MB" << endl;
}
