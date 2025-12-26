class Solution {
public:
    int bestClosingTime(string customers) {
        int penalty = 0;
        
        // Initial penalty: all 'Y' if shop closes at hour 0
        for (char c : customers) {
            if (c == 'Y') penalty++;
        }

        int minPenalty = penalty;
        int bestHour = 0;

        // Try closing at each hour
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i] == 'Y') {
                penalty--;      // one less missed customer
            } else {
                penalty++;      // one extra idle hour
            }

            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = i + 1;
            }
        }

        return bestHour;
    }
};
