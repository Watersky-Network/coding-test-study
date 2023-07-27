# 정리
[[my tistory]]()

# 풀이
```kotlin
import java.util.*

class Solution {
    fun solution(n: Int, wires: Array<IntArray>): Int {
        var answer: Int = n // 간선의 수는 n - 1개 (변경)
        /**
         * 1. wires list를 순회하며 connection 배열 생성
         * 2. wires list를 순회하며, 각 노드 간 연결 노선 갯수 확인
         * 3. 노선 갯수를 확인할 수 있는 메서드 구현
         * 4. 각 값의 차의 최소 값 찾기
         */
        
        val connection = Array(n) { mutableListOf<Int>() }
        wires.forEach {
            connection[it[0] - 1].add(it[1] - 1)
            connection[it[1] - 1].add(it[0] - 1)
        }
        
        wires.forEach {
            val one = countEdge(connection, it[0] - 1, it[1] - 1)
            val theOther = countEdge(connection, it[1] - 1, it[0] - 1)
            var record = one - theOther
            if (record < 0) record *= -1
            if (answer > record) answer = record
        }
        
        return answer
    }
    
    fun countEdge(connection: Array<MutableList<Int>>, start: Int, end: Int): Int {
        val visited = HashSet<Int>()
        val queue: Queue<Int> = LinkedList()

        connection[start].forEach {
            if (it != end) { // 연결을 끊는 지점은 pass
                queue.add(it)
                visited.add(it)
            }
        }
        while (queue.isNotEmpty()) {
            val node = queue.poll()
            connection[node].forEach {
                if (it != start && !visited.contains(it)) { // 조건: 연결을 끊는 지점X && 방문 X
                    visited.add(it)
                    queue.add(it)
                }

            }
        }
        return visited.size
    }
}
```
