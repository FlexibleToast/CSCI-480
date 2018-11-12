/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 6
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		11/14/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Simulates memory management functions such as loading a program,
	 							allocating, terminating a program, deallocating space. The sim
								can take a variable F or B for either first-fit algorithm or
								best-fit algorithm.
*******************************************************************************/

#include "Memblock.h"
#include "Assign6.h"

int main(int argc, char *args[]){
	if(argc == 2){
		if(strcmp(args[1], "B") == 0){
			best_fit = true;
		} else if(strcmp(args[1], "F") == 0){
			best_fit = false;
		} else {
			cerr << "Must use argument B for best fit or F for first fit" << endl;
			exit(-1);
		}
	} else {
		cerr << "Must provide 1 argument, B for best fit or F for first fit" <<endl;
		exit(-1);
	}
	size_t sim_counter = 0;
	initialize_avail();
	ifstream file;
	file.open("data6.txt");
	if(file.fail())
	{
		cerr << "Failed to open file data6.txt" << endl;
		exit(-1);
	}
	string line;
	while(getline(file, line))
	{
		if(sim_counter % HOW_OFTEN == 0){
			cout << "********************************************************" << endl
				<< "Current simulation cycle: " << sim_counter
				<< ", current memory states:" << endl;
				print_avail();
				print_inuse();
		}
		readline(line);
		sim_counter++;
	}
	cout << "********************************************************" << endl
		<< "Simulation completed with " << sim_counter << " cycles." << endl
		<< "Current memory states:" << endl;
	print_avail();
	print_inuse();
	file.close();
  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:		void initialize_avail()
Use:				Initializes the available space in blocks of 1MB, 2*2MB, and 2*4MB
Arguments:	none
Returns:		none
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
/*******************************************************************************
Function:		void readline(string line)
Use:				Reads contents of line and determines what steps of simulation to
						perform
Arguments:	line - String that is used to tell simulation what steps to perform
Returns:		none
*******************************************************************************/
void readline(string line){
	vector<string> tokens;
	tokenize(line, tokens);
	if(tokens[0] == "L"){
		if(best_fit){
			load_best(tokens);
		} else {
			load_first(tokens);
		}
	} else if(tokens[0] == "A"){
		if(best_fit){
			allocate_best(tokens);
		} else {
			allocate_first(tokens);
		}
	} else if(tokens[0] == "D"){
		deallocate(tokens[1], tokens[2]);
	} else if(tokens[0] == "T"){
		terminate(tokens[1]);
	}
	return;
}
/*******************************************************************************
Function:		void load_best(vector<string> &tokens)
Use:				Loads program to memory using best-fit algorithm
Arguments:	&tokens - A vector containing a tokenized string
Returns:		none
*******************************************************************************/
void load_best(vector<string> &tokens){
	Memblock load(0, stoi(tokens[2]), tokens[1], tokens[3]);
	list<Memblock>::iterator it, best;
	it = avail.begin();
	size_t smallest = 4 * MB;
	bool found = false;
	while(it != avail.end()){
		if(it->get_size() > load.get_size()
			&& it->get_size() <= smallest)
		{
			found = true;
			smallest = it->get_size();
			best = it;
		}
		it++;
	}
	if(found)
	{
		load.set_start(best->get_start());
		best->set_start(best->get_start() + load.get_size());
		best->set_size(best->get_size() - load.get_size());
		if(best->get_size() == 0)
			avail.erase(best);
		inuse.push_front(load);
	} else {
		cerr << "No large enough free block found for Block" << endl
		 	<< "PID: "<< load.get_process_id() << endl
			<< "Block ID: " << load.get_block_id() << endl
			<< "Size: " << setprecision(2) << fixed
			<< (float)load.get_size()/MB << "MB" << endl;
		exit(-1);
	}
}
/*******************************************************************************
Function:		void load_first(vector<string> &line)
Use:				Loads program to memory using first-fit algorithm
Arguments:	&tokens - A vector containing a tokenized string
Returns:		none
*******************************************************************************/
void load_first(vector<string> &line){
	Memblock load(0, stoi(line[2]), line[1], line[3]);
	list<Memblock>::iterator it = avail.begin();
	while(it->get_size() < load.get_size()){
		it++;
	}
	if(it->get_size() > load.get_size())
	{
		load.set_start(it->get_start());
		it->set_start(it->get_start() + load.get_size());
		it->set_size(it->get_size() - load.get_size());
		if(it->get_size() == 0)
			avail.erase(it);
		inuse.push_front(load);
	} else {
		cerr << "No large enough free block found for Block" << endl
		 	<< "PID: "<< load.get_process_id() << endl
			<< "Block ID: " << load.get_block_id() << endl
			<< "Size: " << setprecision(2) << fixed
			<< (float)load.get_size()/MB << "MB" << endl;
		exit(-1);
	}
}
/*******************************************************************************
Function:		void allocate_best(vector<string> &tokens)
Use:				Calls load_best to allocate memory for a block using best-fit
Arguments:	tokens - A vector containing a tokenized sting
Returns:		none
*******************************************************************************/
void allocate_best(vector<string> &tokens){
	load_best(tokens);
}
/*******************************************************************************
Function:		void allocate_first(vector<string> &tokens)
Use:				Calls load_first to allocate memory for a block using first-fit
Arguments:	tokens - A vector containing a tokenized sting
Returns:		none
*******************************************************************************/
void allocate_first(vector<string> &tokens){
	load_first(tokens);
}
/*******************************************************************************
Function:		void deallocate(string deproc, string deblock)
Use:				Deallocates a block of memory
Arguments:	deproc - The process id of the block to be deallocated
						deblock - The block id of the blcok to be deallocated
Returns:		none
*******************************************************************************/
void deallocate(string deproc, string deblock){
	list<Memblock>::iterator deuse = inuse.begin();
	list<Memblock>::iterator make_avail = avail.begin();
	bool found = false;
	while(deuse != inuse.end())
	{
		if(deuse->get_process_id() == deproc && deuse->get_block_id() == deblock)
		{
			found = true;
			break;
		}
		deuse++;
	}
	if(found){
		while(make_avail->get_start() < deuse->get_start())
			make_avail++;
		Memblock new_available(deuse->get_start(), deuse->get_size());
		avail.insert(make_avail, new_available);
		inuse.erase(deuse);
		defrag();
	} else {
		cerr << "* Cannot deallocate, block not found *" << endl
		 	<< "PID: "<< deproc << endl
			<< "Block ID: " << deblock << endl;
	}
}
/*******************************************************************************
Function:		void terminate(string proc_id)
Use:				Deallocates all blocks associate with a process id
Arguments:	proc_id - The process id of the process to be terminate
Returns:
*******************************************************************************/
void terminate(string proc_id){
	bool found;
	list<Memblock>::iterator it;
	do {
		it = inuse.begin();
		found = false;
		while(it != inuse.end()){
			if(it->get_process_id() == proc_id){
				deallocate(it->get_process_id(), it->get_block_id());
				found = true;
				break;
			}
			it++;
		}
	} while(found);
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void print_avail(){
	if(avail.empty())
	{
		cout << "There is no more free memory." << endl;
		return;
	}
	list<Memblock>::iterator it = avail.begin();
	size_t total = 0;
	cout << "Available free memory" << endl;
	while(it != avail.end()){
		total += it->get_size();
		cout << "Starting address: " << it->get_start()
			<< ", size: " << it->get_size()
			<< " B, size in MB: " << setprecision(2) << fixed
			<< (float)it->get_size()/MB << " MB" << endl;
		it++;
	}
	cout << "Total size of available memory space: "
		<< setprecision(2) << fixed << (float)total/MB << " MB" << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void print_inuse(){
	if(inuse.empty())
	{
		cout << "No memory in use." << endl;
		return;
	}
	list<Memblock>::iterator it = inuse.begin();
	size_t total = 0;
	cout << "Blocks of memory in use" << endl;
	while(it != inuse.end()){
		total += it->get_size();
		cout << "Process ID: " << it->get_process_id()
			<< ", Block ID: " << it->get_block_id() << endl
			<< "Starting address: " << it->get_start()
			<< ", size: " << it->get_size()
			<< " B, size in MB: " << setprecision(2) << fixed
			<< (float)it->get_size()/MB << " MB" << endl;
		it++;
	}
	cout << "Total memory in use: "
		<< setprecision(2) << fixed << (float)total/MB << " MB" << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void tokenize(string line, vector<string> &tokens){
	//line.erase(line.size() - 1); //Remove '\r' from data6.txt
	if(line[line.size() - 1] == '\r')
		line.erase(line.end()-1,line.end());
	char* token = strtok((char*)line.c_str(), " ");
	while(token)
	{
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
void defrag(){
	list<Memblock>::iterator prev_it, it;
	prev_it = it = avail.begin();
	it++;
	while(prev_it != avail.end())
	{
		if(prev_it->get_end() == it->get_start()
			&& prev_it->get_size() + it->get_size() <= 4 * MB)
		{
			prev_it->set_size(prev_it->get_size() + it->get_size());
			avail.erase(it++);
			continue;
		}
		prev_it++;
		it++;
	}
}
