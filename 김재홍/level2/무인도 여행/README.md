# 정리
[[my tistory]](https://chivalrous-hyeop.tistory.com/9)

# 풀이 수정
```kotlin
import java.util.*

class Solution {
    lateinit var visited: Array<BooleanArray>
    val dx = intArrayOf(0, 0, -1, 1)
    val dy = intArrayOf(1, -1, 0, 0)
    data class Node(
        val row: Int,
        val col: Int,
    )
    var onlyX: Boolean = true
    
    fun solution(maps: Array<String>): IntArray {
        var answer: IntArray = intArrayOf()
        /**
         * 1. visited, dx, dy 배열 & Node class & 조기 종료 판단 변수 생성
         * 2. bfs
         * 3. 조기 종료 판단 변수 확인 및 조치
         */
        visited = Array(maps.size) { BooleanArray(maps[0].length) }
        
        maps.forEachIndexed {row, string ->
            string.forEachIndexed {col, char ->
                if (char != 'X' && !visited[row][col]) {
                    onlyX = false // 조기 종료 판단 변수 변경
                    // bfs
                    val queue: Queue<Node> = LinkedList()
                    queue.add(Node(row, col))
                    var record: Int = 0 // answer에 저장할 record 초기화
                    
                    while (queue.isNotEmpty()) {
                        val currentNode = queue.poll()
                        visited[currentNode.row][currentNode.col] = true
                        record += maps[currentNode.row][currentNode.col].toString().toInt()
                        for (i in 0..3) {
                            val newRow = currentNode.row + dx[i]
                            val newCol = currentNode.col + dy[i]
                            if (newRow >= 0 && newRow < maps.size && newCol >= 0 && newCol < maps[0].length) {
                                if (maps[newRow][newCol] != 'X' && !visited[newRow][newCol]) {
                                    visited[newRow][newCol] = true
                                    queue.add(Node(newRow, newCol))
                                }
                            }
                        }
                    }
                    answer += record
                } 
            }
        }
        
        if (onlyX) return intArrayOf(-1) // 조기 종료 판단
        
        return answer.sorted().toIntArray()
    }
    
}
```

# 내 풀이
```kotlin
import java.util.*

class Solution {
    // 상하좌우
    val dx = intArrayOf(0, 0, -1, 1)
    val dy = intArrayOf(1, -1, 0, 0)
    // map
    val map: MutableList<MutableList<String>> = mutableListOf()
    val check: MutableList<MutableList<Int>> = mutableListOf()
    // 조기종료 확인
    var endCheck: Boolean = true
    
    class Node(
        val x: Int,
        val y: Int,
    ) {
        
    }
    
    fun solution(maps: Array<String>): IntArray {
        var answer: IntArray = intArrayOf()
        /**
         * 1. map, check 만들기
         * 2. (0,0)에서부터 탐색 bfs
         * 3. 탐색이 종료될 때, 머문 일수 합 answer에 추가
         */
         makeMapAndCheck(maps) // [1]
         if (endCheck) return intArrayOf(-1)
         println("map: $map")
         println("check: $check")
         
         val queue: Queue<Node> = LinkedList() // 좌표를 담는 queue
         for (x in 0 until map.size) {
             for (y in 0 until map[0].size) {
                 if (map[x][y] != "X" && check[x][y] == 0) {
                     queue.add(Node(x, y))
                     check[x][y] = 1
                     // bfs
                     var dayRecord: Int = 0
                     while (queue.size > 0) {
                         val coordinate: Node = queue.poll()
                         // 머무를 수 있는 일자 기록, check 
                         dayRecord += map[coordinate.x][coordinate.y].toInt()
                         println("현재 좌표 >>> (${coordinate.x}, ${coordinate.y})")
                         for (k in 0 until 4) {
                             val newX = dx[k] + coordinate.x
                             val newY = dy[k] + coordinate.y
                             if (checkNewCoordinate(newX, newY)) {
                                 queue.add(Node(newX, newY))
                                 // check를 이곳에서 하지 않으면, 중복된 좌표를 queue에 넣는다.
                                 check[newX][newY] = 1
                             }
                         }
                     }
                     answer += dayRecord
                 }
             }
             
        }
        
        return answer.sorted().toIntArray()
    }
    
    fun makeMapAndCheck(maps: Array<String>) {
        for (i in 0 until maps.size) {
            val rowOfMap = mutableListOf<String>()
            val rowOfCheck = mutableListOf<Int>()
            for (j in 0 until maps[i].length) {
                if (maps[i][j].toString() != "X") {
                    endCheck = false
                }
                rowOfMap.add(maps[i][j].toString())
                rowOfCheck.add(0)
            }
            map.add(rowOfMap)
            check.add(rowOfCheck)
        }
    }
    
    fun checkNewCoordinate(newX: Int, newY: Int): Boolean {
        if (newX >= 0 && newX < map.size && newY >= 0 && newY < map[0].size) {
            if (map[newX][newY] != "X" && check[newX][newY] == 0) {
                return true
            }
        } 
        
        return false
    }
}
```
