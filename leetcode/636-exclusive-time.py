class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        result = [0] * n
        stack = []
        prev = 0
        
        for log in logs:
            fid, state, time = log.split(':')
            fid, time = int(fid), int(time)
            
            if state == 'start':
                if stack:
                    result[stack[-1]] += (time - prev)
                stack.append(fid)
                prev = time
            else:
                result[stack.pop()] += (time - prev + 1)
                prev = time + 1
                
        return result
                
