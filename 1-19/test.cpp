// #include <iostream>
// #include <cmath>
// #include <cstring>
// using namespace std;

// const int N = 1001;
// int dp[N][N];
// int n, V;
// int v[N], w[N];

// int main()
// {
//     cin >> n >> V;
//     for (int i = 0; i <= n; ++i)
//     {
//         cin >> v[i] >> w[i];
//     }

//     // 问题1
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = 0; j <= V; ++j)
//         {
//             dp[i][j] = dp[i - 1][j];
//             if (j >= v[i - 1])
//                 dp[i][j] = max(dp[i][j], dp[i][j - v[i - 1]] + w[i - 1]);
//         }
//     }

//     cout << dp[n][V] << endl;

//     // 问题2
//     memset(dp, 0, sizeof dp);
//     for (int i = 1; i <= V; ++i)
//         dp[0][i] = -1;
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = 0; j <= V; ++j)
//         {
//             dp[i][j] = dp[i - 1][j];
//             if (j >= v[i - 1] && (dp[i][j - v[i - 1]] != -1))
//                 dp[i][j] = max(dp[i][j], dp[i][j - v[i - 1]] + w[i - 1]);
//         }
//     }
//     cout << (dp[n][V] == -1 ? 0 : dp[n][V]) << endl;
//     return 0;
// }

// 空间优化，滚动数组
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1001;
int dp[N];
int n, V;
int v[N], w[N];

int main()
{
    cin >> n >> V;
    for (int i = 0; i <= n; ++i)
    {
        cin >> v[i] >> w[i];
    }

    // 问题1
    for (int i = 1; i <= n; ++i)
    {
        for (int j = v[i - 1]; j <= V; ++j)
        {
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
        }
    }

    cout << dp[V] << endl;

    // 问题2
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= V; ++i)
        dp[i] = -0x3F3F3F3F;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = v[i - 1]; j <= V; ++j)
        {
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
        }
    }
    cout << (dp[V] < 0 ? 0 : dp[V]) << endl;
    return 0;
}