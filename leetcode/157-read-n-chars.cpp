// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    bool eof;
    char readbuf[4];
    int left;
    int pos;
public:
    Solution ():eof(false), left(0), pos(0) { memset(readbuf, 0, 4);}
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int sofar = 0;
        int o;
        while (n && (left || !eof)) {
            if (!left) {
                o = read4(readbuf);
                if (o < 4) {
                    eof = true;
                }
                left = o;
                pos = 0;
            }
            if (n > left) {
                memcpy(buf+sofar, readbuf + pos, left);
                sofar += left;
                n -= left;
                left = 0;
            } else {
                memcpy(buf+sofar, readbuf + pos, n);
                sofar += n;
                left -= n;
                pos += n;
                n = 0;
            }
        }
        return sofar;
    }
};
