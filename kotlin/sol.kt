import java.util.*
 
fun main() = with(Scanner(System.`in`)) {
    val tt = nextInt()
    repeat(tt) {
        val n = nextInt()
        val s = next()
        val a = next()
        val inf = 2 * n + 1
        val dp = IntArray(8) { inf }
        dp[0] = 0
        repeat(n) { i ->
            val ndp = IntArray(8) { inf }
            if (i >= 3 && a[i-3] == '1') {
                val need = (if (s[i] == '(') 1 else 0)
                ndp[3] = minOf(ndp[3], dp[1] + need)
                ndp[5] = minOf(ndp[5], dp[2] + need)
            } else {
                for (x in 0..7) {
                    if (dp[x] < inf) {
                        val y = x * 2 % 8
                        val z = y + 1
                        if (s[i] == '(') {
                            ndp[y] = minOf(ndp[y], dp[x])
                            ndp[z] = minOf(ndp[z], dp[x] + 1)
                        } else {
                            ndp[y] = minOf(ndp[y], dp[x] + 1)
                            ndp[z] = minOf(ndp[z], dp[x])
                        }
                    }
                }
            }
 
            for (x in 0..7) dp[x] = ndp[x]
        }
        val ans = dp.minOrNull()!!
        if (ans == inf) {
            println(-1)
        } else {
            println(ans)
        }
    }
}