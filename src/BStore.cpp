//
// BStore.cpp
// BlindStorage
//

#include "BStore.h"

BStore::BStore(Communicator &communicator){
	this->communicator = communicator;
}
BStore::BStore(Communicator &communicator, string directoryPath): D(TOTAL_BLOCKS){
	this->communicator = communicator;
	readFilesFromDirectory(directoryPath);
	cout << "Processing files" << endl;
	for(int i = 0; i < filesList.size(); i++){
		//cout << __PRETTY_FUNCTION__ << "Processing file " << filesList[i] << endl;
		cout << ((double)i*100)/(double)filesList.size() << "\% i.e. " << i << "/" << filesList.size() << " processed";
		cout.flush();
		cout << "\r";
		int32_t fileSize = readFileSize(filesList[i]);
		uint32_t numBlocks =(uint32_t) ceil((double)fileSize/MAX_BLOCK_DATA_SIZE) * BLOW_UP;
		PRSubset prSubset(numBlocks);
	T.addFile(filesList[i], prSubset);
		D.addFile(filesList[i], prSubset);	
	}
	cout << endl;
	T.finalize(D);
	cout << "Writing T to disk" << endl;
	T.writeToDisk();
	
	D.finalize();
	cout << "Writing D to disk" << endl;
	D.writeToDisk();



}

BStore::~BStore(){
}

void BStore::upload(){
}

unsigned char* BStore::read(string filename){
	OnlineSession session(communicator);
	return session.get(filename);
}

void BStore::write(string filename, unsigned char* filedata, uint32_t filesize){
	OnlineSession session(communicator);
	PRSubset* prSubset = new PRSubset(filesize);
	unsigned char* readData = session.get(filename, prSubset);
	session.update(filedata, filesize, filename);
	delete prSubset;
}

unsigned char* BStore::update(string filename, unsigned char* updatedFiledata, uint32_t filesize){
}

void BStore::del(string filename){
}

void BStore::rename(string filename){
}

void BStore::readFilesFromDirectory(string directory){
	/* Code for this function is taken from: http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c*/
 	DIR *dir;
     class dirent *ent;
     class stat st;
 	
     dir = opendir(directory.c_str());
 
     while ((ent = readdir(dir)) != NULL) {
     	const string file_name = ent->d_name;
     	string full_file_name = directory + '/' + file_name;
 		
     	if (file_name[0] == '.')
     		continue;
 
     	if (stat(full_file_name.c_str(), &st) == -1)
     		continue;
 		
 		
 		const bool is_directory = (st.st_mode & S_IFDIR) != 0;
 	
 		if(!is_directory){
 			filesList.push_back(full_file_name);
 			cout << "Processing file " << full_file_name << endl;
 		}
 			
     	if (is_directory){
 			full_file_name = directory + file_name;
 			readFilesFromDirectory(full_file_name);
		}
    }
    closedir(dir);
}

//void BStore::readFilesFromDirectory(string path){
//	for(boost::filesystem::recursive_directory_iterator end, dir(path); dir!=end; ++dir){
//		string fileName = dir->path().string();
//		cout << "Processing " << fileName << endl;
//		filesList.push_back(fileName);
//	}
//}


ifstream::pos_type BStore::readFileSize(string filename){
	ifstream file(filename.c_str(), std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
	return file.tellg();
}
