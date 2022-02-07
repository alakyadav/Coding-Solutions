class Solution {
public:
    const char openParenthesis = '(';
    const char closeParenthesis = ')';
    const int unassigned = -2;
    const int invalid = -1;
    vector<int> mem;
    
    int endsAt(int idx, string &s) {
        /*
         * Return the index at which the valid substring beginning
         * at idx ends. If this is not the beginning of a valid
         * substring, return -1;
         *
         * This function assumes character at idx is an open parenthesis.
         */
        
        if (idx + 1 == s.length()) {
            return invalid;
        }
        
        if (s.at(idx + 1) == closeParenthesis) {
            return idx + 1;
        }
        else {
            /* 
             * Find where the next substring ends and check if the
             * current one ends right after that, or another starts.
             */
            
            if (mem.at(idx) != unassigned) {
                //printf("using\n");
                return mem.at(idx);
            }
            
            int insideIdx = idx + 1;
            while (true) {
                const int closeIdx = endsAt(insideIdx, s);
                if (closeIdx == invalid or closeIdx == s.length() - 1) {
                    mem.at(idx) = invalid;
                    return invalid;
                }
                
                if (s.at(closeIdx + 1) == closeParenthesis) {
                    mem.at(idx) = closeIdx + 1;
                    return closeIdx + 1;
                }
                else {
                    insideIdx = closeIdx + 1;
                }
            }
        }
    }
    
    int longestValidParentheses(string s) {
      
        int maxLen = 0;
        int currLen = 0;
        int idx = 0;
        mem = vector<int>(s.length(), unassigned);
        
        /* This traverses only through the outermost valid substrings */
        while (idx < s.length()) {
            if (s.at(idx) == openParenthesis) {
                const int end = endsAt(idx, s);
                if (end == invalid) {
                    /* invalid beginning */
                    currLen = 0;
                    idx++;
                }
                else {
                    /* valid block */
                    currLen += end - idx + 1;
                    //printf("adding %d - %d + 1\n", end, idx);
                    maxLen = max(currLen, maxLen);
                    idx = end + 1;
                }
            }
            else {
                /* Unmatched closing parenthesis */
                currLen = 0;
                idx++;
            }
        }
        
        return maxLen;
    }
};
