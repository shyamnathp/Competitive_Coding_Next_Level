// C++ program to find minimum cost k partitions 
// of array. 
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <iterator>
#include <cmath>
#include <vector>
#include <set>
#include <numeric>
#include <iomanip>

using namespace std;
constexpr static int INF = numeric_limits<int>::max();

template <typename vec>
void print_2d_vec(const vec &T) {
    for (auto &t : T) {
        for (auto &a : t){
            cout << a << " ";
        }
        cout << endl;
    }
    cout << endl;
}


template <typename vec>
void print_vec(const vec &T) {
    for (auto &t : T) {
        cout << t << " ";
    }
    cout << endl;
}


int minSum(vector<int> &a, int begin, int end){
    // Median of the array

    //cout << "begin " << begin << endl;
    //cout << "end " << end << endl;
    //print_vec(a);

    if (end == begin){
        return 0;
    }

    //vector<int> arr;

    //std::vector<int> arr(&a[begin], &a[end]+1);

    //print_vec(arr);

    int x = a[(end-begin)/2 + begin];

    int sum = 0;

    // Calculate the minimized sum
    for (int i = begin; i < end + 1; ++i) {
        sum += abs(a[i] - x);
    }
    // Return the required sum
    return sum;
}

vector<int> returnAllDistances(vector<int> &a){
    // Median of the array

    vector<int> distances (a.size());
    int j = 0;
    for (int i = 0; i < a.size(); ++i) {
        distances[i] = a[i] - a[j];
        j = i;
    }
    print_vec(distances);
    return distances;
}

int sumOfMinAbsDifferences(vector<int> &nums, vector<int> &all_dists, int begin, int end){


    if (end == begin){
        //cout << 0 << endl;
        return 0;
    }
    cout << "begin " << begin << endl;
    cout << "end " << end << endl;

    //print_vec(a);

    int sum = 0;

    sum += abs(nums[begin] - nums[begin + 1]);

    if (begin + 1 != end){
        sum += abs(nums[end] - nums[end - 1]);
    }

    for (int i = begin + 1; i < end - 1; i++) {
        //cout << nums[i] << " ";
        sum += min(abs(nums[i] - nums[i - 1]), abs(nums[i] - nums[i + 1]));
    }
    //cout << endl;

    cout << "sum " << sum << endl;
    print_vec(nums);
    return sum;
}

int minCost(vector<int> &a, int n, int k) {
    // Create a dp[][] table and initialize 
    // all values as infinite. dp[i][j] is 
    // going to store optimal partition cost 
    // for arr[0..i-1] and j partitions 
    vector<vector<int>> dp (n + 1, (vector<int> (k + 1, INF)));

    // Fill dp[][] in bottom up manner 
    dp[0][0] = 0;

    // Current ending position (After i-th
    // iteration result for a[0..i-1] is computed.
    for (int i = 1; i < n + 1; ++i) {
        // j is number of partitions
        for (int j = 1; j < k + 1; ++j) {

            // Picking previous partition for 
            // current i. 
            for (int m = i - 1; m >= 0; --m) {
                dp[i][j] = (int) min((long) dp[i][j], ((long)dp[m][j-1] + minSum(a, m, i - 1)));
            }
        }

    }

    //print_2d_vec(dp);
    return dp[n][k];
}


int random(int min, int max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}


int main() {

    int i1, n;
    cin >> i1 >> n;

    vector<int> n_values(n);
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        n_values[i] = val;
    }

    //n random value generator here, u can maybe uncomment the above to input the n values
/*

    for (int i = 0; i < n; ++i)
    {
        n_values[i] = random(1, 1000);
    }
*/

    //sort the values inititally
    std::sort(n_values.begin(), n_values.end());


    //vector<int> all_dists = returnAllDistances(a);
    cout << 25*n - minCost(n_values, n, i1) << endl;
    return 0;
}