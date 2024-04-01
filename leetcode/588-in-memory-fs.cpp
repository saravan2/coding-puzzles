struct Inode {
    public:
    std::map<std::string, Inode*> dir;
    std::string content;
};

class FileSystem {
private:
    Inode inode;
public:
    FileSystem() {
        
    }
    
    vector<string> ls(string path) {
        auto pathInode = getOrCreateInode(path);
        // File
        if (!pathInode->content.empty()) {
            return {path.substr(path.find_last_of('/') + 1)};
        }
        // Directory
        std::vector<string> contents;
        for (auto const& [path, inode] : pathInode->dir) {
            contents.push_back(path);
        }
        return std::move(contents);
    }
    
    void mkdir(string path) {
        getOrCreateInode(path);
    }
    
    void addContentToFile(string filePath, string content) {
        auto fileInode = getOrCreateInode(filePath);
        fileInode->content += content;
    }
    
    string readContentFromFile(string filePath) {
        auto fileInode = getOrCreateInode(filePath);
        return fileInode->content;
    }

    Inode* getOrCreateInode(std::string path) {
        std::stringstream ss(path);
        std::string currentPath = "";
        Inode* currInode = &inode;
        while (getline(ss, currentPath, '/')) {
            if ((currInode->dir).find(currentPath) == (currInode->dir).end()) {
                currInode->dir[currentPath] = new Inode;
            }
            currInode = currInode->dir[currentPath];
        }
        return currInode;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */