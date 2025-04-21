int dp[2][10001];
int pre[10001][17];
class Solution {
public:
 int And(int x, int y) {
 y++;
 assert(x <= y);
 if (x == y) {
  return (1<<19)-1;
 }
 int ret = 0;
 for (int i = 0; i < 17; i++) {
 if (pre[y][i] - pre[x][i] == y-x) {
 ret |= (1<<i);
 }
 }
 return ret;
 }
 int minimumValueSum(vector<int>& a, vector<int>& av) {
 int n = a.size();
 int m = av.size();
 memset(pre[0], 0, sizeof(pre[0]));
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < 17; j++) {
 pre[i+1][j] = pre[i][j];
 if (a[i] & (1<<j)) {
 pre[i+1][j]++;
 }
 }
 }
  memset(dp[0], 1<<5, sizeof(int)*(n+1));
 dp[0][0] = 0;
 for (int i = 0; i < m; i++) {
 int b = (i & 1);
 memset(dp[1-b], 1<<5, sizeof(int)*(n+1));
 for (int j = 0; j < n; j++) {
 if ((av[i] & a[j]) != av[i]) continue;
 if (dp[b][j] > 1e7) continue;
 int winl = j;  int c = a[j];
 for (; winl < n; winl++) {
 c &= a[winl];
 if (av[i] == c) break;
 if (av[i] & ~c) break;
 }
 if (c != av[i]) {
 j = winl;
 continue;
 }
 assert(winl < n);
 int winr = winl+1;  for (; winr < n; winr++) {
 c &= a[winr];
 if (c != av[i]) break;
 }
 int mi = dp[b][j];
 assert(winr <= n);
 for (int j2 = j; j2 < winr; j2++) {
 c = And(j2, winl);
 while (c != av[i] && winl < winr) {
 dp[1-b][winl+1] = mi + a[winl];
 winl++;
 if (winl < n) c &= a[winl];
 }
 if (winl == winr) break;
 mi = min(mi, dp[b][j2]);
 }
 while (winl < winr) {
 dp[1-b][winl+1] = mi + a[winl];
 winl++;
 }
 j = winr;
 }
 }
 int ret = dp[m&1][n];
 if (ret > 1e7) return -1;
 return ret;
 }
};
