class SnapshotArray {
private:
    unordered_map<int, map<int, int>> sArray;
    int snap_id;
public:
    SnapshotArray(int length) {
        snap_id = 0;
        map<int, int> init_value ={{snap_id,0}};
        for(int i = 0; i < length; i++) {
            sArray[i] = init_value;
        }
    }
    
    void set(int index, int val) {
        sArray[index][snap_id] = val;
    }
    
    int snap() {
        return snap_id++;
    }
    
    int get(int index, int snap_id) {
        auto it = sArray[index].upper_bound(snap_id);
        return std::prev(it)->second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */