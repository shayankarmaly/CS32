
void listAll(const File* f, string path)  // two-parameter overload
{
    
    path += '/';
    if(dynamic_cast <const PlainFile*>(f) != nullptr)
        cout << path << f -> name() << endl;
    
    else
    {
        path += f -> name();
        cout << path << endl;
        
        const vector<File*> files = *(f -> files());
        
        for(int j = 0; j < files.size(); j++)
        {
            listAll(files[j], path);
        }
    }
}
   // You will write this code.

