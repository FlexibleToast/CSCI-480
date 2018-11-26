/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 7
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		11/30/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulate a FAT12 filesystem
*******************************************************************************/

#include "Entry.h"
#include "Assign7.h"

int main() {
	ifstream file;
	file.open("data7.txt");
	if(file.fail()){
		cerr << "Failed to open file data6.txt" << endl;
		exit(-1);
	}
	string line;
	initialize_directory();
	print_fat();
	while(getline(file, line))
	{	// Read each line from the file for instructions
		if(sim_counter % HOW_OFTEN == 0){	// Print current status every HOW_OFTEN
			// Print stuff
		}
		readline(line);
		sim_counter++;
	}
	list<Entry>::iterator it = directory.begin();
	while(it != directory.end()){
		cout << it->get_name() << endl;
		it++;
	}
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void initialize_directory(){
	// Create "." current directory
	new_entry(".", 512);
	// Create ".." parent directory
	new_entry("..", 0);
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void readline(string line){
	vector<string> tokens;
	tokenize(line, tokens);
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void new_entry(string new_name, size_t new_size)
{
	Entry new_entry_item(new_name, new_size,
		allocate(new_size, find_empty(0)), sim_counter);
	directory.push_back(new_entry_item);
	reallocate(512*ceil((float)directory.size()/BLOCK_ENTRIES), 0);
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int find_empty(int start){
	int found = -1;
	for(int empty = start; empty < 4096; empty++)
	{
		if(fat[empty] == 0){
			found = empty;
			break;
		}
	}
	if(found == -1){
		std::cerr << "No free blocks found" << '\n';
		return -1;
	}	// else
	return found;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int allocate(size_t size, int pass_start_block){
	int start_block = find_empty(pass_start_block);
	// Special case, size is 0
	if(size == 0){
		return -1;
	}
	// Else the size is greater than 0, find needed number of blocks
	int current_block = start_block;
	int needed_blocks = (ceil((float)size / BLOCK_SIZE));
	for(int i = 0; i < needed_blocks; i++){
		if(i == needed_blocks - 1)
		{	// If at the last block mark it end -1 and return
			fat[current_block] = -1;
			break;
		}
		fat[current_block] = -2; // Make current_block non empty so it isn't found
		current_block = fat[current_block] = find_empty(current_block);
	}
	return start_block;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int reallocate(size_t size, int start_block){
	// Special case, size is 0
	if(size == 0){
		deallocate(start_block);
		return -1;
	}
	if(start_block == -1){	// If previously empty, find a starting block
		start_block = find_empty();
	}
	// Initialize variables
	int allocated_blocks = count_clusters(start_block);
	int needed_blocks = (ceil((float)size / BLOCK_SIZE));
	int current_block = start_block;
	if(allocated_blocks == needed_blocks){	// No change in number of blocks
		return start_block;
	} else if(allocated_blocks < needed_blocks){	// Need more allocated blocks
		int i = 0;
		while(i++ < allocated_blocks - 1){	// Move to last block
			current_block = fat[current_block];
		}
		current_block = fat[current_block] = find_empty();
		while(++i < needed_blocks){	// Allocate new blocks
			fat[current_block] = -1;	// Make current_block non-empty
			current_block = fat[current_block] = find_empty(current_block);
		}
		fat[current_block] = -1;
		return start_block;
	} else {	// More space allocated than needed
		int i = 0;
		while(i++ < needed_blocks - 1){	// Move to end of needed blocks
			current_block = fat[current_block];
		}
		deallocate(fat[current_block]); // Free rest of of blocks
		fat[current_block] = -1;
	}
	return start_block;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void deallocate(int start_block){
	if(start_block == -1){	// Size was 0, no blocks assigned to deallocate
		return;
	}
	int next_block;
	while(fat[start_block] != -1){
		next_block = fat[start_block];
		fat[start_block] = 0;
		start_block = next_block;
	}
	fat[start_block] = 0;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int count_clusters(int start_block){
	int count = 0;
	int current_block = start_block;
	if(start_block == -1)	// Size 0, no clusters
		return count;
	while(fat[current_block] != -1){	// While not at last cluster, count
		count++;
		current_block = fat[current_block];
	}
	return ++count;
}
/*******************************************************************************
Function:		void tokenize(string line, vector<string> &tokens)
Use:				Tokenizes a line received as input
Arguments:	line - String to tokenize
						tokens - A vector to contain the tokens
Returns:		none
*******************************************************************************/
void tokenize(string line, vector<string> &tokens){
	if(line[line.size() - 1] == '\r')	// Remove carriage return if found
		line.erase(line.end()-1,line.end());
	char* token = strtok((char*)line.c_str(), " ");
	while(token)
	{	// Gather all tokens
		tokens.push_back((string)token);
		token = strtok(NULL, " ");
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void print_fat(){
	int counter = 0;
	while(counter < PRINT){
		if(!(counter % BLOCK_ENTRIES) && !(counter == 0))
			cout << '\n';
		cout << setw(4) << right << fat[counter++];
	}
	cout << '\n';
}
