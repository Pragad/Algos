/*
 * Q: Given a string and a list of characters, find the Smallest Substring
 * that contain all the characters
 *
 * LEARNINGS:
 */

// n = 10
// g[] = 40, 50, 50, 100, 160, 200, 325, 500, 1075, 1500 = 4000
// ps = 40, 90, 140, 240, 400, 600, 725, 1225, 2500, 4000
// b = 2000
// c ?
// Say c = 400; If anyone asks more than 400, you would just 400.
// ans: 358.33

/*
int min_dif = 0;
cur_ans = 240 + (n - i - 1)*g[i]
  For 200: 600 + 200 * 4 = 1400
// 2000 - () /     
if (cur_ans <= b && b - cur_ans < min_diff) {
     res = cur_ans;
}
*/
