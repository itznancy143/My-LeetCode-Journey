
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival,vector<int>& load) {

        set<int> available;

        // {finishTime, serverID}
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> busy;

        vector<int> count(k, 0);

        // Initially, all servers are available
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            // Release servers that have completed their requests
            while (!busy.empty() &&
                   busy.top().first <= arrival[i]) {

                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // All servers are busy
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int target = i % k;

            // Find the next available server
            auto it = available.lower_bound(target);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request to the server
            available.erase(it);

            count[server]++;

            // Calculate request completion time
            long long finishTime =
                (long long)arrival[i] + load[i];

            busy.push({finishTime, server});
        }

        // Find maximum number of handled requests
        int maxRequests = *max_element(count.begin(),
                                       count.end());

        vector<int> ans;

        // Collect all busiest servers
        for (int i = 0; i < k; i++) {
            if (count[i] == maxRequests) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};