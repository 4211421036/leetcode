object Solution {
    def calculateMinimumHP(dungeon: Array[Array[Int]]): Int = {
        val m = dungeon.length
        val n = dungeon(0).length
        val dp = Array.ofDim[Int](m, n)
        
        // Initialize the bottom-right cell
        dp(m-1)(n-1) = math.max(1, 1 - dungeon(m-1)(n-1))
        
        // Fill last row from right to left
        var j = n - 2
        while (j >= 0) {
            dp(m-1)(j) = math.max(1, dp(m-1)(j+1) - dungeon(m-1)(j))
            j -= 1
        }
        
        // Fill last column from bottom to top
        var i = m - 2
        while (i >= 0) {
            dp(i)(n-1) = math.max(1, dp(i+1)(n-1) - dungeon(i)(n-1))
            i -= 1
        }
        
        // Fill the rest of the table from bottom-right to top-left
        i = m - 2
        while (i >= 0) {
            j = n - 2
            while (j >= 0) {
                val minHealthExit = math.min(dp(i+1)(j), dp(i)(j+1))
                dp(i)(j) = math.max(1, minHealthExit - dungeon(i)(j))
                j -= 1
            }
            i -= 1
        }
        
        dp(0)(0)
    }
}
