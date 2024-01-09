private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

fun main(args: Array<String>) {
    var tt = readInt()
    for (qq in 0 until tt) {
        var s = readLn()
        var ans = 0
        var v = 0
        for (c in s) {
            if (c == 'w') {
                ans += 1
                v = 0;
            } else {
            	++v;
            	if (v == 2) {
            		++ans;
            		v = 0;
            	}
            }
        }
        println(ans)
    }
}				