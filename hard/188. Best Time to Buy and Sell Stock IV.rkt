(define/contract (max-profit k prices)
  (-> exact-integer? (listof exact-integer?) exact-integer?)
  
  ;; Base cases:
  ;; 1. If no transactions allowed (k=0)
  ;; 2. If prices list is empty or has only one element (no trading possible)
  (cond
    [(or (= k 0) (null? prices) (null? (cdr prices))) 0]
    [else
     ;; Convert the prices list to a vector for O(1) access
     (let* ((prices-vec (list->vector prices))
            (n (vector-length prices-vec)))
       
       ;; Initialize DP table:
       ;; dp is a vector of vectors where:
       ;; - First dimension: transaction counts (0 to k)
       ;; - Second dimension: days (0 to n-1)
       (let ((dp (make-vector (add1 k))))
         ;; Initialize each transaction count's vector with n zeros
         (for ([i (in-range (add1 k))])
           (vector-set! dp i (make-vector n 0)))
         
         ;; Fill DP table:
         ;; Outer loop: for each transaction count from 1 to k
         (for ([i (in-range 1 (add1 k))])
           ;; Track the maximum value of (dp[i-1][j] - prices[j])
           ;; Initialize with -prices[0] (potential buy on day 0)
           (let ([max-diff (- (vector-ref prices-vec 0))])
             
             ;; Inner loop: for each day from 1 to n-1
             (for ([j (in-range 1 n)])
               ;; Two choices for day j:
               ;; 1. Don't trade: profit remains dp[i][j-1]
               (let ([no-trade (vector-ref (vector-ref dp i) (sub1 j))]
                     ;; 2. Sell today: price[j] + max_diff
                     ;; where max_diff tracks best (dp[i-1][m] - price[m])
                     [sell-today (+ (vector-ref prices-vec j) max-diff)])
                 
                 ;; Take the maximum of both options
                 (vector-set! (vector-ref dp i) j (max no-trade sell-today))
                 
                 ;; Update max_diff for next iteration:
                 ;; Compare current max_diff with potential new buy at day j
                 ;; (dp[i-1][j] - price[j])
                 (set! max-diff (max max-diff 
                                  (- (vector-ref (vector-ref dp (sub1 i)) j)
                                     (vector-ref prices-vec j))))))))
         
         ;; The answer is in dp[k][n-1] - max profit with k transactions up to last day
         (vector-ref (vector-ref dp k) (sub1 n))))]))
