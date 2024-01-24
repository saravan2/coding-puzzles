#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

class Photo {
public:
    bool favorite; 
    Photo(bool isFavorite) : favorite(isFavorite) {}
};

class Album {
private:
    //std::vector<Photo> photos;
    const std::vector<Photo> &photos;
    std::vector<size_t> favoritePhotoIndices;
    std::vector<size_t> nonFavoritePhotoIndices; 
    size_t currentNonFavoriteIndex; 
    size_t currentFavoriteIndex;
    //bool favoritePhotosRemaining;
    //std::vector<Photo>::const_iterator favoritePhotoIterator;

public:
    std::vector<Photo>::const_iterator sentinelIterator;
    //Album(const std::vector<Photo>& photos) : photos(photos), favoritePhotosRemaining(true) {
    Album(const std::vector<Photo>& photos) : photos(photos) {
        for (size_t i = 0; i < photos.size(); ++i) {
            if (!photos[i].favorite) {
                nonFavoritePhotoIndices.push_back(i);
            } else {
                favoritePhotoIndices.push_back(i);
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(favoritePhotoIndices.begin(), favoritePhotoIndices.end(), g);
        std::shuffle(nonFavoritePhotoIndices.begin(), nonFavoritePhotoIndices.end(), g);
        currentFavoriteIndex = 0;
        currentNonFavoriteIndex = 0; 
        //favoritePhotoIterator = photos.begin();
        sentinelIterator = photos.end();
    }

    // Function to get the next photo iterator, favoring favorites
    //std::vector<Photo>::const_iterator getNextPhoto() {
        //if (favoritePhotosRemaining) {
            // Look for the next favorite photo starting from the last favorite photo
            //while(favoritePhotoIterator != sentinelIterator) {
                //if (favoritePhotoIterator->favorite) {
                    //favoritePhotoIterator++;
                    //return favoritePhotoIterator - 1;
                //} else {
                    //favoritePhotoIterator++;
                //}
            //}
            //favoritePhotosRemaining = false; 
            //favoritePhotoIterator = photos.begin();
        //}
        //if (currentNonFavoriteIndex < nonFavoritePhotoIndices.size()) {
            //size_t index = nonFavoritePhotoIndices[currentNonFavoriteIndex];
            //++currentNonFavoriteIndex;
            //return photos.begin() + index;
        //}
        //return sentinelIterator;
    //}
    
    std::vector<Photo>::const_iterator getNextPhoto() {
        if (currentFavoriteIndex < favoritePhotoIndices.size()) {
            size_t index = favoritePhotoIndices[currentFavoriteIndex];
            ++currentFavoriteIndex;
            return photos.begin() + index;
        }
        if (currentNonFavoriteIndex < nonFavoritePhotoIndices.size()) {
            size_t index = nonFavoritePhotoIndices[currentNonFavoriteIndex];
            ++currentNonFavoriteIndex;
            return photos.begin() + index;
        }
        return sentinelIterator;
    }
};

int main() {
    std::vector<Photo> photos;
    photos.push_back(Photo(true)); // Example: favorite photo
    photos.push_back(Photo(false)); // Example: non-favorite photo
    photos.push_back(Photo(true)); // Example: favorite photo
    photos.push_back(Photo(false)); // Example: non-favorite photo

    Album myAlbum(photos);
  
    std::vector<Photo>::const_iterator photoIterator;

    //while (true) {
        //photoIterator = myAlbum.getNextPhoto();
        //if (photoIterator == myAlbum.sentinelIterator) {
        //    break;
        //} else {
            //if (photoIterator->favorite) {
                //std::cout << "Favorite photo" << std::endl;
            //} else {
                //std::cout << "Non favorite photo" << std::endl;
            //}
        //}
    //}
    
    while((photoIterator = myAlbum.getNextPhoto()) != myAlbum.sentinelIterator) {
        if (photoIterator->favorite) {
            std::cout << "Favorite photo" << std::endl;
        } else {
            std::cout << "Non favorite photo" << std::endl;
        }
    }
    return 0;
}
