#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip> // For formatting seconds output

using namespace std;
using namespace chrono;

// Function to merge two halves
void merge(vector<int>& cards, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = cards[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = cards[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j])
            cards[k++] = leftArr[i++];
        else
            cards[k++] = rightArr[j++];
    }

    while (i < n1) cards[k++] = leftArr[i++];
    while (j < n2) cards[k++] = rightArr[j++];
}

// Merge Sort function
void mergeSort(vector<int>& cards, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(cards, left, mid);
        mergeSort(cards, mid + 1, right);
        merge(cards, left, mid, right);
    }
}

// Function to display cards
void displayCards(const vector<int>& cards) {
    for (int card : cards) {
        cout << card << " ";
    }
    cout << endl;
}

// Main function
int main() {
    srand(time(0));
    vector<int> cards(5);

    // Generate random card values (1-13)
    cout << "Your random cards: ";
    for (int i = 0; i < 5; i++) {
        cards[i] = rand() % 13 + 1;
        cout << cards[i] << " ";
    }
    cout << endl;

    // Player input for sorting guess
    vector<int> playerGuess(5);
    
    cout << "\n🕒 Start sorting! Type the numbers in sorted order as fast as you can: \n";
    auto playerStart = high_resolution_clock::now(); // Start player timer
    for (int i = 0; i < 5; i++) {
        cin >> playerGuess[i];
    }
    auto playerEnd = high_resolution_clock::now(); // End player timer

    // Calculate player time in seconds
    double playerTime = duration_cast<duration<double>>(playerEnd - playerStart).count();

    // Start Merge Sort timer
    auto algoStart = high_resolution_clock::now();
    mergeSort(cards, 0, 4);
    auto algoEnd = high_resolution_clock::now();

    // Calculate Merge Sort time in microseconds (µs)
    auto algoTime = duration_cast<microseconds>(algoEnd - algoStart).count();

    // Display sorted cards
    cout << "\n✅ Merge Sort Result: ";
    displayCards(cards);

    // Show times
    cout << fixed << setprecision(4); // Format output for seconds
    cout << "\n🕒 Merge Sort Time: " << algoTime << " µs";
    cout << "\n🕒 Your Time: " << playerTime << " seconds";

    // Show Merge Sort Time Complexity
    cout << "\n⏳ Merge Sort Time Complexity: O(n log n)\n";

    // Determine winner
    if (playerGuess == cards) {
        if (playerTime < algoTime / 1e6) { // Convert microseconds to seconds
            cout << "🎉 Congratulations! You sorted faster than Merge Sort! 🎉" << endl;
        } else {
            cout << "🤖 Merge Sort was faster, but you got the correct order! Keep practicing!" << endl;
        }
    } else {
        cout << "❌ Oops! Your sorting was incorrect. Try again!" << endl;
    }

    return 0;
}
