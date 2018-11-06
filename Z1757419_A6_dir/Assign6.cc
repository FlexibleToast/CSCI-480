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
	ifstream file;
	file.open("data60.txt");
	if(file.fail())
	{
		cerr << "Failed to open file data6.txt" << endl;
		exit(-1);
	}
	string line;
	while(getline(file, line))
	{
		readline(line);
	}
	initialize_avail();
	print_avail();
	print_inuse();
	file.close();
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
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
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
	}
	return;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void load_best(vector<string> &line){
	cout << "Place holder" << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void load_first(vector<string> &line){
	vector<string>::iterator it = line.begin();
	while(it != line.end())
	{
		cout << *it << endl;
		it++;
	}
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
			<< ", size in MB: " << setprecision(2) << fixed
			<< (float)it->get_size()/MB << endl;
		it++;
	}
	cout << "Total size of available memory space: "
		<< setprecision(2) << fixed << (float)total/MB << "MB" << endl;
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
			<< ", size in MB: " << setprecision(2) << fixed
			<< (float)it->get_size()/MB << endl;
		it++;
	}
	cout << "Total memory in use: "
		<< setprecision(2) << fixed << (float)total/MB << "MB" << endl;
}
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void tokenize(string line, vector<string> &tokens){
	char* token = strtok((char*)line.c_str(), " ");
	while(token)
	{
		tokens.push_back((string)token);
		token = strtok(NULL, " ");
	}
	return;
}
