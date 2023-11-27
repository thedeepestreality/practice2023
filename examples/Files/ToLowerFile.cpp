#include <iostream>
#include <fstream>

int getFileSize(const char* path){
    std::ifstream in(path, std::ios_base::binary);
    if (!in)
        return -1;
    // move read-pointer to the end of the file
    in.seekg(0, std::ios_base::end);
    // get current get-pointer position
    // relative to the beginning of the file
    int file_size = in.tellg();
    // // prepare file to valid read
    // in.seekg(0, std::ios_base::beg);
    // in.clear();
    return file_size;
}

int main(int argc, const char* argv[])
{
    if (argc < 3)
        std::cout << "Wrong arguments!\n";

    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cout << "Failed to open input file\n";
        return 1;
    }

    std::ofstream out(argv[2]);
    if (!out)
    {
        std::cout << "Failed to open output file\n";
        return 2;
    }
    
    // read file till the end
    while(in.peek() != EOF){
        char c = in.get();
        if (c >= 'A' && c <= 'Z')
            c += 32;
        out.put(c);
    }

    // // example on how to get file size
    // // and read full file to memory
    // int file_size = getFileSize("in.txt");
    
    // char* file_val = new char[file_size];
    // in.read(file_val, file_size);
    // delete[] file_val;

    return 0;
}