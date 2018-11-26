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
		cerr << "Failed to open file data7.txt" << endl;
		exit(-1);
	}
	string line;
	initialize_directory();
	while(getline(file, line))
	{	// Read each line from the file for instructions
		if(sim_counter % HOW_OFTEN == 0){	// Print current status every HOW_OFTEN
			// Print stuff
		}
		readline(line);
		sim_counter++;
	}
	list<Entry>::iterator it = directory.begin();
	print_directory();
	print_fat();
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
	if(tokens.size() == 0)
		return;
	switch(tokens[0][0]){
		case 'C':
			cout << "Transaction:  Copy a file" << endl;
			copy_entry(tokens[1], tokens[2]);
			break;
		case 'D':
			cout << "Transaction:  Delete a file" << endl;
			delete_entry(tokens[1]);
			break;
		case 'N':
			cout << "Transaction:  Add a new file" << endl;
			new_entry(tokens[1], stoi(tokens[2]));
			break;
		case 'M':
			cout << "Transaction:  Modify a file" << endl;
			modify_entry(tokens[1], stoi(tokens[2]));
			break;
		case 'R':
			cout << "Transaction:  Rename a file" << endl;
			rename_entry(tokens[1], tokens[2]);
			break;
		case '?':
			cout << "\nEnd of the FAT simulation\n" << endl;
			break;
		default:
			cerr << tokens[0][0] << " not a valid simulation step" << '\n';
			break;
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void copy_entry(string old_entry, string copied_entry){
	if(!(exist_entry(old_entry))){
		cerr << "File entry " << old_entry << " not found." << '\n';
		return;
	} else if(exist_entry(copied_entry)){
		cerr << "Cannot copy entry, " << copied_entry << " already exists" << '\n';
		return;
	} else {
		list<Entry>::iterator it = find_entry(old_entry);
		new_entry(copied_entry, it->get_size());
		cout << "Successfully copied " << old_entry
			<< " to " << copied_entry << endl;
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void delete_entry(string del_name){
	if(exist_entry(del_name)){
		list<Entry>::iterator it = find_entry(del_name);
		deallocate(it->get_start());
		directory.erase(it);
		reallocate(BLOCK_SIZE*ceil((float)directory.size()/BLOCK_ENTRIES), 0);
		directory.begin()->resize
			(BLOCK_SIZE*ceil((float)directory.size()/BLOCK_ENTRIES));
		cout << "Successfully deleted a file, " << del_name << endl;
	} else {
		cerr << "File entry " << del_name << " not found." << '\n';
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void new_entry(string new_name, size_t new_size){
	// Check if already exists
	if(exist_entry(new_name)){
		cerr << "Cannot create new entry, " << new_name
		 	<< " already exists."<< '\n';
		return;
	}
	Entry new_entry_item(new_name, new_size,
		allocate(new_size, find_empty(0)));
	directory.push_back(new_entry_item);
	reallocate(BLOCK_SIZE*ceil((float)directory.size()/BLOCK_ENTRIES), 0);
	directory.begin()->resize
		(BLOCK_SIZE*ceil((float)directory.size()/BLOCK_ENTRIES));
	cout << "Successfuly added a new file, " << new_name
		<< ", of size " << new_size << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void modify_entry(string mod_name, size_t new_size){
	if(exist_entry(mod_name)){
		list<Entry>::iterator it = find_entry(mod_name);
		Entry temp = *it;
		directory.erase(it);
		new_entry(temp.get_name(), new_size);
		deallocate(temp.get_start());
		cout << "Successfully modified a file, " << mod_name << endl;
	} else {
		cerr << "File entry " << mod_name << " not found." << '\n';
	}
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void rename_entry(string old_name, string new_name){
	if(!(exist_entry(old_name))){
		cerr << "File entry " << old_name << " not found." << '\n';
		return;
	} else if(exist_entry(new_name)){
		cerr << "Can't rename entry, " << new_name << " already exists" << '\n';
		return;
	} else {
		list<Entry>::iterator it = find_entry(old_name);
		Entry temp = *it;
		directory.erase(it);
		temp.rename(new_name);
		directory.push_back(temp);
		cout << "Successfully changed the file name " << old_name
			<< " to " << new_name << endl;
	}
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
		cerr << "No free blocks found" << '\n';
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
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
bool exist_entry(string search_entry){
	bool found = false;
	list<Entry>::iterator it = directory.begin();
	while(it != directory.end()){
		if(it++->get_name() == search_entry){
			found = true;
			break;
		}
	}
	return found;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
list<Entry>::iterator find_entry(string search_entry){
	list<Entry>::iterator it = directory.begin();
	while(it != directory.end()){
		if(it->get_name() == search_entry)
			break;
		it++;
	}
	return it;
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
void print_directory(){
	cout << "\nDirectory Listing" << endl;
	int total_size = 0, total_files = 0;
	list<Entry>::iterator it = directory.begin();
	while(it != directory.end()){
		print_entry(it);
		total_size += it++->get_size();
		total_files++;
	}
	cout << "Files:" << setw(3) << total_files
		<< "  Total Size:" << setw(7) << total_size << " bytes" << endl;
}
/*******************************************************************************
Function:		void print_fat()
Use:				Prints the FAT table with ENTRIES_PERLINE amount of entries on one
						line and ENTRIES_PRINT total amount of entries
Arguments:	none
Returns:		none
*******************************************************************************/
void print_fat(){
	cout << "\nContents of the File Allocation Table" << endl;
	int counter = 0, line_head = 0;
	cout << '#'  << setfill('0') << setw(3)<< line_head
		<< '-' << setw(3) << ENTRIES_PERLINE - 1;
	line_head += ENTRIES_PERLINE;
	while(counter < ENTRIES_PRINT){
		if(!(counter % ENTRIES_PERLINE) && !(counter == 0))
		{
			cout << '\n' << '#'  << setfill('0') << setw(3)<< line_head
				<< '-' << setw(3) << line_head + ENTRIES_PERLINE - 1;
			line_head += ENTRIES_PERLINE;
		}
		cout << setfill(' ') << setw(6) << right << fat[counter++];
	}
	cout << '\n';
}
/*******************************************************************************
Function:		void print_entry(list<Entry>::iterator entry)
Use:				Prints information including name, size, and clusters of an entry
Arguments:	entry - List iterator for entry to be printed
Returns:		none
*******************************************************************************/
void print_entry(list<Entry>::iterator entry){
	int current_block = entry->get_start();
	cout << "File name: " << setw(23) << left << entry->get_name()
		<< "File Size: " << setw(6) << entry->get_size()
		<< setw(20) << "\nCluster(s) in use:  ";
	if(current_block == -1){
		cout << setw(6) << right << "(none)";
	} else {
		int i = 0;
		while(current_block != -1){
			if((i % 12 == 0) && !(i == 0)){
				cout << endl << setw(26) << current_block;
			} else {
				cout << setw(6) << right << current_block;
			}
			i++;
			current_block = fat[current_block];
		}
	}
	cout << endl;
}
