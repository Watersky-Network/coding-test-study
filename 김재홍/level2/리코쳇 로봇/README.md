# 정리
[[my tistory]]()

# 내 풀이
```kotlin
import java.util.*

class Solution {
    val dx = intArrayOf(0, 0, -1, 1)
    val dy = intArrayOf(1, -1, 0, 0)
    lateinit var visited: Array<BooleanArray>
    data class Node(
        val row: Int,
        val col: Int,
        val count: Int, // 부딪혀 방향이 바뀐 횟수
    )
    
    fun solution(board: Array<String>): Int {
        var answer: Int = 0
        /**
         * 1. dx, dy, visited 배열 & Node class 생성
         * 2. start pair 찾기
         * 3. bfs
         * 4. 부딪혀 방향이 바뀌는 pair 찾기
         */
        visited = Array(board.size) { BooleanArray(board[0].length) } // default == false
        val startPair = findStartPair(board)
        val startNode = Node(startPair.first, startPair.second, 0)
        answer = bfs(board, visited, startNode)      

        return answer
    }
    
    fun findStartPair(board: Array<String>): Pair<Int, Int> {
        var startPair = Pair(-1, -1)
        
        board.forEachIndexed {row, string -> 
            string.forEachIndexed {col, char -> 
                if (char == 'R') startPair = Pair(row, col)
            }
        }
        return startPair
    }
    
    fun bfs(board: Array<String>, visited: Array<BooleanArray>, startNode: Node): Int {
        val queue: Queue<Node> = LinkedList()
        queue.add(startNode)
        visited[startNode.row][startNode.col] = true
        while(queue.isNotEmpty()) {
            val currentNode = queue.poll()
            if (board[currentNode.row][currentNode.col] == 'G') return currentNode.count
            
            for (i in 0..3) {
                val nextPair = findPairWhenChangeDirection(board, currentNode.row, currentNode.col, dx[i], dy[i])
                if (!visited[nextPair.first][nextPair.second]) {
                    visited[nextPair.first][nextPair.second] = true
                    queue.add(Node(nextPair.first, nextPair.second, currentNode.count + 1))
                }
            }
        }
        return -1
        
    }
    
    fun findPairWhenChangeDirection(board: Array<String>, currentRow: Int, currentCol: Int, dx: Int, dy: Int): Pair<Int, Int> {
        var startRow: Int = currentRow
        var startCol: Int = currentCol
        while (true) {
            if (startRow + dx == -1 || startRow + dx == board.size) return Pair(startRow, startCol)
            if (startCol + dy == -1 || startCol + dy == board[0].length) return Pair(startRow, startCol)
            if (board[startRow + dx][startCol + dy] == 'D') return Pair(startRow, startCol)
            
            startRow += dx
            startCol += dy
        } 
        
    }
}
```

