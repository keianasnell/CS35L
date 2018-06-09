/* Return negative, zero, positive if A < B, A == B, A > B, respectively.
 *    Assume the nanosecond components are in range, or close to it.  */

static inline int
 timespec_cmp (struct timespec a, struct timespec b)
 {
    if (a.tv_nsec == b.tv_nsec) return 0;
    else if(a.tv_nsec < b.tv_nsec) return -1;
    else return 1;
 }
