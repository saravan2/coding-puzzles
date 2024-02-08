/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void openDoor();
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 *     void moveLeft();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {
        int count = 0;
        for (int i = 0; i < k; i++) {
            street->closeDoor();
            street->moveLeft();
        }
        street->openDoor();
        for (street->moveLeft(), count = 1; !street->isDoorOpen(); street->moveLeft(), count++)
        ;
        return count;
    }
};