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
	int sim_counter = 0;
	initialize_directory();
	// while(getline(file, line))
	// {	// Read each line from the file for instructions
	// 	if(sim_counter % HOW_OFTEN == 0){	// Print current status every HOW_OFTEN
	// 		// Print stuff
	// 	}
	// 	readline(line);
	// 	sim_counter++;
	// }
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
	int start_block = allocate(0);
	Entry first(".", 0, start_block);
	cout << "First entry is: " << first.get_name() << ", with starting block: "
		<< first.get_start() << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
// void readline(string line){
// 	vector<string> tokens;
// 	tokenize(line, tokens);
// }
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int find_empty(){
	for(int empty = 0; empty < 4096; empty++)
	{
		if(fat[empty] == 0)
			return empty;
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
int allocate(size_t size){
	int start_block = find_empty();
	// Special case, size is 0
	if(size == 0){
		fat[start_block] = -1;
		return start_block;
	}
	// Else the size is greater than 0
	int current_block = start_block;
	int needed_blocks = (size / BLOCK_SIZE);
	if((size / BLOCK_SIZE) > 0)
		needed_blocks++;
	while(needed_blocks-- > 0){
		if(needed_blocks == 0){
			fat[current_block] = -1;
			return start_block;
		}
		fat[current_block] = find_empty();
		current_block = fat[current_block];
	}
}

/*******************************************************************************
Function:		void tokenize(string line, vector<string> &tokens)
Use:				Tokenizes a line received as input
Arguments:	line - String to tokenize
						tokens - A vector to contain the tokens
Returns:		none
*******************************************************************************/
// void tokenize(string line, vector<string> &tokens){
// 	if(line[line.size() - 1] == '\r')	// Remove carriage return if found
// 		line.erase(line.end()-1,line.end());
// 	char* token = strtok((char*)line.c_str(), " ");
// 	while(token)
// 	{	// Gather all tokens
// 		tokens.push_back((string)token);
// 		token = strtok(NULL, " ");
// 	}
// }
